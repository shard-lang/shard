/* ************************************************************************* */
/* This file is part of Shard.                                               */
/*                                                                           */
/* Shard is free software: you can redistribute it and/or modify             */
/* it under the terms of the GNU Affero General Public License as            */
/* published by the Free Software Foundation.                                */
/*                                                                           */
/* This program is distributed in the hope that it will be useful,           */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the              */
/* GNU Affero General Public License for more details.                       */
/*                                                                           */
/* You should have received a copy of the GNU Affero General Public License  */
/* along with this program. If not, see <http://www.gnu.org/licenses/>.      */
/* ************************************************************************* */

// C++
#include <algorithm>
#include <ios>
#include <iostream>
#include <fstream>
#include <iterator>
#include <stdexcept>

// Shard
#include "shard/Exception.hpp"
#include "shard/FilePath.hpp"
#include "shard/Map.hpp"
#include "shard/String.hpp"
#include "shard/StringView.hpp"
#include "shard/ir/Block.hpp"
#include "shard/ir/Constant.hpp"
#include "shard/ir/Function.hpp"
#include "shard/ir/Module.hpp"
#include "shard/ir/Type.hpp"
#include "shard/ir/Value.hpp"
#include "shard/ir/Serializer.hpp"

/* ************************************************************************* */

using namespace shard;

/* ************************************************************************* */

namespace {

/* ************************************************************************* */

/**
 * @brief      Create an example module.
 *
 * @return     A module.
 */
ir::Module exampleModule()
{
    ir::Module module;

    {
        auto fn = module.createFunction(
            "add",
            ir::TypeInt32::instance(),
            {ir::TypeInt32::instance(), ir::TypeInt32::instance()});

        auto block = fn->createBlock();
        auto res   = block->createInstruction<ir::InstructionAdd>(
            ir::TypeInt32::instance(), fn->arg(0), fn->arg(1));

        block->createInstruction<ir::InstructionReturn>(
            res->resultType(), res->result());
    }

    {
        auto fn = module.createFunction("main", {});

        auto block  = fn->createBlock();
        auto alloc1 = block->createInstruction<ir::InstructionAlloc>(
            ir::TypeInt32::instance());
        auto alloc2 = block->createInstruction<ir::InstructionAlloc>(
            ir::TypeInt32::instance());

        auto const1 = module.createConstant<ir::ConstInt32>(1);
        auto const2 = module.createConstant<ir::ConstInt32>(2);

        block->createInstruction<ir::InstructionStore>(
            alloc1->result(), const1.get());
        block->createInstruction<ir::InstructionStore>(
            alloc2->result(), const2.get());

        auto val1 =
            block->createInstruction<ir::InstructionLoad>(alloc1->result());
        auto val2 =
            block->createInstruction<ir::InstructionLoad>(alloc2->result());

        auto callAdd = block->createInstruction<ir::InstructionCall>(
            "add",
            ir::TypeInt32::instance(),
            Vector<ViewPtr<ir::Value>>{val1->result(), val2->result()});

        auto stringType =
            module.createType<ir::TypePointer>(ir::TypeInt8::instance());

        auto callToString = block->createInstruction<ir::InstructionCall>(
            "toString",
            stringType,
            Vector<ViewPtr<ir::Value>>{callAdd->result()});

        auto callPrint = block->createInstruction<ir::InstructionCall>(
            "print", Vector<ViewPtr<ir::Value>>{callToString->result()});

        block->createInstruction<ir::InstructionCall>(
            "free", Vector<ViewPtr<ir::Value>>{callToString->result()});

        block->createInstruction<ir::InstructionReturnVoid>();
    }

    return module;
}

/* ************************************************************************* */

/**
 * @brief      Load module form file path.
 *
 * @param      path  The path.
 *
 * @return     Loaded module.
 */
ir::Module loadModule(FilePath path)
{
    std::ifstream file(path, std::ios::in | std::ios::binary);

    if (!file.is_open())
        throw std::runtime_error("Unable to open source file");

    return ir::deserialize(file);
}

/* ************************************************************************* */

struct Mapping
{
    Map<ViewPtr<ir::Value>, int> values;
    Map<ViewPtr<ir::Block>, int> blocks;
};

/* ************************************************************************* */

/**
 * @brief      Map value to index.
 *
 * @param      mapping  The mapping in block.
 * @param      value    The value to map.
 *
 * @return     Value index.
 */
int mapValue(Mapping& mapping, ViewPtr<ir::Value> value)
{
    SHARD_ASSERT(value != nullptr);

    auto it = mapping.values.find(value);

    if (it != end(mapping.values))
        return it->second;

    auto [iti, ins] = mapping.values.emplace(value, mapping.values.size());

    return iti->second;
}

/* ************************************************************************* */

/**
 * @brief      Map block to index.
 *
 * @param      mapping  The mapping in block.
 * @param      block    The block to map.
 *
 * @return     Block index.
 */
int mapBlock(Mapping& mapping, ViewPtr<ir::Block> block)
{
    SHARD_ASSERT(block != nullptr);

    auto it = mapping.blocks.find(block);

    if (it != end(mapping.blocks))
        return it->second;

    auto [iti, ins] = mapping.blocks.emplace(block, mapping.blocks.size());

    return iti->second;
}

/* ************************************************************************* */

/**
 * @brief      Dump a type to stream.
 *
 * @param      out   The output stream.
 * @param      type  The type.
 */
void dumpType(std::ostream& out, ViewPtr<ir::Type> type)
{
    if (type == nullptr)
    {
        out << "void";
        return;
    }

    switch (type->kind())
    {
    case ir::TypeKind::Int1: out << "int1"; break;

    case ir::TypeKind::Int8: out << "int8"; break;

    case ir::TypeKind::Int16: out << "int16"; break;

    case ir::TypeKind::Int32: out << "int32"; break;

    case ir::TypeKind::Int64: out << "int64"; break;

    case ir::TypeKind::Float32: out << "float32"; break;

    case ir::TypeKind::Float64: out << "float64"; break;

    case ir::TypeKind::Pointer:
        dumpType(out, type->as<ir::TypePointer>().type());
        out << "*";
        break;

    case ir::TypeKind::Struct:
        // TODO: struct
        out << "{}";
        break;
    }
}

/* ************************************************************************* */

/**
 * @brief      Dumps a value.
 *
 * @param      out      The output stream.
 * @param      mapping  The mapping.
 * @param      value    The value.
 */
void dumpValue(std::ostream& out, Mapping& mapping, ViewPtr<ir::Value> value)
{
    if (value->isConst())
    {
        switch (value->type()->kind())
        {
        case ir::TypeKind::Int1:
        {
            auto& val = static_cast<ir::ConstInt1&>(*value);
            out << (val.value() ? "1" : "0");
            break;
        }

        case ir::TypeKind::Int8:
        {
            auto& val = static_cast<ir::ConstInt8&>(*value);
            out << static_cast<int>(val.value());
            break;
        }

        case ir::TypeKind::Int16:
        {
            auto& val = static_cast<ir::ConstInt16&>(*value);
            out << static_cast<int>(val.value());
            break;
        }

        case ir::TypeKind::Int32:
        {
            auto& val = static_cast<ir::ConstInt32&>(*value);
            out << val.value();
            break;
        }

        case ir::TypeKind::Int64:
        {
            auto& val = static_cast<ir::ConstInt64&>(*value);
            out << val.value();
            break;
        }

        case ir::TypeKind::Float32:
        {
            auto& val = static_cast<ir::ConstFloat32&>(*value);
            out << val.value();
            break;
        }

        case ir::TypeKind::Float64:
        {
            auto& val = static_cast<ir::ConstFloat64&>(*value);
            out << val.value();
            break;
        }

        default: throw std::runtime_error("Unsupported constant type");
        }
    }
    else
    {
        out << '%' << mapValue(mapping, value);
    }
}

/* ************************************************************************* */

/**
 * @brief      Dumps a label.
 *
 * @param      out      The output stream.
 * @param      mapping  The mapping.
 * @param      block    The block.
 */
void dumpLabel(std::ostream& out, Mapping& mapping, ViewPtr<ir::Block> block)
{
    out << "@L_" << mapBlock(mapping, block);
}

/* ************************************************************************* */

/**
 * @brief      Dumps an instruction.
 *
 * @param      out      The output stream.
 * @param      mapping  The mapping.
 * @param      instr    The instruction.
 */
void dumpInstr(
    std::ostream& out,
    Mapping& mapping,
    ViewPtr<ir::Instruction> instr)
{
    out << "    ";

    switch (instr->kind())
    {
    case ir::InstructionKind::Alloc:
    {
        const auto& in = instr->as<ir::InstructionAlloc>();
        dumpValue(out, mapping, in.result());
        out << " = alloc ";
        dumpType(out, in.type());

        if (in.count() != 1)
            out << ", " << in.count();

        break;
    }

    case ir::InstructionKind::Store:
    {
        const auto& in = instr->as<ir::InstructionStore>();
        out << "store ";
        dumpType(out, in.value()->type());
        out << " ";
        dumpValue(out, mapping, in.pointer());
        out << ", ";
        dumpValue(out, mapping, in.value());

        if (in.index() != 0)
            out << ", " << in.index();

        break;
    }

    case ir::InstructionKind::Load:
    {
        const auto& in = instr->as<ir::InstructionLoad>();
        dumpValue(out, mapping, in.result());
        out << " = load ";
        dumpType(out, in.resultType());
        out << " ";
        dumpValue(out, mapping, in.pointer());

        if (in.index() != 0)
            out << ", " << in.index();

        break;
    }

    case ir::InstructionKind::Add:
    {
        const auto& in = instr->as<ir::InstructionAdd>();

        dumpValue(out, mapping, in.result());
        out << " = add ";
        dumpType(out, in.type());
        out << " ";
        dumpValue(out, mapping, in.value1());
        out << ", ";
        dumpValue(out, mapping, in.value2());
        break;
    }

    case ir::InstructionKind::Sub:
    {
        const auto& in = instr->as<ir::InstructionSub>();

        dumpValue(out, mapping, in.result());
        out << " = sub ";
        dumpType(out, in.type());
        out << " ";
        dumpValue(out, mapping, in.value1());
        out << ", ";
        dumpValue(out, mapping, in.value2());
        break;
    }

    case ir::InstructionKind::Mul:
    {
        const auto& in = instr->as<ir::InstructionMul>();

        dumpValue(out, mapping, in.result());
        out << " = mul ";
        dumpType(out, in.type());
        out << " ";
        dumpValue(out, mapping, in.value1());
        out << ", ";
        dumpValue(out, mapping, in.value2());
        break;
    }

    case ir::InstructionKind::Div:
    {
        const auto& in = instr->as<ir::InstructionDiv>();

        dumpValue(out, mapping, in.result());
        out << " = div ";
        dumpType(out, in.type());
        out << " ";
        dumpValue(out, mapping, in.value1());
        out << ", ";
        dumpValue(out, mapping, in.value2());
        break;
    }

    case ir::InstructionKind::Rem:
    {
        const auto& in = instr->as<ir::InstructionRem>();

        dumpValue(out, mapping, in.result());
        out << " = rem ";
        dumpType(out, in.type());
        out << " ";
        dumpValue(out, mapping, in.value1());
        out << ", ";
        dumpValue(out, mapping, in.value2());
        break;
    }

    case ir::InstructionKind::Cmp: out << "cmp"; break;

    case ir::InstructionKind::And:
    {
        const auto& in = instr->as<ir::InstructionAnd>();

        dumpValue(out, mapping, in.result());
        out << " = and ";
        dumpType(out, in.type());
        out << " ";
        dumpValue(out, mapping, in.value1());
        out << ", ";
        dumpValue(out, mapping, in.value2());
        break;
    }

    case ir::InstructionKind::Or:
    {
        const auto& in = instr->as<ir::InstructionOr>();

        dumpValue(out, mapping, in.result());
        out << " = or ";
        dumpType(out, in.type());
        out << " ";
        dumpValue(out, mapping, in.value1());
        out << ", ";
        dumpValue(out, mapping, in.value2());
        break;
    }

    case ir::InstructionKind::Xor:
    {
        const auto& in = instr->as<ir::InstructionXor>();

        dumpValue(out, mapping, in.result());
        out << " = xor ";
        dumpType(out, in.type());
        out << " ";
        dumpValue(out, mapping, in.value1());
        out << ", ";
        dumpValue(out, mapping, in.value2());
        break;
    }

    case ir::InstructionKind::Branch:
    {
        auto& in = instr->as<ir::InstructionBranch>();
        out << "branch ";
        dumpLabel(out, mapping, in.block());
        break;
    }

    case ir::InstructionKind::BranchCondition:
    {
        auto& in = instr->as<ir::InstructionBranchCondition>();
        out << "branch ";
        dumpValue(out, mapping, in.condition());
        out << ", ";
        dumpLabel(out, mapping, in.blockTrue());
        out << ", ";
        dumpLabel(out, mapping, in.blockFalse());
        break;
    }

    case ir::InstructionKind::Call:
    {
        auto& in = instr->as<ir::InstructionCall>();

        if (auto result = in.result(); result)
        {
            dumpValue(out, mapping, result);
            out << " = call ";
            dumpType(out, result->type());
            out << "(";
        }
        else
        {
            out << "call void(";
        }

        {
            bool first = true;
            for (const auto& arg : in.arguments())
            {
                if (!first)
                    out << ", ";
                dumpType(out, arg->type());
                first = false;
            }
        }

        out << ") @" << in.name() << " (";

        {
            bool first = true;
            for (const auto& arg : in.arguments())
            {
                if (!first)
                    out << ", ";
                dumpValue(out, mapping, arg);
                first = false;
            }
        }

        out << ")";

        break;
    }

    case ir::InstructionKind::Return:
    {
        auto& in = instr->as<ir::InstructionReturn>();

        out << "return ";
        dumpType(out, in.type());
        out << " ";
        dumpValue(out, mapping, in.value());
        break;
    }

    case ir::InstructionKind::ReturnVoid: out << "return void"; break;
    }

    out << "\n";
}

/* ************************************************************************* */

/**
 * @brief      Dumps a block.
 *
 * @param      out      The output stream.
 * @param      mapping  The mapping.
 * @param      block    The block.
 */
void dumpBlock(std::ostream& out, Mapping& mapping, ViewPtr<ir::Block> block)
{
    out << "  ";
    dumpLabel(out, mapping, block);
    out << ":\n";

    for (const auto& instr : block->instructions())
    {
        dumpInstr(out, mapping, instr.get());
    }
}

/* ************************************************************************* */

/**
 * @brief      Dump a module to stream.
 *
 * @param      out     The output stream.
 * @param      module  The module.
 */
void dumpModule(std::ostream& out, const ir::Module& module)
{
    for (const auto& fn : module.functions())
    {
        out << '@' << fn->name() << " = function ";

        dumpType(out, fn->returnType());

        out << '(';

        bool first = true;
        for (const auto& param : fn->parameterTypes())
        {
            if (!first)
                out << ", ";

            dumpType(out, param);
            first = false;
        }

        out << ") {";

        Mapping mapping;

        // Map arguments
        for (const auto& arg : fn->arguments())
            mapValue(mapping, arg.get());

        for (const auto& block : fn->blocks())
        {
            out << "\n";
            dumpBlock(out, mapping, block.get());
        }

        out << "}\n\n";
    }
}

/* ************************************************************************* */

} // namespace

/* ************************************************************************* */

/**
 * @brief Entry function.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char** argv)
{
    /*
    if (argc < 2)
    {
        std::cerr << "no input file" << std::endl;
        return -1;
    }
    */

    try
    {
        if (argc < 2)
        {
            ir::Module module = exampleModule();
            dumpModule(std::cout, module);
        }
        else
        {
            ir::Module module = loadModule(argv[1]);
            dumpModule(std::cout, module);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "\033[31mERROR\033[0m: " << e.what() << "" << std::endl;
        return -1;
    }
}

/* ************************************************************************* */

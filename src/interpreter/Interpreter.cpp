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

// Declaration
#include "shard/interpreter/Interpreter.hpp"

// C++
#include <iostream>

// Shard
#include "shard/interpreter/Exception.hpp"
#include "shard/ir/Block.hpp"
#include "shard/ir/Constant.hpp"
#include "shard/ir/Function.hpp"
#include "shard/ir/Instruction.hpp"
#include "shard/ir/Module.hpp"

/* ************************************************************************* */

namespace shard::interpreter {

/* ************************************************************************* */

namespace {

/* ************************************************************************* */

/**
 * @brief      Convert interpreter value to IR type.
 *
 * @param      value  The value.
 *
 * @return     IR type.
 */
ViewPtr<ir::Type> fetchType(const Value& value)
{
    if (value.is<bool>())
        return ir::TypeInt1::instance();
    else if (value.is<int8_t>())
        return ir::TypeInt8::instance();
    else if (value.is<int16_t>())
        return ir::TypeInt16::instance();
    else if (value.is<int32_t>())
        return ir::TypeInt32::instance();
    else if (value.is<int64_t>())
        return ir::TypeInt64::instance();
    else if (value.is<float>())
        return ir::TypeFloat32::instance();
    else if (value.is<double>())
        return ir::TypeFloat64::instance();

    throw Exception("Unknown value type");
}

/* ************************************************************************* */

/**
 * @brief      Cast value to type.
 *
 * @param      value  The value.
 * @param      type   The type.
 *
 * @tparam     T      The value type.
 *
 * @return     The result value.
 */
template<typename T>
Value castTo(T value, const ir::Type& type)
{
    switch (type.kind())
    {
    case ir::TypeKind::Int8: return Value{int8_t(value)};

    case ir::TypeKind::Int16: return Value{int16_t(value)};

    case ir::TypeKind::Int32: return Value{int32_t(value)};

    case ir::TypeKind::Int64: return Value{int64_t(value)};

    case ir::TypeKind::Float32: return Value{float(value)};

    case ir::TypeKind::Float64: return Value{double(value)};

    default: throw Exception("Unsupported operand types");
    }
}

/* ************************************************************************* */

/**
 * @brief      Cast value to type.
 *
 * @param      value  The value.
 * @param      type   The type.
 *
 * @return     The result value.
 */
Value castTo(const Value& value, const ir::Type& type)
{
    if (value.is<bool>())
        return castTo<bool>(value.get<bool>(), type);
    else if (value.is<int8_t>())
        return castTo<int8_t>(value.get<int8_t>(), type);
    else if (value.is<int16_t>())
        return castTo<int16_t>(value.get<int16_t>(), type);
    else if (value.is<int32_t>())
        return castTo<int32_t>(value.get<int32_t>(), type);
    else if (value.is<int64_t>())
        return castTo<int64_t>(value.get<int64_t>(), type);
    else if (value.is<float>())
        return castTo<float>(value.get<float>(), type);
    else if (value.is<double>())
        return castTo<double>(value.get<double>(), type);

    throw Exception("Unknown value type");
}

/* ************************************************************************* */

/**
 * @brief      Perform binary operation.
 *
 * @param      type  The values type.
 * @param      val1  The first value.
 * @param      val2  The second value.
 * @param      op    The operation.
 *
 * @tparam     OP    Operation type.
 *
 * @return     The result.
 */
template<typename OP>
Value binaryOperation(
    const ir::Type& type,
    const Value& val1,
    const Value& val2,
    OP op)
{
    switch (type.kind())
    {
    case ir::TypeKind::Int8:
        return Value{op(val1.get<int8_t>(), val2.get<int8_t>())};

    case ir::TypeKind::Int16:
        return Value{op(val1.get<int16_t>(), val2.get<int16_t>())};

    case ir::TypeKind::Int32:
        return Value{op(val1.get<int32_t>(), val2.get<int32_t>())};

    case ir::TypeKind::Int64:
        return Value{op(val1.get<int64_t>(), val2.get<int64_t>())};

    default: throw Exception("Unsupported operand types");
    }
}

/* ************************************************************************* */

/**
 * @brief      Perform binary operation.
 *
 * @param      type  The values type.
 * @param      val1  The first value.
 * @param      val2  The second value.
 * @param      op    The operation.
 *
 * @tparam     OP    Operation type.
 *
 * @return     The result.
 */
template<typename OP>
Value binaryOperationFloat(
    const ir::Type& type,
    const Value& val1,
    const Value& val2,
    OP op)
{
    switch (type.kind())
    {
    case ir::TypeKind::Int8:
        return Value{op(val1.get<int8_t>(), val2.get<int8_t>())};

    case ir::TypeKind::Int16:
        return Value{op(val1.get<int16_t>(), val2.get<int16_t>())};

    case ir::TypeKind::Int32:
        return Value{op(val1.get<int32_t>(), val2.get<int32_t>())};

    case ir::TypeKind::Int64:
        return Value{op(val1.get<int64_t>(), val2.get<int64_t>())};

    case ir::TypeKind::Float32:
        return Value{op(val1.get<float>(), val2.get<float>())};

    case ir::TypeKind::Float64:
        return Value{op(val1.get<double>(), val2.get<double>())};

    default: throw Exception("Unsupported operand types");
    }
}

/* ************************************************************************* */

struct PrintVisitor
{
    void operator()(bool arg) const
    {
        std::cout << (arg ? "true" : "false") << '\n';
    }

    void operator()(std::monostate) const
    {
        // Nothing
    }

    template<typename T>
    void operator()(T&& arg) const
    {
        std::cout << arg << '\n';
    }
};

/* ************************************************************************* */

} // namespace

/* ************************************************************************* */

void Interpreter::load(const ir::Module& module)
{
    // Register module
    m_modules.push_back(&module);
}

/* ************************************************************************* */

Value Interpreter::call(StringView name, const Vector<Value>& args)
{
    // TODO: remove
    if (name == "print")
    {
        for (const auto& arg : args)
            arg.visit(PrintVisitor{});

        return {};
    }

    // Find function
    ViewPtr<const ir::Function> function;

    Vector<ViewPtr<ir::Type>> types;
    for (const auto& arg : args)
        types.push_back(fetchType(arg));

    for (auto module : m_modules)
    {
        function = module->findFunction(name, types);

        if (function)
            break;
    }

    if (function == nullptr)
        throw Exception("Unable to find function: " + String(name));

    // Create new stack
    m_stack.push({});

    // Copy arguments to the frame
    for (size_t i = 0; i < args.size(); ++i)
        currentFrame().value(*function->arg(i)) = args[i];

    // Eval the first block
    evalBlock(*function->blocks().front());

    // Copy result from stack
    auto result = castTo(m_stack.top().result(), *function->returnType());

    m_stack.pop();

    return result;
}

/* ************************************************************************* */

Value Interpreter::fetchValue(const ir::Value& value)
{
    if (!value.isConst())
    {
        return currentFrame().value(value);
    }
    else
    {
        switch (value.type()->kind())
        {
        case ir::TypeKind::Int1:
        {
            const auto& val = static_cast<const ir::ConstInt1&>(value);
            return val.value();
        }

        case ir::TypeKind::Int8:
        {
            const auto& val = static_cast<const ir::ConstInt8&>(value);
            return val.value();
        }

        case ir::TypeKind::Int16:
        {
            const auto& val = static_cast<const ir::ConstInt16&>(value);
            return val.value();
        }

        case ir::TypeKind::Int32:
        {
            const auto& val = static_cast<const ir::ConstInt32&>(value);
            return val.value();
        }

        case ir::TypeKind::Int64:
        {
            const auto& val = static_cast<const ir::ConstInt64&>(value);
            return val.value();
        }

        case ir::TypeKind::Float32:
        {
            const auto& val = static_cast<const ir::ConstFloat32&>(value);
            return val.value();
        }

        case ir::TypeKind::Float64:
        {
            const auto& val = static_cast<const ir::ConstFloat64&>(value);
            return val.value();
        }

        default: throw Exception("Unsupported constant type");
        }
    }
}

/* ************************************************************************* */

void Interpreter::evalBlock(const ir::Block& block)
{
    // Just evaluate all instructions
    for (const auto& instr : block.instructions())
        evalInstruction(*instr);
}

/* ************************************************************************* */

void Interpreter::evalInstruction(const ir::Instruction& instr)
{
    switch (instr.kind())
    {
    case ir::InstructionKind::Alloc:
        evalInstruction(instr.as<ir::InstructionAlloc>());
        break;
    case ir::InstructionKind::Store:
        evalInstruction(instr.as<ir::InstructionStore>());
        break;
    case ir::InstructionKind::Load:
        evalInstruction(instr.as<ir::InstructionLoad>());
        break;
    case ir::InstructionKind::Add:
        evalInstruction(instr.as<ir::InstructionAdd>());
        break;
    case ir::InstructionKind::Sub:
        evalInstruction(instr.as<ir::InstructionSub>());
        break;
    case ir::InstructionKind::Mul:
        evalInstruction(instr.as<ir::InstructionMul>());
        break;
    case ir::InstructionKind::Div:
        evalInstruction(instr.as<ir::InstructionDiv>());
        break;
    case ir::InstructionKind::Rem:
        evalInstruction(instr.as<ir::InstructionRem>());
        break;
    case ir::InstructionKind::Cmp:
        evalInstruction(instr.as<ir::InstructionCmp>());
        break;
    case ir::InstructionKind::And:
        evalInstruction(instr.as<ir::InstructionAnd>());
        break;
    case ir::InstructionKind::Or:
        evalInstruction(instr.as<ir::InstructionOr>());
        break;
    case ir::InstructionKind::Xor:
        evalInstruction(instr.as<ir::InstructionXor>());
        break;
    case ir::InstructionKind::Branch:
        evalInstruction(instr.as<ir::InstructionBranch>());
        break;
    case ir::InstructionKind::BranchCondition:
        evalInstruction(instr.as<ir::InstructionBranchCondition>());
        break;
    case ir::InstructionKind::Call:
        evalInstruction(instr.as<ir::InstructionCall>());
        break;
    case ir::InstructionKind::Return:
        evalInstruction(instr.as<ir::InstructionReturn>());
        break;
    case ir::InstructionKind::ReturnVoid:
        evalInstruction(instr.as<ir::InstructionReturnVoid>());
        break;
    default: throw Exception("Unsupported instruction");
    }
}

/* ************************************************************************* */

void Interpreter::evalInstruction(const ir::InstructionAlloc& instr)
{
    // TODO: implement size allocation
}

/* ************************************************************************* */

void Interpreter::evalInstruction(const ir::InstructionStore& instr)
{
    // TODO: implement index

    // Store value
    currentFrame().value(*instr.pointer()) = fetchValue(*instr.value());
}

/* ************************************************************************* */

void Interpreter::evalInstruction(const ir::InstructionLoad& instr)
{
    // TODO: implement index

    // Load value
    currentFrame().value(*instr.result()) = fetchValue(*instr.pointer());
}

/* ************************************************************************* */

void Interpreter::evalInstruction(const ir::InstructionAdd& instr)
{
    const Value val1 = fetchValue(*instr.value1());
    const Value val2 = fetchValue(*instr.value2());

    const Value res =
        binaryOperationFloat(*instr.type(), val1, val2, std::plus<>{});

    // Store result
    currentFrame().value(*instr.result()) = res;
}

/* ************************************************************************* */

void Interpreter::evalInstruction(const ir::InstructionSub& instr)
{
    const Value val1 = fetchValue(*instr.value1());
    const Value val2 = fetchValue(*instr.value2());

    const Value res =
        binaryOperationFloat(*instr.type(), val1, val2, std::minus<>{});

    // Store result
    currentFrame().value(*instr.result()) = res;
}

/* ************************************************************************* */

void Interpreter::evalInstruction(const ir::InstructionMul& instr)
{
    const Value val1 = fetchValue(*instr.value1());
    const Value val2 = fetchValue(*instr.value2());

    const Value res =
        binaryOperationFloat(*instr.type(), val1, val2, std::multiplies<>{});

    // Store result
    currentFrame().value(*instr.result()) = res;
}

/* ************************************************************************* */

void Interpreter::evalInstruction(const ir::InstructionDiv& instr)
{
    const Value val1 = fetchValue(*instr.value1());
    const Value val2 = fetchValue(*instr.value2());

    const Value res =
        binaryOperationFloat(*instr.type(), val1, val2, std::divides<>{});

    // Store result
    currentFrame().value(*instr.result()) = res;
}

/* ************************************************************************* */

void Interpreter::evalInstruction(const ir::InstructionRem& instr)
{
    const Value val1 = fetchValue(*instr.value1());
    const Value val2 = fetchValue(*instr.value2());

    const Value res =
        binaryOperation(*instr.type(), val1, val2, std::modulus<>{});

    // Store result
    currentFrame().value(*instr.result()) = res;
}

/* ************************************************************************* */

void Interpreter::evalInstruction(const ir::InstructionCmp& instr)
{
    const Value val1 = fetchValue(*instr.value1());
    const Value val2 = fetchValue(*instr.value2());
    Value res;

    switch (instr.operation())
    {
    case ir::InstructionCmp::Operation::Equal:
        res =
            binaryOperationFloat(*instr.type(), val1, val2, std::equal_to<>{});
        break;
    case ir::InstructionCmp::Operation::NotEqual:
        res = binaryOperationFloat(
            *instr.type(), val1, val2, std::not_equal_to<>{});
        break;
    case ir::InstructionCmp::Operation::GreaterThan:
        res = binaryOperationFloat(*instr.type(), val1, val2, std::greater<>{});
        break;
    case ir::InstructionCmp::Operation::GreaterEqual:
        res = binaryOperationFloat(
            *instr.type(), val1, val2, std::greater_equal<>{});
        break;
    case ir::InstructionCmp::Operation::LessThan:
        res = binaryOperationFloat(*instr.type(), val1, val2, std::less<>{});
        break;
    case ir::InstructionCmp::Operation::LessEqual:
        res = binaryOperationFloat(
            *instr.type(), val1, val2, std::less_equal<>{});
        break;
    }

    // Store result
    currentFrame().value(*instr.result()) = res;
}

/* ************************************************************************* */

void Interpreter::evalInstruction(const ir::InstructionAnd& instr)
{
    const Value val1 = fetchValue(*instr.value1());
    const Value val2 = fetchValue(*instr.value2());
    const Value res =
        binaryOperation(*instr.type(), val1, val2, std::bit_and<>{});

    // Store result
    currentFrame().value(*instr.result()) = res;
}

/* ************************************************************************* */

void Interpreter::evalInstruction(const ir::InstructionOr& instr)
{
    const Value val1 = fetchValue(*instr.value1());
    const Value val2 = fetchValue(*instr.value2());
    const Value res =
        binaryOperation(*instr.type(), val1, val2, std::bit_or<>{});

    // Store result
    currentFrame().value(*instr.result()) = res;
}

/* ************************************************************************* */

void Interpreter::evalInstruction(const ir::InstructionXor& instr)
{
    const Value val1 = fetchValue(*instr.value1());
    const Value val2 = fetchValue(*instr.value2());
    const Value res =
        binaryOperation(*instr.type(), val1, val2, std::bit_xor<>{});

    // Store result
    currentFrame().value(*instr.result()) = res;
}

/* ************************************************************************* */

void Interpreter::evalInstruction(const ir::InstructionBranch& instr)
{
    // Jump to other block
    evalBlock(*instr.block());
}

/* ************************************************************************* */

void Interpreter::evalInstruction(const ir::InstructionBranchCondition& instr)
{
    const Value cond = fetchValue(*instr.condition());

    if (cond.get<bool>())
    {
        evalBlock(*instr.blockTrue());
    }
    else
    {
        evalBlock(*instr.blockFalse());
    }
}

/* ************************************************************************* */

void Interpreter::evalInstruction(const ir::InstructionCall& instr)
{
    Vector<Value> args;
    args.reserve(instr.arguments().size());

    for (auto arg : instr.arguments())
        args.push_back(fetchValue(*arg));

    // Call function
    auto res = call(instr.name(), args);

    // Store result value
    currentFrame().value(*instr.result()) = res;
}

/* ************************************************************************* */

void Interpreter::evalInstruction(const ir::InstructionReturn& instr)
{
    if (m_stack.empty())
        throw Exception("Invalid return instruction");

    // Store result value
    currentFrame().result() = fetchValue(*instr.value());
}

/* ************************************************************************* */

void Interpreter::evalInstruction(const ir::InstructionReturnVoid& instr)
{
    // Nothing
}

/* ************************************************************************* */

} // namespace shard::interpreter

/* ************************************************************************* */

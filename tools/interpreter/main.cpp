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
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <ios>

// Shard
#include "shard/FilePath.hpp"
#include "shard/String.hpp"
#include "shard/StringView.hpp"
#include "shard/Exception.hpp"
#include "shard/ast/Source.hpp"
#include "shard/parser/Parser.hpp"
#include "shard/ir/Module.hpp"
#include "shard/interpreter/Interpreter.hpp"

/* ************************************************************************* */

using namespace shard;

/* ************************************************************************* */

namespace {

/* ************************************************************************* */

/**
 * @brief      Creates an AST.
 *
 * @param      filename  The filename.
 *
 * @return     AST.
 */
#if 0
ast::Source createAst(StringView filename)
{
    String input;
    input.reserve(4096);

    if (filename == "-")
    {
        // Copy standard input to string
        std::copy(
            std::istream_iterator<char>(std::cin >> std::noskipws),
            std::istream_iterator<char>(),
            std::back_inserter(input)
        );
    }
    else
    {
        std::ifstream file{String(filename)};

        if (!file.is_open())
            throw std::runtime_error("file not found: " + String(filename));

        std::copy(
            std::istream_iterator<char>(file >> std::noskipws),
            std::istream_iterator<char>(),
            std::back_inserter(input)
        );

    }

    tokenizer::Source source("");
    tokenizer::Tokenizer tokenizer(source);
    parser::Parser parser(tokenizer);

    return parser.parseSource();
}
#endif

/* ************************************************************************* */

ir::Module createModule()
{
    ir::Module module;

    auto const1 = module.createConstant<ir::ConstInt32>(5);
    auto const2 = module.createConstant<ir::ConstInt32>(3);

    {
        auto main = module.createFunction("main", {});
        auto block = main->createBlock();

        auto add = block->createInstruction<ir::InstructionCall>("add", ir::TypeInt32::instance(), Vector<ViewPtr<ir::Value>>{const1, const2});

        auto print = block->createInstruction<ir::InstructionCall>("print", Vector<ViewPtr<ir::Value>>{add->result()});

        block->createInstruction<ir::InstructionReturnVoid>();
    }

    {
        auto add = module.createFunction("add", ir::TypeInt32::instance(), Vector<ViewPtr<ir::Type>>{ir::TypeInt32::instance(), ir::TypeInt32::instance()});

        auto block = add->createBlock();

        // Result variable
        auto result = block->createInstruction<ir::InstructionAdd>(
            ir::TypeInt32::instance(), add->arg(0), add->arg(1));

        // Return result
        block->createInstruction<ir::InstructionReturn>(
            ir::TypeInt32::instance(), result->result());
    }

    return module;
}

/* ************************************************************************* */

}

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
        //auto ast = createAst(argv[1]);
        auto module = createModule();
        //interpreter::interpret(makeView(ast));

        interpreter::Interpreter interp;
        interp.load(module);
        interp.call("main", {});
    }
    catch (const Exception& e)
    {
        std::cerr << "\033[31mERROR\033[0m: " << e.what() << "" << std::endl;
        return -1;
    }
}

/* ************************************************************************* */

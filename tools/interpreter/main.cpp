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
#include <algorithm>
#include <iterator>
#include <ios>

// Shard
#include "shard/Path.hpp"
#include "shard/String.hpp"
#include "shard/StringView.hpp"
#include "shard/Exception.hpp"
#include "shard/ast/Unit.hpp"
#include "shard/parser/Parser.hpp"
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
UniquePtr<ast::Unit> createAst(StringView filename)
{
    if (filename != "-")
        return parser::Parser(Path(String(filename))).parseUnit();

    String input;
    input.reserve(4096);

    // Copy standard input to string
    std::copy(
        std::istream_iterator<char>(std::cin >> std::noskipws),
        std::istream_iterator<char>(),
        std::back_inserter(input)
    );

    return parser::Parser(moveValue(input)).parseUnit();
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
    if (argc < 2)
    {
        std::cerr << "no input file" << std::endl;
        return -1;
    }

    try
    {
        auto ast = createAst(argv[1]);
        interpreter::interpret(makeView(ast));
    }
    catch (const Exception& e)
    {
        std::cerr << "\033[31mERROR\033[0m: " << e.what() << "" << std::endl;
        return -1;
    }
    catch (...)
    {
        std::cerr << "\033[31mERROR\033[0m: Unknown error" << std::endl;
        return -1;
    }
}

/* ************************************************************************* */

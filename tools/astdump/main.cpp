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
#include <fstream>
#include <ios>
#include <iostream>
#include <iterator>

// Shard
#include "shard/Exception.hpp"
#include "shard/builtin/Parser.hpp"
#include "shard/tokenizer/Source.hpp"
#include "shard/tokenizer/Tokenizer.hpp"

/* ************************************************************************* */

using namespace shard;

/* ************************************************************************* */

namespace {

/* ************************************************************************* */

int printError(const char* msg) noexcept
{
    std::cerr << "\033[31mERROR\033[0m: " << msg << std::endl;
    return -1;
}

/* ************************************************************************* */

} // namespace

/* ************************************************************************* */

/**
 * @brief      Entry function.
 *
 * @param      argc  Number of argument.
 * @param      argv  Arguments.
 *
 * @return     Result code.
 */
int main(int argc, char** argv)
{
    if (argc < 2)
        return printError("no input file");

    try
    {
        std::ifstream file(argv[1]);

        if (!file.is_open())
            return printError("unable to open file");

        auto code = std::string{std::istreambuf_iterator<char>{file},
                                std::istreambuf_iterator<char>{}};

        auto source    = tokenizer::Source{code};
        auto tokenizer = tokenizer::Tokenizer{source};
        auto parser    = builtin::Parser{tokenizer};

        // Parse source
        auto ast = parser.parseSource();

        // Semantic analysis
        ast.analyse();

        ast.dump(std::cout);
    }
    catch (const Exception& err)
    {
        return printError(err.what());
    }
}

/* ************************************************************************* */

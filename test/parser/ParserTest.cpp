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

#include <ostream>

// Google test
#include "gtest/gtest.h"

// Shard
#include "shard/String.hpp"
#include "shard/DynamicArray.hpp"
#include "shard/parser/Parser.hpp"

/* ************************************************************************* */

using namespace shard;
using namespace shard::ast;
using namespace shard::parser;

/* ************************************************************************* */

static void test_impl(
        int line,
        const String& code)
{
    SCOPED_TRACE(code);

    Parser parser(code);

    auto temp = parser.parseModule();
}

/* ************************************************************************* */

#define test(...) test_impl(__LINE__, __VA_ARGS__)

/* ************************************************************************* */

TEST(Parser, basic)
{
    test("throw");
}

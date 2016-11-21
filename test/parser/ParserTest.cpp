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

static void test_exception_impl(int line, const String& code, const String& correct)
{
    SCOPED_TRACE(code);

    try
    {
    	Parser parser(code);

    	auto temp = parser.parseModule();
    }
    catch (TokenizerException& ex)
    {
        ASSERT_EQ(correct, ex.formatMessage());
    }
}

/* ************************************************************************* */

#define test(...) test_impl(__LINE__, __VA_ARGS__)
#define test_exception(...) test_exception_impl(__LINE__, __VA_ARGS__)

/* ************************************************************************* */

TEST(Parser, variable_decl_literal)
{
    test("int a = 10;");
    test("var a = 10;");
    test("char a = 'a';");
    test("bool a = true;");
    test("bool b = false;");
    test("bool c = null;");
    test("float a = 10.1;");
    test("string a = \"abc\";");
    test("auto a = 10;");
}
TEST(Parser, variable_decl_expr)
{
    test("auto a = b;");
    test("auto a = 5 % 1 + (1 + 1) - 5 * 3 / 2;");
    test("auto a = b++;");
    test("auto a = b--;");
    test("auto a = ++b;");
    test("auto a = --b;");
    test("auto a = +b;");
    test("auto a = -b;");
    test("auto a = b.c.d;");
    test("auto a = b();");
    test("auto a = b(1, 2, 3, 4);");
    test("auto a = !b;");
    test("auto a = b[1];");
    test("auto a = b[1, 2, 3];");
    test("auto a = !b.c[1]++;");
    test("auto a = b ? 50 : 20;");
    test("auto a = b == c;");
    test("auto a = b != c;");
    test("auto a = b <= c;");
    test("auto a = b >= c;");
    test("auto a = b < c;");
    test("auto a = b > c;");
}

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
    auto temp = parser.parseUnit();
}

/* ************************************************************************* */

static void test_exception_impl(int line, const String& code)
{
    SCOPED_TRACE(code);

    try
    {
    	Parser parser(code);
    	auto temp = parser.parseUnit();
    }
    catch (ParserException& ex)
    {
        //ASSERT_EQ(correct, ex.formatMessage());
    }
}

/* ************************************************************************* */

#define test(...) test_exception_impl(__LINE__, __VA_ARGS__)
#define test_exception(...) test_exception_impl(__LINE__, __VA_ARGS__)

/* ************************************************************************* */

TEST(Parser, variable_decl_literal)
{
    test("var int a;");
    test("var int a = 10;");
    test("var any a = 10;");
    test("var char a = 'a';");
    test("var bool a = true;");
    test("var bool b = false;");
    test("var bool c = null;");
    test("var float a = 10.1;");
    test("var string a = \"abc\";");
    test("var auto a = 10;");
}
TEST(Parser, variable_decl_expr)
{
    test("var auto a = b;");
    test("var auto a = 5 % 1 + (1 + 1) - 5 * 3 / 2;");
    test("var auto a = b++;");
    test("var auto a = b--;");
    test("var auto a = ++b;");
    test("var auto a = --b;");
    test("var auto a = +b;");
    test("var auto a = -b;");
    test("var auto a = b.c.d;");
    test("var auto a = b();");
    test("var auto a = b(1, 2, 3, 4);");
    test("var auto a = !b;");
    test("var auto a = b[1];");
    test("var auto a = b[1, 2, 3];");
    test("var auto a = !b.c[1]++;");
    test("var auto a = b ? 50 : 20;");
    test("var auto a = b == c;");
    test("var auto a = b != c;");
    test("var auto a = b <= c;");
    test("var auto a = b >= c;");
    test("var auto a = b < c;");
    test("var auto a = b > c;");
}
TEST(Parser, variable_decl_non_primitive)
{
    test("var A a;");
    test("var A a = 0;");
}
TEST(Parser, function_decl)
{
    test(
    "func int main(){return;}"
    );
    test(
    "func int main(var int a, var int b){return a + b;}"
    );
    test(
    "func int main(var char a, var any b){return a + b;}"
    );
    test(
    "func int main(var float a, var string b){return a + b;}"
    );
    test(
    "func int main(var bool a, var auto b){return a + b;}"
    );
    test(
    "func int main(var A a, var B b){return a + b;}"
    );
    test(
    "func int main(var A a = 1, var B b = 2){return a + b;}"
    );
}
TEST(Parser, statements)
{
    test(
    "func int main(){throw 0;}"
    );
    test(
    "func int main(){break;}"
    );
    test(
    "func int main(){continue;}"
    );
    test(
    "func int main(){var int a; {var float b; var string c;}}"
    );
}
TEST(Parser, statement_if)
{
    test(
    "func int main(){var any a; if(a) return a;}"
    );
    test(
    "func int main(){var auto a; var char b; if (a) {return a;}else{return b;}}"
    );
    test(
    "func int main(){var bool a; var int b; if (a) {return a;}else if(b){return b;}}"
    );
}
TEST(Parser, statement_while)
{
    test(
    "ifunc nt main(){var int a; while(true){a++;}}"
    );
    test(
    "func int main(){var int a; do {a++;} while(false);}"
    );
}
TEST(Parser, statement_for)
{
    test(
    "func int main(){for(var int i = 0; i < 0; i++){i++;}}"
    );
    test(
    "func int main(){for(;;){return;}}"
    );
    test(
    "func int main(){for(var int i = 0;;){return;}}"
    );
    test(
    "func int main(){for(;true;){return;}}"
    );
    test(
    "func int main(){var int i; for(;;i++){return;}}"
    );
}
TEST(Parser, statement_switch)
{
    test(
    "func int main(){var int i; switch(i){case 1: return 1; case 2: return 2; default: return 3;}}"
    );
    test(
    "func int main(){var int i; switch(i){case 1: return 1; case 2: return 2;}}"
    );
    test(
    "func int main(){var int i; switch(i){default: return 3;}}"
    );
    test(
    "func int main(){var int i; switch(i){case 1: return 1; default: return 3; case 2: return 2;}}"
    );
    test(
    "func int main(){var int i; switch(i){case 1: var int j = 1; return j; }}"
    );
    test(
    "func int main(){var int i; switch(i){case 1: var int j = 1; return i + j; }}"
    );
    test(
    "func int main(){var int i; switch(i){case 1: { var int j = 1; return i + j;}}}"
    );
    test(
    "func int main(){var int i; switch(i){case 1: var int j = 1; return i + j; default:{ var int j = 1; return i + j;}}}"
    );
}
TEST(Parser, statement_assignment)
{
    test(
    "func int main(){a = b;}"
    );
    test(
    "func int main(){a += b;}"
    );
    test(
    "func int main(){a -= b;}"
    );
    test(
    "func int main(){a *= b;}"
    );
    test(
    "func int main(){a /= b;}"
    );
    test(
    "func int main(){a %= b;}"
    );
}
TEST(Parser, class_decl)
{
    test(
    "class A { var int i = 0; func int main(){return 0;} }"
    );
    test(
    "class A { class B { func int main(){return 0;} } }"
    );
    test(
    "class A { class B { var int a = 0; class C { var int b = 0; func int main(){return a + b;} } } }"
    );
}

/* ************************************************************************* */

TEST(Parser, exception)
{
    
}
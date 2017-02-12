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
    test("int a;");
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
TEST(Parser, variable_decl_non_primitive)
{
    test("A a;");
    test("A a = 0;");
}
TEST(Parser, function_decl)
{
    test(
    "int main(){return;}"
    );
    test(
    "int main(int a, int b){return a + b;}"
    );
    test(
    "int main(char a, var b){return a + b;}"
    );
    test(
    "int main(float a, string b){return a + b;}"
    );
    test(
    "int main(bool a, auto b){return a + b;}"
    );
    test(
    "int main(A a, B b){return a + b;}"
    );
    test(
    "int main(A a = 1, B b = 2){return a + b;}"
    );
}
TEST(Parser, statements)
{
    test(
    "int main(){throw 0;}"
    );
    test(
    "int main(){break;}"
    );
    test(
    "int main(){continue;}"
    );
    test(
    "int main(){int a; {float b;string c;}}"
    );
}
TEST(Parser, statement_if)
{
    test(
    "int main(){var a; if(a) return a;}"
    );
    test(
    "int main(){auto a; char b; if (a) {return a;}else{return b;}}"
    );
    test(
    "int main(){bool a; int b; if (a) {return a;}else if(b){return b;}}"
    );
}
TEST(Parser, statement_while)
{
    test(
    "int main(){int a; while(true){a++;}}"
    );
    test(
    "int main(){int a; do {a++;} while(false);}"
    );
}
TEST(Parser, statement_for)
{
    test(
    "int main(){for(int i = 0; i < 0; i++){i++;}}"
    );
    test(
    "int main(){for(;;){return;}}"
    );
    test(
    "int main(){for(int i = 0;;){return;}}"
    );
    test(
    "int main(){for(;true;){return;}}"
    );
    test(
    "int main(){int i; for(;;i++){return;}}"
    );
}
TEST(Parser, statement_switch)
{
    test(
    "int main(){int i; switch(i){case 1: return 1; case 2: return 2; default: return 3;}}"
    );
    test(
    "int main(){int i; switch(i){case 1: return 1; case 2: return 2;}}"
    );
    test(
    "int main(){int i; switch(i){default: return 3;}}"
    );
    test(
    "int main(){int i; switch(i){case 1: return 1; default: return 3; case 2: return 2;}}"
    );
    test(
    "int main(){int i; switch(i){case 1: int j = 1; return j; }}"
    );
    test(
    "int main(){int i; switch(i){case 1: int j = 1; return i + j; }}"
    );
    test(
    "int main(){int i; switch(i){case 1: { int j = 1; return i + j;}}}"
    );
    test(
    "int main(){int i; switch(i){case 1: int j = 1; return i + j; default:{ int j = 1; return i + j;}}}"
    );
}
TEST(Parser, statement_assignment)
{
    test(
    "int main(){a = b;}"
    );
    test(
    "int main(){a += b;}"
    );
    test(
    "int main(){a -= b;}"
    );
    test(
    "int main(){a *= b;}"
    );
    test(
    "int main(){a /= b;}"
    );
    test(
    "int main(){a %= b;}"
    );
}
TEST(Parser, class_decl)
{
    test(
    "class A { int i = 0; int main(){return 0;} }"
    );
    test(
    "class A { class B { int main(){return 0;} } }"
    );
    test(
    "class A { class B { int a = 0; class C { int b = 0; int main(){return a + b;} } } }"
    );
}

/* ************************************************************************* */

TEST(Parser, exception)
{
    
}
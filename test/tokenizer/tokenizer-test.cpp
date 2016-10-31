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

// Google test
#include "gtest/gtest.h"

// Shard
#include "shard/String.hpp"
#include "shard/DynamicArray.hpp"
#include "shard/tokenizer/Tokenizer.hpp"

/* ************************************************************************* */

using namespace shard;
using namespace shard::tokenizer;

/* ************************************************************************* */

static void test_impl(
        int line,
        const String& code,
        const DynamicArray<Token>& correct)
{
    SCOPED_TRACE(code);

    // Test using while

    Tokenizer tokenizer(code);
    DynamicArray<Token> result;
    result.reserve(correct.size());
    while (!tokenizer.isEof())
    {
        result.push_back(tokenizer.extract());
    }

    ASSERT_EQ(correct.size(), result.size());

    for (int i = 0; i < correct.size(); ++i)
    {
        ASSERT_EQ(correct[i], result[i]) << result[i];
    }

    // Test using Range-For

    DynamicArray<Token> resultIt;
    resultIt.reserve(correct.size());
    for (auto&& x : Tokenizer(code))
    {
        resultIt.push_back(x);
    }

    ASSERT_EQ(correct.size(), resultIt.size());

    for (int i = 0; i < correct.size(); ++i)
    {
        ASSERT_EQ(correct[i], resultIt[i]) << resultIt[i];
    }
}

/* ************************************************************************* */

static void test_invalid_impl(int line, const String& code)
{
    SCOPED_TRACE(code);

    ASSERT_THROW
    (
        Tokenizer tokenizer(code);
        while (!tokenizer.isEof())
        {
            tokenizer.toss();
        },
        TokenizerException
    );
}

/* ************************************************************************* */

static void test_location_impl(int line, const String& code, const DynamicArray<SourceLocation>& correct)
{
    SCOPED_TRACE(code);

    DynamicArray<SourceLocation> result;
    result.reserve(correct.size());
    for (auto&& x : Tokenizer(code))
    {
        result.push_back(x.getLocation());
    }

    ASSERT_EQ(correct.size(), result.size());

    for (int i = 0; i < correct.size(); ++i)
    {
        ASSERT_EQ(correct[i].getLine(), result[i].getLine());
        ASSERT_EQ(correct[i].getColumn(), result[i].getColumn());
    }
}

/* ************************************************************************* */

static void test_exception_impl(int line, const String& code, const String& correct)
{
    SCOPED_TRACE(code);

    try
    {
        DynamicArray<SourceLocation> result;
        result.reserve(correct.size());
        for (auto&& x : Tokenizer(code))
        {
            result.push_back(x.getLocation());
        }
    }
    catch (TokenizerException& ex)
    {
        ASSERT_EQ(correct, ex.what());
    }
}

/* ************************************************************************* */
#define test(...) test_impl(__LINE__, __VA_ARGS__)
#define test_invalid(...) test_invalid_impl(__LINE__, __VA_ARGS__)
#define test_location(...) test_location_impl(__LINE__, __VA_ARGS__)
#define test_exception(...) test_exception_impl(__LINE__, __VA_ARGS__)

/* ************************************************************************* */

TEST(Tokenizer, basic)
{
    test("", {});
    test(".", {Token(TokenType::Period)});
    test(",.-", {Token(TokenType::Comma), Token(TokenType::Period), Token(TokenType::Minus)});
}
TEST(Tokenizer, identifier)
{
    test(
        ",.-jhdba{}&\\)^/",
        {Token(TokenType::Comma), Token(TokenType::Period), Token(TokenType::Minus), Token::Identifier("jhdba"),
        Token(TokenType::BraceO), Token(TokenType::BraceC), Token(TokenType::Amp), Token(TokenType::Backslash),
        Token(TokenType::ParenC), Token(TokenType::Caret), Token(TokenType::Slash)}
    );
    test(
        "+   blabla17_fcr8_4",
        {Token(TokenType::Plus), Token::Identifier("blabla17_fcr8_4")}
    );
    test(
        "+ __bla17_8-",
        {Token(TokenType::Plus), Token::Identifier("__bla17_8"), Token(TokenType::Minus)}
    );
    test(
        "+ bla17_8_",
        {Token(TokenType::Plus), Token::Identifier("bla17_8_")}
    );
}
TEST(Tokenizer, string)
{
    test(
        "-\" \"",
        {Token(TokenType::Minus), Token::StringLiteral(" ")}
    );
    test(
        "-\"teajnd/jansjda\"ide",
        {Token(TokenType::Minus), Token::StringLiteral("teajnd/jansjda"), Token::Identifier("ide")}
    );
    test(
        String("\"\0\"", 3),
        {Token::StringLiteral(String("\0", 1))}
    );
    test(
        String("\"\n\r\t\0\"", 6),
        {Token::StringLiteral(String("\n\r\t\0", 4))}
    );
    test(
        "\"\n\r\t\\\"\"",
        {Token::StringLiteral("\n\r\t\"")}
    );
    test_invalid("\"\n\r\t\0\\");
    test_invalid("bla\"bla");
}
TEST(Tokenizer, floats)
{
    test(
        "3.1415926538",
        {Token::FloatLiteral(3.1415926538)}
    );
    test(
        "00003.1415926538",
        {Token::FloatLiteral(3.1415926538)}
    );
    test(
        "3.1415926538+1.4",
        {Token::FloatLiteral(3.1415926538), Token(TokenType::Plus), Token::FloatLiteral(1.4)}
    );
    test(
        "a 3.1415926538+",
        {Token::Identifier("a"), Token::FloatLiteral(3.1415926538), Token(TokenType::Plus)}
    );
    test(
        "a 3.1415926538+1.4",
        {Token::Identifier("a"), Token::FloatLiteral(3.1415926538), Token(TokenType::Plus), Token::FloatLiteral(1.4)}
    );
    test(
        "3.1415926538e10",
        {Token::FloatLiteral(3.1415926538e10)}
    );
    test(
        "3.1415926538e-10",
        {Token::FloatLiteral(3.1415926538e-10)}
    );
    test("3.1415926538e+10",
        {Token::FloatLiteral(3.1415926538e+10)}
    );
    test_invalid("3.");
    test_invalid("3.1415926538e");
    test_invalid("3.1415926538e-");
    test_invalid("3.1415926538e+");
}
TEST(Tokenizer, chars)
{
    test(
        "+-'z'",
        {Token(TokenType::Plus), Token(TokenType::Minus), Token::CharLiteral('z')}
    );
    test(
        "'\\n''\\r''\\0'",
        {Token::CharLiteral('\n'), Token::CharLiteral('\r'), Token::CharLiteral('\0')}
    );
    test(
        "'a'+'b'",
        {Token::CharLiteral('a'), Token(TokenType::Plus), Token::CharLiteral('b')}
    );
    test_invalid("'\n'");
    test_invalid("'abc'");
    test_invalid("'a");
}
TEST(Tokenizer, ints)
{
    test(
        "0",
        {Token::IntLiteral(0)}
    );
    test(
        "0;",
        {Token::IntLiteral(0), Token(TokenType::Semicolon)}
    );
    test(
        "a123+123+123a",
        {Token::Identifier("a123"), Token(TokenType::Plus), Token::IntLiteral(123), Token(TokenType::Plus),
        Token::IntLiteral(123), Token::Identifier("a")}
    );
    test(
        "0000321",
        {Token::IntLiteral(321)}
    );
    test(
        "a3.1415926538+1.4",
        {Token::Identifier("a3"), Token(TokenType::Period),
        Token::IntLiteral(1415926538), Token(TokenType::Plus), Token::FloatLiteral(1.4)}
    );
}
TEST(Tokenizer, keywords)
{
    test(
        "for float null while",
        {Token::Keyword(KeywordType::For), Token::Keyword(KeywordType::Float),
        Token::Keyword(KeywordType::Null), Token::Keyword(KeywordType::While)}
    );
    test(
        "for (int i = 0; i <= 10; i++)",
        {Token::Keyword(KeywordType::For), Token(TokenType::ParenO), Token::Keyword(KeywordType::Int), Token::Identifier("i"),
        Token(TokenType::Equal), Token::IntLiteral(0), Token(TokenType::Semicolon), Token::Identifier("i"),
        Token(TokenType::LessEqual), Token::IntLiteral(10), Token(TokenType::Semicolon), Token::Identifier("i"),
        Token(TokenType::PlusPlus), Token(TokenType::ParenC)}
    );
    test(
        "while(true){[]}",
        {Token::Keyword(KeywordType::While), Token(TokenType::ParenO), Token::Keyword(KeywordType::True), Token(TokenType::ParenC),
        Token(TokenType::BraceO), Token(TokenType::SquareO), Token(TokenType::SquareC), Token(TokenType::BraceC)}
    );
    test(
        "string a = \"bla\";",
        {Token::Keyword(KeywordType::String), Token::Identifier("a"), Token(TokenType::Equal),
        Token::StringLiteral("bla"), Token(TokenType::Semicolon)}
    );
    test(
        "throw Exception& ex;",
        {Token::Keyword(KeywordType::Throw), Token::Identifier("Exception"),
        Token(TokenType::Amp), Token::Identifier("ex"), Token(TokenType::Semicolon)}
    );
}
TEST(Tokenizer, comments)
{
    test(
        "123//comment\n123",
        {Token::IntLiteral(123), Token::CommentLine("comment"), Token::IntLiteral(123)}
    );
    test(
        "123/*dadjabj\ndadbhj\rda*/123",
        {Token::IntLiteral(123), Token::CommentBlock("dadjabj\ndadbhj\rda"), Token::IntLiteral(123)}
    );
    test(
        "123//comment\r123",
        {Token::IntLiteral(123), Token::CommentLine("comment"), Token::IntLiteral(123)}
    );
    test(
        "123//comme/nt\r123",
        {Token::IntLiteral(123), Token::CommentLine("comme/nt"), Token::IntLiteral(123)}
    );
    test(
        "123/*comme*nt\r123*/123",
        {Token::IntLiteral(123), Token::CommentBlock("comme*nt\r123"), Token::IntLiteral(123)}
    );
    test(
        "123/*comme*nt\r123123",
        {Token::IntLiteral(123), Token::CommentBlock("comme*nt\r123123")}
    );
    test(
        "123//comme*nt",
        {Token::IntLiteral(123), Token::CommentLine("comme*nt")}
    );
}
TEST(Tokenizer, strings_utf)
{
    test(
        "\"blačššžžý\"",
        {Token::StringLiteral("blačššžžý")}
    );
}
TEST(Tokenizer, chars_utf)
{
    test(
        "'š'",
        {Token::CharLiteral(0x0161)}
    );
    test(
        "'č'",
        {Token::CharLiteral(0x010D)}
    );
    test(
        "'ř'",
        {Token::CharLiteral(0x0159)}
    );
    test(
        "'𠜎'",
        {Token::CharLiteral(0x2070e)}
    );
    test(
        "'Ϯ'",
        {Token::CharLiteral(0x03EE)}
    );
    test(
        "'š''𠜎''č''ř''Ϯ'",
        {Token::CharLiteral(0x0161),
        Token::CharLiteral(0x2070e),
        Token::CharLiteral(0x010D),
        Token::CharLiteral(0x0159),
        Token::CharLiteral(0x03EE)}
    );
}
TEST(Tokenizer, operators_multichar)
{
    test(
        "&&=||=||&&!=<<<<=>>=",
        {Token(TokenType::AmpAmpEqual), Token(TokenType::PipePipeEqual), Token(TokenType::PipePipe),
        Token(TokenType::AmpAmp), Token(TokenType::ExclaimEqual), Token(TokenType::LessLess),
        Token(TokenType::LessLessEqual), Token(TokenType::GreaterGreaterEqual)}
    );
    test(
        "&&=||=||&&!=<<<<=>>=&&&",
        {Token(TokenType::AmpAmpEqual), Token(TokenType::PipePipeEqual), Token(TokenType::PipePipe),
        Token(TokenType::AmpAmp), Token(TokenType::ExclaimEqual), Token(TokenType::LessLess),
        Token(TokenType::LessLessEqual), Token(TokenType::GreaterGreaterEqual),
        Token(TokenType::AmpAmp), Token(TokenType::Amp)}
    );
}
TEST(Tokenizer, ints_bin)
{
    test(
        "0b1111",
        {Token::IntLiteral(0b1111)}
    );
    test(
        "0B0",
        {Token::IntLiteral(0b0)}
    );
    test(
        "0b10111011011011",
        {Token::IntLiteral(0b10111011011011)}
    );
}
TEST(Tokenizer, ints_hex)
{
    test(
        "0XFF",
        {Token::IntLiteral(255)}
    );
    test(
        "0x00FF",
        {Token::IntLiteral(255)}
    );
}
TEST(Tokenizer, ints_oct)
{
    test(
        "0o123456",
        {Token::IntLiteral(0123456)}
    );
    test(
        "0000321",
        {Token::IntLiteral(321)}
    );
    test(
        "0O571",
        {Token::IntLiteral(0571)}
    );
}

/* ************************************************************************* */

TEST(Tokenizer, location)
{
    test_location(
        "0o123456,.\"hhh\"ide",
        {{1, 1}, {1, 9}, {1, 10}, {1, 11}, {1, 16}}
    );
    test_location(
        "\n\n,.\"hhh\"ide",
        {{3, 1}, {3, 2}, {3, 3}, {3, 8}}
    );
    test_location(
        "\n\r\r\n0o123456,.\r\n\"hhh\"ide",
        {{4, 1}, {4, 9}, {4, 10}, {5, 1}, {5, 6}}
    );
    test_location(
        "0o123456,./*\"hhh\"*/ide",
        {{1, 1}, {1, 9}, {1, 10}, {1, 11}, {1, 20}}
    );
    test_location(
        "0o12/*34\n\r\n56*/,.\"hhh\"\ride",
        {{1, 1}, {1, 5}, {3, 5}, {3, 6}, {3, 7}, {4, 1}}
    );
    test_location(
        "0o1\n234//56\n,//.\"hhh\"ide",
        {{1, 1}, {2, 1}, {2, 4}, {3, 1}, {3, 2}}
    );
}

/* ************************************************************************* */

TEST(Tokenizer, exception)
{
    test_exception(
        "154.+",
        "Expected number at 1:5."
    );
}

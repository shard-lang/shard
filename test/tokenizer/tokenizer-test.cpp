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

static void test_impl(
        int line,
        const String& code,
        const DynamicArray<Token>& correct)
{
    SCOPED_TRACE(code);

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

static void test_invalid_impl(int line, const String& code)
{
    SCOPED_TRACE(code);

    ASSERT_THROW
    (
        Tokenizer tokenizer(code);
        while (!tokenizer.isEof())
        {
            tokenizer.next();
        },
        TokenizerException
    );

}

#define test(...) test_impl(__LINE__, __VA_ARGS__)
#define test_invalid(...) test_invalid_impl(__LINE__, __VA_ARGS__)

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
        {Token(TokenType::Comma), Token(TokenType::Period), Token(TokenType::Minus), Token("jhdba"),
        Token(TokenType::BraceO), Token(TokenType::BraceC), Token(TokenType::Amp), Token(TokenType::Backslash),
        Token(TokenType::ParenC), Token(TokenType::Caret), Token(TokenType::Slash)}
    );
    test(
        "+   blabla17_fcr8_4",
        {Token(TokenType::Plus), Token("blabla17_fcr8_4")}
    );
    test(
        "+ __bla17_8-",
        {Token(TokenType::Plus), Token("__bla17_8"), Token(TokenType::Minus)}
    );
    test(
        "+ bla17_8_",
        {Token(TokenType::Plus), Token("bla17_8_")}
    );
}
TEST(Tokenizer, string)
{
    test(
        "-\" \"",
        {Token(TokenType::Minus), Token(TokenType::String, " ")}
    );
    test(
        "-\"teajnd/jansjda\"ide",
        {Token(TokenType::Minus), Token(TokenType::String, "teajnd/jansjda"), Token("ide")}
    );
    test(
        String("\"\0\"", 3),
        {Token(TokenType::String, String("\0", 1))}
    );
    test(
        String("\"\n\r\t\0\"", 6),
        {Token(TokenType::String, String("\n\r\t\0", 4))}
    );
    test(
        "\"\n\r\t\\\"\"",
        {Token(TokenType::String, "\n\r\t\"")}
    );
    test_invalid("\"\n\r\t\0\\");
    test_invalid("bla\"bla");
}
TEST(Tokenizer, floats)
{
    test(
        "3.1415926538",
        {Token(3.1415926538)}
    );
    test(
        "00003.1415926538",
        {Token(3.1415926538)}
    );
    test(
        "3.1415926538+1.4",
        {Token(3.1415926538), Token(TokenType::Plus), Token(1.4)}
    );
    test(
        "a 3.1415926538+",
        {Token("a"), Token(3.1415926538), Token(TokenType::Plus)}
    );
    test(
        "a 3.1415926538+1.4",
        {Token("a"), Token(3.1415926538), Token(TokenType::Plus), Token(1.4)}
    );
    test(
        "3.1415926538e10",
        {Token(3.1415926538e10)}
    );
    test(
        "3.1415926538e-10",
        {Token(3.1415926538e-10)}
    );
    test("3.1415926538e+10",
        {Token(3.1415926538e+10)}
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
        {Token(TokenType::Plus), Token(TokenType::Minus), Token('z')}
    );
    test(
        "'\\n''\\r''\\0'",
        {Token('\n'), Token('\r'), Token('\0')}
    );
    test(
        "'a'+'b'",
        {Token('a'), Token(TokenType::Plus), Token('b')}
    );
    test_invalid("'abc'");
    test_invalid("'a");
}
TEST(Tokenizer, ints)
{
    test(
        "a123+123+123a",
        {Token("a123"), Token(TokenType::Plus), Token(123l), Token(TokenType::Plus), Token(123l), Token("a")}
    );
    test(
        "0000321",
        {Token(321l)}
    );
    test(
        "a3.1415926538+1.4",
        {Token("a3"), Token(TokenType::Period), Token(1415926538l), Token(TokenType::Plus), Token(1.4)}
    );
}
TEST(Tokenizer, keywords)
{
    test(
        "for float null while",
        {Token(KeywordType::For), Token(KeywordType::Float), Token(KeywordType::Null), Token(KeywordType::While)}
    );
    test(
        "for (int i = 0; i <= 10; i++)",
        {Token(KeywordType::For), Token(TokenType::ParenO), Token(KeywordType::Int), Token("i"),
        Token(TokenType::Equal), Token(0l), Token(TokenType::Semicolon), Token("i"),
        Token(TokenType::LessEqual), Token(10l), Token(TokenType::Semicolon), Token("i"),
        Token(TokenType::PlusPlus), Token(TokenType::ParenC)}
    );
    test(
        "while(true){[]}",
        {Token(KeywordType::While), Token(TokenType::ParenO), Token(KeywordType::True), Token(TokenType::ParenC),
        Token(TokenType::BraceO), Token(TokenType::SquareO), Token(TokenType::SquareC), Token(TokenType::BraceC)}
    );
    test(
        "string a = \"bla\";",
        {Token(KeywordType::String), Token("a"), Token(TokenType::Equal),
        Token(TokenType::String, "bla"), Token(TokenType::Semicolon)}
    );
    test(
        "throw Exception& ex;",
        {Token(KeywordType::Throw), Token("Exception"), Token(TokenType::Amp), Token("ex"), Token(TokenType::Semicolon)}
    );
}
TEST(Tokenizer, comments)
{
    test(
        "123//comment\n123",
        {Token(123l), Token(123l)}
    );
    test(
        "123/*dadjabj\ndadbhj\rda*/123",
        {Token(123l), Token(123l)}
    );
    test(
        "123//comment\r123",
        {Token(123l), Token(123l)}
    );
}
TEST(Tokenizer, strings_utf)
{
    test(
        "\"blačššžžý\"",
        {Token(TokenType::String, "blačššžžý")}
    );
}
TEST(Tokenizer, chars_utf)
{
    test(
        "'š'",
        {Token(0b1100'0101'1010'0001)}
    );
    test(
        "'č'",
        {Token(0b1100'0100'1000'1101)}
    );
    test(
        "'ř'",
        {Token(0b1100'0101'1001'1001)}
    );
    test(
        "'𠜎'",
        {Token((int32_t)0b1111'0000'1010'0000'1001'1100'1000'1110)}
    );
    test(
        "'Ϯ'",
        {Token(0b1100'1111'1010'1110)}
    );
    test(
        "'š''𠜎''č''ř''Ϯ'",
        {Token(0b1100'0101'1010'0001),
        Token((int32_t)0b1111'0000'1010'0000'1001'1100'1000'1110),
        Token(0b1100'0100'1000'1101),
        Token(0b1100'0101'1001'1001),
        Token(0b1100'1111'1010'1110)}
    );
}
TEST(Tokenizer, operators_multichar)
{
    test(
        "&&=||=||&&!=<<<<=>>=",
        {Token(TokenType::AmpAmpEqual), Token(TokenType::PipePipeEqual), Token(TokenType::PipePipe),
        Token(TokenType::AmpAmp), Token(TokenType::EMarkEqual), Token(TokenType::LessLess),
        Token(TokenType::LessLessEqual), Token(TokenType::GreaterGreaterEqual)}
    );
    test(
        "&&=||=||&&!=<<<<=>>=&&&",
        {Token(TokenType::AmpAmpEqual), Token(TokenType::PipePipeEqual), Token(TokenType::PipePipe),
        Token(TokenType::AmpAmp), Token(TokenType::EMarkEqual), Token(TokenType::LessLess),
        Token(TokenType::LessLessEqual), Token(TokenType::GreaterGreaterEqual),
        Token(TokenType::AmpAmp), Token(TokenType::Amp)}
    );
}
TEST(Tokenizer, ints_bin)
{
    test(
        "0b1111",
        {Token(15l)}
    );
    test(
        "0B0",
        {Token(0l)}
    );
    test(
        "0b10111011011011",
        {Token(11995l)}
    );
}
TEST(Tokenizer, ints_hex)
{
    test(
        "0XFF",
        {Token(255l)}
    );
    test(
        "0x00FF",
        {Token(255l)}
    );
}
TEST(Tokenizer, ints_oct)
{
    test(
        "0o123456",
        {Token(42798l)}
    );
    test(
        "0000321",
        {Token(321l)}
    );
    test(
        "0O571",
        {Token(377l)}
    );
}
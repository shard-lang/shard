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
#include "shard/tokenizer/Tokenizer.hpp"
#include "shard/tokenizer/exceptions.hpp"

/* ************************************************************************* */

namespace shard {

/* ************************************************************************* */

inline std::ostream& operator<<(std::ostream& os, const SourceLocation& loc)
{
    return os << loc.line() << ":" << loc.column();
}

/* ************************************************************************* */

namespace tokenizer {

/* ************************************************************************* */

inline std::ostream& operator<<(std::ostream& os, TokenType type)
{
    switch (type)
    {
    case TokenType::Unknown: return os << "Unknown";
    case TokenType::Identifier: return os << "Identifier";
    case TokenType::StringLiteral: return os << "StringLiteral";
    case TokenType::CharLiteral: return os << "CharLiteral";
    case TokenType::NumberLiteral: return os << "NumberLiteral";
    case TokenType::Comment: return os << "Comment";
    case TokenType::WhiteSpace: return os << "WhiteSpace";
    case TokenType::EndOfLine: return os << "EndOfLine";
    case TokenType::Other: return os << "Other";
    }
};

/* ************************************************************************* */

} // namespace tokenizer

/* ************************************************************************* */

} // namespace shard

/* ************************************************************************* */

using namespace shard;
using namespace shard::tokenizer;

/* ************************************************************************* */

TEST(Tokenizer, empty)
{
    Source source("");
    Tokenizer tokenizer(source);

    ASSERT_TRUE(tokenizer.isEmpty());
    auto token = tokenizer.tokenize();
    EXPECT_FALSE(token);
}

/* ************************************************************************* */

TEST(Tokenizer, identifier)
{
    {
        Source source("hello");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::Identifier);
        EXPECT_EQ(token->value(), "hello");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }

    {
        Source source("HelloWorld");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::Identifier);
        EXPECT_EQ(token->value(), "HelloWorld");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }

    {
        Source source("Hello_World_01");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::Identifier);
        EXPECT_EQ(token->value(), "Hello_World_01");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }

    {
        Source source("_0123456");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::Identifier);
        EXPECT_EQ(token->value(), "_0123456");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }

    {
        Source source("a_0_123456zi");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::Identifier);
        EXPECT_EQ(token->value(), "a_0_123456zi");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }
}

/* ************************************************************************* */

TEST(Tokenizer, number)
{
    {
        Source source("0");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::NumberLiteral);
        EXPECT_EQ(token->value(), "0");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }

    {
        Source source("12345");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::NumberLiteral);
        EXPECT_EQ(token->value(), "12345");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }

    {
        Source source("0x123456");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::NumberLiteral);
        EXPECT_EQ(token->value(), "0x123456");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }

    {
        Source source("0b10011_01001");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::NumberLiteral);
        EXPECT_EQ(token->value(), "0b10011_01001");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }
}

/* ************************************************************************* */

TEST(Tokenizer, string)
{
    {
        Source source("\"\"");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::StringLiteral);
        EXPECT_EQ(token->value(), "");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }

    {
        Source source("\"Hello World!\"");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::StringLiteral);
        EXPECT_EQ(token->value(), "Hello World!");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }

    {
        Source source("\"Hello\\n\\tWorld!\\\"quote\'\"");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::StringLiteral);
        EXPECT_EQ(token->value(), "Hello\n\tWorld!\"quote\'");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }

    // Unterminated
    {
        Source source("\"Hell");
        Tokenizer tokenizer(source);

        EXPECT_THROW(tokenizer.tokenize(), TokenizerError);
    }
}

/* ************************************************************************* */

TEST(Tokenizer, character)
{
    {
        Source source("'A'");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::CharLiteral);
        EXPECT_EQ(token->value(), "A");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }

    {
        Source source("'\\n'");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::CharLiteral);
        EXPECT_EQ(token->value(), "\n");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }

    {
        Source source("'\\t'");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::CharLiteral);
        EXPECT_EQ(token->value(), "\t");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }

    {
        Source source("'\\''");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::CharLiteral);
        EXPECT_EQ(token->value(), "'");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }

    {
        Source source("'\\\\'");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::CharLiteral);
        EXPECT_EQ(token->value(), "\\");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }

    {
        Source source("'\\r'");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::CharLiteral);
        EXPECT_EQ(token->value(), "\r");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }

    {
        Source source("'\\n'");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::CharLiteral);
        EXPECT_EQ(token->value(), "\n");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }

    {
        Source source("'\\0'");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::CharLiteral);
        EXPECT_EQ(token->value(), String("\0", 1));
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }

    // Unsupported escape
    {
        Source source("'\\a'");
        Tokenizer tokenizer(source);

        EXPECT_THROW(tokenizer.tokenize(), TokenizerError);
    }

    // Empty
    {
        Source source("''");
        Tokenizer tokenizer(source);

        EXPECT_THROW(tokenizer.tokenize(), TokenizerError);
    }

    // Unterminated
    {
        Source source("'");
        Tokenizer tokenizer(source);

        EXPECT_THROW(tokenizer.tokenize(), TokenizerError);
    }

    // Unterminated
    {
        Source source("\'a");
        Tokenizer tokenizer(source);

        EXPECT_THROW(tokenizer.tokenize(), TokenizerError);
    }
}

/* ************************************************************************* */

TEST(Tokenizer, comment)
{
    {
        Source source("// Hello World\n");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::Comment);
        EXPECT_EQ(token->value(), " Hello World");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }

    {
        Source source("// Hello World");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::Comment);
        EXPECT_EQ(token->value(), " Hello World");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }

    {
        Source source("/* Hello\nWorld */");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::Comment);
        EXPECT_EQ(token->value(), " Hello\nWorld ");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }

    {
        Source source("/* Hello\nWorld");
        Tokenizer tokenizer(source);

        // Unterminated string
        EXPECT_THROW(tokenizer.tokenize(), TokenizerError);
    }
}

/* ************************************************************************* */

TEST(Tokenizer, whitespace)
{
    {
        Source source(" ");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::WhiteSpace);
        EXPECT_EQ(token->value(), " ");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }

    {
        Source source("  \t \t   ");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::WhiteSpace);
        EXPECT_EQ(token->value(), "  \t \t   ");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }
}

/* ************************************************************************* */

TEST(Tokenizer, endOfLine)
{
    {
        Source source("\n");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::EndOfLine);
        EXPECT_EQ(token->value(), "\n");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }

    {
        Source source("\r\n");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::EndOfLine);
        EXPECT_EQ(token->value(), "\n");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }

    {
        Source source("\r\n\n\n");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::EndOfLine);
        EXPECT_EQ(token->value(), "\n");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::EndOfLine);
        EXPECT_EQ(token->value(), "\n");
        EXPECT_EQ(token->location(), (SourceLocation{2, 1}));

        token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::EndOfLine);
        EXPECT_EQ(token->value(), "\n");
        EXPECT_EQ(token->location(), (SourceLocation{3, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }
}

/* ************************************************************************* */

TEST(Tokenizer, other)
{
    {
        Source source(";");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::Other);
        EXPECT_EQ(token->value(), ";");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }

    {
        Source source("(");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::Other);
        EXPECT_EQ(token->value(), "(");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }
}

/* ************************************************************************* */

TEST(Tokenizer, multiple)
{
    {
        Source source("var value = 5;\nvalue += 10;");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::Identifier);
        EXPECT_EQ(token->value(), "var");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::WhiteSpace);
        EXPECT_EQ(token->value(), " ");
        EXPECT_EQ(token->location(), (SourceLocation{1, 4}));

        token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::Identifier);
        EXPECT_EQ(token->value(), "value");
        EXPECT_EQ(token->location(), (SourceLocation{1, 5}));

        token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::WhiteSpace);
        EXPECT_EQ(token->value(), " ");
        EXPECT_EQ(token->location(), (SourceLocation{1, 10}));

        token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::Other);
        EXPECT_EQ(token->value(), "=");
        EXPECT_EQ(token->location(), (SourceLocation{1, 11}));

        token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::WhiteSpace);
        EXPECT_EQ(token->value(), " ");
        EXPECT_EQ(token->location(), (SourceLocation{1, 12}));

        token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::NumberLiteral);
        EXPECT_EQ(token->value(), "5");
        EXPECT_EQ(token->location(), (SourceLocation{1, 13}));

        token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::Other);
        EXPECT_EQ(token->value(), ";");
        EXPECT_EQ(token->location(), (SourceLocation{1, 14}));

        token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::EndOfLine);
        EXPECT_EQ(token->value(), "\n");
        EXPECT_EQ(token->location(), (SourceLocation{1, 15}));

        token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::Identifier);
        EXPECT_EQ(token->value(), "value");
        EXPECT_EQ(token->location(), (SourceLocation{2, 1}));

        token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::WhiteSpace);
        EXPECT_EQ(token->value(), " ");
        EXPECT_EQ(token->location(), (SourceLocation{2, 6}));

        token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::Other);
        EXPECT_EQ(token->value(), "+");
        EXPECT_EQ(token->location(), (SourceLocation{2, 7}));

        token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::Other);
        EXPECT_EQ(token->value(), "=");
        EXPECT_EQ(token->location(), (SourceLocation{2, 8}));

        token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::WhiteSpace);
        EXPECT_EQ(token->value(), " ");
        EXPECT_EQ(token->location(), (SourceLocation{2, 9}));

        token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::NumberLiteral);
        EXPECT_EQ(token->value(), "10");
        EXPECT_EQ(token->location(), (SourceLocation{2, 10}));

        token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::Other);
        EXPECT_EQ(token->value(), ";");
        EXPECT_EQ(token->location(), (SourceLocation{2, 12}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }

    {
        Source source("(");
        Tokenizer tokenizer(source);

        auto token = tokenizer.tokenize();
        ASSERT_TRUE(token);
        EXPECT_EQ(token->type(), TokenType::Other);
        EXPECT_EQ(token->value(), "(");
        EXPECT_EQ(token->location(), (SourceLocation{1, 1}));

        token = tokenizer.tokenize();
        EXPECT_FALSE(token);
    }
}

/* ************************************************************************* */

TEST(Tokenizer, tokenize)
{
    {
        Source source("var value = 5;\nvalue += 10;");

        Vector<Token> tokens;
        tokenize(source.begin(), source.end(), std::back_inserter(tokens));

        ASSERT_EQ(tokens.size(), 16);

        EXPECT_EQ(tokens[0].type(), TokenType::Identifier);
        EXPECT_EQ(tokens[0].value(), "var");
        EXPECT_EQ(tokens[0].location(), (SourceLocation{1, 1}));

        EXPECT_EQ(tokens[1].type(), TokenType::WhiteSpace);
        EXPECT_EQ(tokens[1].value(), " ");
        EXPECT_EQ(tokens[1].location(), (SourceLocation{1, 4}));

        EXPECT_EQ(tokens[2].type(), TokenType::Identifier);
        EXPECT_EQ(tokens[2].value(), "value");
        EXPECT_EQ(tokens[2].location(), (SourceLocation{1, 5}));

        EXPECT_EQ(tokens[3].type(), TokenType::WhiteSpace);
        EXPECT_EQ(tokens[3].value(), " ");
        EXPECT_EQ(tokens[3].location(), (SourceLocation{1, 10}));

        EXPECT_EQ(tokens[4].type(), TokenType::Other);
        EXPECT_EQ(tokens[4].value(), "=");
        EXPECT_EQ(tokens[4].location(), (SourceLocation{1, 11}));

        EXPECT_EQ(tokens[5].type(), TokenType::WhiteSpace);
        EXPECT_EQ(tokens[5].value(), " ");
        EXPECT_EQ(tokens[5].location(), (SourceLocation{1, 12}));

        EXPECT_EQ(tokens[6].type(), TokenType::NumberLiteral);
        EXPECT_EQ(tokens[6].value(), "5");
        EXPECT_EQ(tokens[6].location(), (SourceLocation{1, 13}));

        EXPECT_EQ(tokens[7].type(), TokenType::Other);
        EXPECT_EQ(tokens[7].value(), ";");
        EXPECT_EQ(tokens[7].location(), (SourceLocation{1, 14}));

        EXPECT_EQ(tokens[8].type(), TokenType::EndOfLine);
        EXPECT_EQ(tokens[8].value(), "\n");
        EXPECT_EQ(tokens[8].location(), (SourceLocation{1, 15}));

        EXPECT_EQ(tokens[9].type(), TokenType::Identifier);
        EXPECT_EQ(tokens[9].value(), "value");
        EXPECT_EQ(tokens[9].location(), (SourceLocation{2, 1}));

        EXPECT_EQ(tokens[10].type(), TokenType::WhiteSpace);
        EXPECT_EQ(tokens[10].value(), " ");
        EXPECT_EQ(tokens[10].location(), (SourceLocation{2, 6}));

        EXPECT_EQ(tokens[11].type(), TokenType::Other);
        EXPECT_EQ(tokens[11].value(), "+");
        EXPECT_EQ(tokens[11].location(), (SourceLocation{2, 7}));

        EXPECT_EQ(tokens[12].type(), TokenType::Other);
        EXPECT_EQ(tokens[12].value(), "=");
        EXPECT_EQ(tokens[12].location(), (SourceLocation{2, 8}));

        EXPECT_EQ(tokens[13].type(), TokenType::WhiteSpace);
        EXPECT_EQ(tokens[13].value(), " ");
        EXPECT_EQ(tokens[13].location(), (SourceLocation{2, 9}));

        EXPECT_EQ(tokens[14].type(), TokenType::NumberLiteral);
        EXPECT_EQ(tokens[14].value(), "10");
        EXPECT_EQ(tokens[14].location(), (SourceLocation{2, 10}));

        EXPECT_EQ(tokens[15].type(), TokenType::Other);
        EXPECT_EQ(tokens[15].value(), ";");
        EXPECT_EQ(tokens[15].location(), (SourceLocation{2, 12}));
    }
}

/* ************************************************************************* */

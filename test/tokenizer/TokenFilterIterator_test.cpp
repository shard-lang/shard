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
#include "shard/tokenizer/TokenFilterIterator.hpp"
#include "shard/tokenizer/Tokenizer.hpp"

/* ************************************************************************* */

using namespace shard;
using namespace shard::tokenizer;

/* ************************************************************************* */

TEST(TokenFilterIterator, whiteSpace)
{
    using Iterator = TokenFilterIterator<TokenType::WhiteSpace>;

    Source source("var i = 8;");
    Tokenizer tokenizer(source);

    Iterator it(tokenizer.begin());
    Iterator end(tokenizer.end());

    EXPECT_TRUE(it.iterator().hasTokenizer());
    EXPECT_FALSE(end.iterator().hasTokenizer());
    EXPECT_EQ(&it.iterator().tokenizer(), &tokenizer);

    EXPECT_NE(it, end);
    EXPECT_EQ(it->type(), TokenType::Identifier);
    EXPECT_EQ(it->value(), "var");
    EXPECT_EQ(it->location(), (SourceLocation{1, 1}));
    EXPECT_EQ((*it).type(), TokenType::Identifier);
    EXPECT_EQ((*it).value(), "var");
    EXPECT_EQ((*it).location(), (SourceLocation{1, 1}));

    ++it;
    EXPECT_NE(it, end);
    EXPECT_EQ(it->type(), TokenType::Identifier);
    EXPECT_EQ(it->value(), "i");
    EXPECT_EQ(it->location(), (SourceLocation{1, 5}));

    ++it;
    EXPECT_NE(it, end);
    EXPECT_EQ(it->type(), TokenType::Other);
    EXPECT_EQ(it->value(), "=");
    EXPECT_EQ(it->location(), (SourceLocation{1, 7}));

    ++it;
    EXPECT_NE(it, end);
    EXPECT_EQ(it->type(), TokenType::NumberLiteral);
    EXPECT_EQ(it->value(), "8");
    EXPECT_EQ(it->location(), (SourceLocation{1, 9}));

    auto it2 = it++;
    EXPECT_NE(it, end);
    EXPECT_EQ(it->type(), TokenType::Other);
    EXPECT_EQ(it->value(), ";");
    EXPECT_EQ(it->location(), (SourceLocation{1, 10}));

    // Copied iterator
    EXPECT_NE(it2, end);
    EXPECT_EQ(it2->type(), TokenType::NumberLiteral);
    EXPECT_EQ(it2->value(), "8");
    EXPECT_EQ(it2->location(), (SourceLocation{1, 9}));

    ++it;
    EXPECT_EQ(it, end);
}

/* ************************************************************************* */

TEST(TokenFilterIterator, multiple)
{
    using Iterator = TokenFilterIterator<
        TokenType::WhiteSpace,
        TokenType::EndOfLine,
        TokenType::Comment>;

    Source source("var i = 8;\ni = i * 2; // Test");
    Tokenizer tokenizer(source);

    Iterator it(tokenizer.begin());
    Iterator end(tokenizer.end());

    EXPECT_TRUE(it.iterator().hasTokenizer());
    EXPECT_FALSE(end.iterator().hasTokenizer());
    EXPECT_EQ(&it.iterator().tokenizer(), &tokenizer);

    EXPECT_NE(it, end);
    EXPECT_EQ(it->type(), TokenType::Identifier);
    EXPECT_EQ(it->value(), "var");
    EXPECT_EQ(it->location(), (SourceLocation{1, 1}));
    EXPECT_EQ((*it).type(), TokenType::Identifier);
    EXPECT_EQ((*it).value(), "var");
    EXPECT_EQ((*it).location(), (SourceLocation{1, 1}));

    ++it;
    EXPECT_NE(it, end);
    EXPECT_EQ(it->type(), TokenType::Identifier);
    EXPECT_EQ(it->value(), "i");
    EXPECT_EQ(it->location(), (SourceLocation{1, 5}));

    ++it;
    EXPECT_NE(it, end);
    EXPECT_EQ(it->type(), TokenType::Other);
    EXPECT_EQ(it->value(), "=");
    EXPECT_EQ(it->location(), (SourceLocation{1, 7}));

    ++it;
    EXPECT_NE(it, end);
    EXPECT_EQ(it->type(), TokenType::NumberLiteral);
    EXPECT_EQ(it->value(), "8");
    EXPECT_EQ(it->location(), (SourceLocation{1, 9}));

    auto it2 = it++;
    EXPECT_NE(it, end);
    EXPECT_EQ(it->type(), TokenType::Other);
    EXPECT_EQ(it->value(), ";");
    EXPECT_EQ(it->location(), (SourceLocation{1, 10}));

    // Copied iterator
    EXPECT_NE(it2, end);
    EXPECT_EQ(it2->type(), TokenType::NumberLiteral);
    EXPECT_EQ(it2->value(), "8");
    EXPECT_EQ(it2->location(), (SourceLocation{1, 9}));

    ++it;
    EXPECT_NE(it, end);
    EXPECT_EQ(it->type(), TokenType::Identifier);
    EXPECT_EQ(it->value(), "i");
    EXPECT_EQ(it->location(), (SourceLocation{2, 1}));

    ++it;
    EXPECT_NE(it, end);
    EXPECT_EQ(it->type(), TokenType::Other);
    EXPECT_EQ(it->value(), "=");
    EXPECT_EQ(it->location(), (SourceLocation{2, 3}));

    ++it;
    EXPECT_NE(it, end);
    EXPECT_EQ(it->type(), TokenType::Identifier);
    EXPECT_EQ(it->value(), "i");
    EXPECT_EQ(it->location(), (SourceLocation{2, 5}));

    ++it;
    EXPECT_NE(it, end);
    EXPECT_EQ(it->type(), TokenType::Other);
    EXPECT_EQ(it->value(), "*");
    EXPECT_EQ(it->location(), (SourceLocation{2, 7}));

    ++it;
    EXPECT_NE(it, end);
    EXPECT_EQ(it->type(), TokenType::NumberLiteral);
    EXPECT_EQ(it->value(), "2");
    EXPECT_EQ(it->location(), (SourceLocation{2, 9}));

    ++it;
    EXPECT_NE(it, end);
    EXPECT_EQ(it->type(), TokenType::Other);
    EXPECT_EQ(it->value(), ";");
    EXPECT_EQ(it->location(), (SourceLocation{2, 10}));

    ++it;
    EXPECT_EQ(it, end);
}

/* ************************************************************************* */

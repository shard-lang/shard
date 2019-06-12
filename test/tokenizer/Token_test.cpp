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
#include "shard/tokenizer/Token.hpp"

/* ************************************************************************* */

using namespace shard;
using namespace shard::tokenizer;

/* ************************************************************************* */

TEST(Token, def)
{
    Token token;

    EXPECT_EQ(token.type(), TokenType::Unknown);
    EXPECT_EQ(token.value(), "");
    EXPECT_EQ(token.location(), (SourceLocation{0, 0}));
}

/* ************************************************************************* */

TEST(Token, construct)
{
    Token token{TokenType::Identifier, "var", SourceLocation{5, 10}};

    EXPECT_EQ(token.type(), TokenType::Identifier);
    EXPECT_EQ(token.value(), "var");
    EXPECT_EQ(token.location(), (SourceLocation{5, 10}));

    // Copy
    Token token2 = token;

    EXPECT_EQ(token2.type(), TokenType::Identifier);
    EXPECT_EQ(token2.value(), "var");
    EXPECT_EQ(token2.location(), (SourceLocation{5, 10}));

    token = Token{TokenType::NumberLiteral, "15", SourceLocation{1, 3}};

    EXPECT_EQ(token.type(), TokenType::NumberLiteral);
    EXPECT_EQ(token.value(), "15");
    EXPECT_EQ(token.location(), (SourceLocation{1, 3}));
}

/* ************************************************************************* */

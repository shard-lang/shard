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

// GTest
#include "gtest/gtest.h"

// C++
#include <limits>

// Shard
#include "shard/ast/expr/StringLiteralExpr.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

TEST(StringLiteralExpr, base)
{
    {
        const StringLiteralExpr expr({});

        EXPECT_EQ(ExprKind::StringLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_TRUE(expr.is<StringLiteralExpr>());
        EXPECT_FALSE(expr.is<NumberLiteralExpr>());
        EXPECT_TRUE(expr.getValue().empty());
        EXPECT_EQ(StringLiteralExpr::ValueType{}, expr.getValue());
    }

    {
        const StringLiteralExpr expr("");

        EXPECT_EQ(ExprKind::StringLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_TRUE(expr.is<StringLiteralExpr>());
        EXPECT_FALSE(expr.is<NumberLiteralExpr>());
        EXPECT_TRUE(expr.getValue().empty());
        EXPECT_EQ("", expr.getValue());
    }

    {
        const StringLiteralExpr expr("Hello world");

        EXPECT_EQ(ExprKind::StringLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_TRUE(expr.is<StringLiteralExpr>());
        EXPECT_FALSE(expr.is<NumberLiteralExpr>());
        EXPECT_FALSE(expr.getValue().empty());
        EXPECT_EQ("Hello world", expr.getValue());
    }

    {
        StringLiteralExpr expr({});

        EXPECT_EQ(ExprKind::StringLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_TRUE(expr.is<StringLiteralExpr>());
        EXPECT_FALSE(expr.is<NumberLiteralExpr>());
        EXPECT_TRUE(expr.getValue().empty());
        EXPECT_EQ(StringLiteralExpr::ValueType{}, expr.getValue());

        // Try to change values
        expr.setValue("Hello world");
        EXPECT_EQ("Hello world", expr.getValue());

        expr.setValue("Maybe");
        EXPECT_EQ("Maybe", expr.getValue());
    }

    {
        const auto expr = StringLiteralExpr::make({});
        ASSERT_NE(nullptr, expr);

        EXPECT_EQ(ExprKind::StringLiteral, expr->getKind());
        EXPECT_TRUE(expr->is<LiteralExpr>());
        EXPECT_TRUE(expr->is<StringLiteralExpr>());
        EXPECT_FALSE(expr->is<NumberLiteralExpr>());
        EXPECT_TRUE(expr->getValue().empty());
        EXPECT_EQ(StringLiteralExpr::ValueType{}, expr->getValue());
    }
}

/* ************************************************************************ */
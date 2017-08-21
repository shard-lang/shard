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
#include "shard/ast/expr/FloatLiteralExpr.hpp"
#include "shard/ast/expr/IntLiteralExpr.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

TEST(FloatLiteralExpr, base)
{
    {
        // Zero value
        const FloatLiteralExpr expr(0);

        EXPECT_EQ(ExprKind::FloatLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<FloatLiteralExpr>());
        EXPECT_FALSE(expr.is<IntLiteralExpr>());
        EXPECT_FLOAT_EQ(0, expr.getValue());
    }

    {
        // Random value
        const FloatLiteralExpr expr(0.111);

        EXPECT_EQ(ExprKind::FloatLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<FloatLiteralExpr>());
        EXPECT_FALSE(expr.is<IntLiteralExpr>());
        EXPECT_FLOAT_EQ(0.111, expr.getValue());
    }

    {
        // Min value
        const FloatLiteralExpr expr(std::numeric_limits<FloatLiteralExpr::ValueType>::min());

        EXPECT_EQ(ExprKind::FloatLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<FloatLiteralExpr>());
        EXPECT_FALSE(expr.is<IntLiteralExpr>());
        EXPECT_FLOAT_EQ(std::numeric_limits<FloatLiteralExpr::ValueType>::min(), expr.getValue());
    }

    {
        // Max value
        const FloatLiteralExpr expr(std::numeric_limits<FloatLiteralExpr::ValueType>::max());

        EXPECT_EQ(ExprKind::FloatLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<FloatLiteralExpr>());
        EXPECT_FALSE(expr.is<IntLiteralExpr>());
        EXPECT_FLOAT_EQ(std::numeric_limits<FloatLiteralExpr::ValueType>::max(), expr.getValue());
    }

    {
        FloatLiteralExpr expr(0);

        EXPECT_EQ(ExprKind::FloatLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<FloatLiteralExpr>());
        EXPECT_FALSE(expr.is<IntLiteralExpr>());
        EXPECT_FLOAT_EQ(0, expr.getValue());

        // Try to change values
        expr.setValue(0.456e5);
        EXPECT_FLOAT_EQ(0.456e5, expr.getValue());

        expr.setValue(-756e45);
        EXPECT_FLOAT_EQ(-756e45, expr.getValue());
    }

    {
        // Zero value
        const auto expr = FloatLiteralExpr::make(0);
        ASSERT_NE(nullptr, expr);

        EXPECT_EQ(ExprKind::FloatLiteral, expr->getKind());
        EXPECT_TRUE(expr->is<FloatLiteralExpr>());
        EXPECT_FALSE(expr->is<IntLiteralExpr>());
        EXPECT_FLOAT_EQ(0, expr->getValue());
    }
}

/* ************************************************************************ */
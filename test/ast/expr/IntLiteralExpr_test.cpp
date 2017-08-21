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
#include "shard/ast/expr/IntLiteralExpr.hpp"
#include "shard/ast/expr/FloatLiteralExpr.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

TEST(IntLiteralExpr, base)
{
    {
        // Zero value
        const IntLiteralExpr expr(0);

        EXPECT_EQ(ExprKind::IntLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<IntLiteralExpr>());
        EXPECT_FALSE(expr.is<FloatLiteralExpr>());
        EXPECT_EQ(0, expr.getValue());
    }

    {
        // Random value
        const IntLiteralExpr expr(123);

        EXPECT_EQ(ExprKind::IntLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<IntLiteralExpr>());
        EXPECT_FALSE(expr.is<FloatLiteralExpr>());
        EXPECT_EQ(123, expr.getValue());
    }

    {
        // Min value
        const IntLiteralExpr expr(std::numeric_limits<IntLiteralExpr::ValueType>::min());

        EXPECT_EQ(ExprKind::IntLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<IntLiteralExpr>());
        EXPECT_FALSE(expr.is<FloatLiteralExpr>());
        EXPECT_EQ(std::numeric_limits<IntLiteralExpr::ValueType>::min(), expr.getValue());
    }

    {
        // Max value
        const IntLiteralExpr expr(std::numeric_limits<IntLiteralExpr::ValueType>::max());

        EXPECT_EQ(ExprKind::IntLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<IntLiteralExpr>());
        EXPECT_FALSE(expr.is<FloatLiteralExpr>());
        EXPECT_EQ(std::numeric_limits<IntLiteralExpr::ValueType>::max(), expr.getValue());
    }

    {
        IntLiteralExpr expr(0);

        EXPECT_EQ(ExprKind::IntLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<IntLiteralExpr>());
        EXPECT_FALSE(expr.is<FloatLiteralExpr>());
        EXPECT_EQ(0, expr.getValue());

        // Try to change values
        expr.setValue(4877);
        EXPECT_EQ(4877, expr.getValue());

        expr.setValue(-488932);
        EXPECT_EQ(-488932, expr.getValue());
    }

    {
        // Zero value
        const auto expr = IntLiteralExpr::make(0);
        ASSERT_NE(nullptr, expr);

        EXPECT_EQ(ExprKind::IntLiteral, expr->getKind());
        EXPECT_TRUE(expr->is<IntLiteralExpr>());
        EXPECT_FALSE(expr->is<FloatLiteralExpr>());
        EXPECT_EQ(0, expr->getValue());
    }
}

/* ************************************************************************ */
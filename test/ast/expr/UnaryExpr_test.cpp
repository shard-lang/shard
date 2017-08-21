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
#include "shard/ast/expr/UnaryExpr.hpp"
#include "shard/ast/expr/BoolLiteralExpr.hpp"
#include "shard/ast/expr/IntLiteralExpr.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

TEST(UnaryExpr, base)
{
    {
        // !true
        const UnaryExpr expr(UnaryExpr::OpKind::Not, BoolLiteralExpr::make(true));

        EXPECT_EQ(ExprKind::Unary, expr.getKind());
        EXPECT_TRUE(expr.is<UnaryExpr>());
        EXPECT_EQ(UnaryExpr::OpKind::Not, expr.getOpKind());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<BoolLiteralExpr>());
        EXPECT_TRUE(expr.getExpr()->cast<BoolLiteralExpr>().getValue());
    }

    {
        // -10
        const UnaryExpr expr(UnaryExpr::OpKind::Minus, IntLiteralExpr::make(10));

        EXPECT_EQ(ExprKind::Unary, expr.getKind());
        EXPECT_TRUE(expr.is<UnaryExpr>());
        EXPECT_EQ(UnaryExpr::OpKind::Minus, expr.getOpKind());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<IntLiteralExpr>());
        EXPECT_EQ(10, expr.getExpr()->cast<IntLiteralExpr>().getValue());
    }

    {
        // 5++
        const UnaryExpr expr(UnaryExpr::OpKind::PostInc, IntLiteralExpr::make(5));

        EXPECT_EQ(ExprKind::Unary, expr.getKind());
        EXPECT_TRUE(expr.is<UnaryExpr>());
        EXPECT_EQ(UnaryExpr::OpKind::PostInc, expr.getOpKind());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<IntLiteralExpr>());
        EXPECT_EQ(5, expr.getExpr()->cast<IntLiteralExpr>().getValue());
    }

    {
        // true--
        const UnaryExpr expr(UnaryExpr::OpKind::PostDec, BoolLiteralExpr::make(true));

        EXPECT_EQ(ExprKind::Unary, expr.getKind());
        EXPECT_TRUE(expr.is<UnaryExpr>());
        EXPECT_EQ(UnaryExpr::OpKind::PostDec, expr.getOpKind());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<BoolLiteralExpr>());
        EXPECT_TRUE(expr.getExpr()->cast<BoolLiteralExpr>().getValue());
    }

    {
        // -10
        UnaryExpr expr(UnaryExpr::OpKind::Minus, IntLiteralExpr::make(0));

        EXPECT_EQ(ExprKind::Unary, expr.getKind());
        EXPECT_TRUE(expr.is<UnaryExpr>());
        EXPECT_EQ(UnaryExpr::OpKind::Minus, expr.getOpKind());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<IntLiteralExpr>());
        EXPECT_EQ(0, expr.getExpr()->cast<IntLiteralExpr>().getValue());

        // !0
        expr.setOpKind(UnaryExpr::OpKind::Not);
        EXPECT_EQ(ExprKind::Unary, expr.getKind());
        EXPECT_TRUE(expr.is<UnaryExpr>());
        EXPECT_EQ(UnaryExpr::OpKind::Not, expr.getOpKind());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<IntLiteralExpr>());
        EXPECT_EQ(0, expr.getExpr()->cast<IntLiteralExpr>().getValue());

        // !true
        expr.setExpr(BoolLiteralExpr::make(true));
        EXPECT_EQ(ExprKind::Unary, expr.getKind());
        EXPECT_TRUE(expr.is<UnaryExpr>());
        EXPECT_EQ(UnaryExpr::OpKind::Not, expr.getOpKind());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<BoolLiteralExpr>());
        EXPECT_TRUE(expr.getExpr()->cast<BoolLiteralExpr>().getValue());
    }

    {
        // !true
        const auto expr = UnaryExpr::make(UnaryExpr::OpKind::Not, BoolLiteralExpr::make(true));
        ASSERT_NE(nullptr, expr);

        EXPECT_EQ(ExprKind::Unary, expr->getKind());
        EXPECT_TRUE(expr->is<UnaryExpr>());
        EXPECT_EQ(UnaryExpr::OpKind::Not, expr->getOpKind());
        ASSERT_NE(nullptr, expr->getExpr());
        ASSERT_TRUE(expr->getExpr()->is<BoolLiteralExpr>());
        EXPECT_TRUE(expr->getExpr()->cast<BoolLiteralExpr>().getValue());
    }
}

/* ************************************************************************ */
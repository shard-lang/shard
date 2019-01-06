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
        const UnaryExpr expr(UnaryOpKind::Not, BoolLiteralExpr::make(true));

        EXPECT_TRUE(expr.is<UnaryExpr>());
        EXPECT_EQ(UnaryOpKind::Not, expr.op());
        ASSERT_NE(nullptr, expr.expr());
        ASSERT_TRUE(expr.expr()->is<BoolLiteralExpr>());
        EXPECT_TRUE(expr.expr()->cast<BoolLiteralExpr>().value());
        EXPECT_TRUE(expr.expr<BoolLiteralExpr>().value());
    }

    {
        // -10
        const UnaryExpr expr(UnaryOpKind::Minus, IntLiteralExpr::make(10));

        EXPECT_TRUE(expr.is<UnaryExpr>());
        EXPECT_EQ(UnaryOpKind::Minus, expr.op());
        ASSERT_NE(nullptr, expr.expr());
        ASSERT_TRUE(expr.expr()->is<IntLiteralExpr>());
        EXPECT_EQ(10, expr.expr()->cast<IntLiteralExpr>().value());
        EXPECT_EQ(10, expr.expr<IntLiteralExpr>().value());
    }

    {
        // 5++
        const UnaryExpr expr(UnaryOpKind::PostInc, IntLiteralExpr::make(5));

        EXPECT_TRUE(expr.is<UnaryExpr>());
        EXPECT_EQ(UnaryOpKind::PostInc, expr.op());
        ASSERT_NE(nullptr, expr.expr());
        ASSERT_TRUE(expr.expr()->is<IntLiteralExpr>());
        EXPECT_EQ(5, expr.expr()->cast<IntLiteralExpr>().value());
        EXPECT_EQ(5, expr.expr<IntLiteralExpr>().value());
    }

    {
        // true--
        const UnaryExpr expr(UnaryOpKind::PostDec, BoolLiteralExpr::make(true));

        EXPECT_TRUE(expr.is<UnaryExpr>());
        EXPECT_EQ(UnaryOpKind::PostDec, expr.op());
        ASSERT_NE(nullptr, expr.expr());
        ASSERT_TRUE(expr.expr()->is<BoolLiteralExpr>());
        EXPECT_TRUE(expr.expr()->cast<BoolLiteralExpr>().value());
        EXPECT_TRUE(expr.expr<BoolLiteralExpr>().value());
    }

    {
        // -10
        UnaryExpr expr(UnaryOpKind::Minus, IntLiteralExpr::make(0));

        EXPECT_TRUE(expr.is<UnaryExpr>());
        EXPECT_EQ(UnaryOpKind::Minus, expr.op());
        ASSERT_NE(nullptr, expr.expr());
        ASSERT_TRUE(expr.expr()->is<IntLiteralExpr>());
        EXPECT_EQ(0, expr.expr()->cast<IntLiteralExpr>().value());
        EXPECT_EQ(0, expr.expr<IntLiteralExpr>().value());

        // !0
        expr.setOp(UnaryOpKind::Not);
        EXPECT_TRUE(expr.is<UnaryExpr>());
        EXPECT_EQ(UnaryOpKind::Not, expr.op());
        ASSERT_NE(nullptr, expr.expr());
        ASSERT_TRUE(expr.expr()->is<IntLiteralExpr>());
        EXPECT_EQ(0, expr.expr()->cast<IntLiteralExpr>().value());
        EXPECT_EQ(0, expr.expr<IntLiteralExpr>().value());

        // !true
        expr.setExpr(BoolLiteralExpr::make(true));
        EXPECT_TRUE(expr.is<UnaryExpr>());
        EXPECT_EQ(UnaryOpKind::Not, expr.op());
        ASSERT_NE(nullptr, expr.expr());
        ASSERT_TRUE(expr.expr()->is<BoolLiteralExpr>());
        EXPECT_TRUE(expr.expr()->cast<BoolLiteralExpr>().value());
        EXPECT_TRUE(expr.expr<BoolLiteralExpr>().value());
    }

    {
        // !true
        const auto expr = UnaryExpr::make(UnaryOpKind::Not, BoolLiteralExpr::make(true));
        ASSERT_NE(nullptr, expr);

        EXPECT_TRUE(expr->is<UnaryExpr>());
        EXPECT_EQ(UnaryOpKind::Not, expr->op());
        ASSERT_NE(nullptr, expr->expr());
        ASSERT_TRUE(expr->expr()->is<BoolLiteralExpr>());
        EXPECT_TRUE(expr->expr()->cast<BoolLiteralExpr>().value());
        EXPECT_TRUE(expr->expr<BoolLiteralExpr>().value());
    }
}

/* ************************************************************************ */
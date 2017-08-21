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
#include "shard/ast/Expr.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

TEST(ParenExpr, base)
{
    {
        // (5)
        const ParenExpr expr(IntLiteralExpr::make(5));

        EXPECT_EQ(ExprKind::Paren, expr.getKind());
        EXPECT_TRUE(expr.is<ParenExpr>());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<IntLiteralExpr>());
        EXPECT_EQ(5, expr.getExpr()->cast<IntLiteralExpr>().getValue());
    }

    {
        // ((true))
        const ParenExpr expr(ParenExpr::make(BoolLiteralExpr::make(true)));

        EXPECT_EQ(ExprKind::Paren, expr.getKind());
        EXPECT_TRUE(expr.is<ParenExpr>());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<ParenExpr>());
        ASSERT_TRUE(expr.getExpr()->cast<ParenExpr>().getExpr());
        EXPECT_TRUE(expr.getExpr()->cast<ParenExpr>().getExpr()->cast<BoolLiteralExpr>().getValue());
    }

    {
        // (5)
        ParenExpr expr(IntLiteralExpr::make(5));

        EXPECT_EQ(ExprKind::Paren, expr.getKind());
        EXPECT_TRUE(expr.is<ParenExpr>());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<IntLiteralExpr>());
        EXPECT_EQ(5, expr.getExpr()->cast<IntLiteralExpr>().getValue());

        // (true)
        expr.setExpr(BoolLiteralExpr::make(true));
        EXPECT_EQ(ExprKind::Paren, expr.getKind());
        EXPECT_TRUE(expr.is<ParenExpr>());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<BoolLiteralExpr>());
        EXPECT_TRUE(expr.getExpr()->cast<BoolLiteralExpr>().getValue());
    }

    {
        // (5)
        const auto expr = ParenExpr::make(IntLiteralExpr::make(5));
        ASSERT_NE(nullptr, expr);

        EXPECT_EQ(ExprKind::Paren, expr->getKind());
        EXPECT_TRUE(expr->is<ParenExpr>());
        ASSERT_NE(nullptr, expr->getExpr());
        ASSERT_TRUE(expr->getExpr()->is<IntLiteralExpr>());
        EXPECT_EQ(5, expr->getExpr()->cast<IntLiteralExpr>().getValue());
    }
}

/* ************************************************************************ */
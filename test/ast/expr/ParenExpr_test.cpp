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
#include "shard/ast/expr/ParenExpr.hpp"
#include "shard/ast/expr/IntLiteralExpr.hpp"
#include "shard/ast/expr/BoolLiteralExpr.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

TEST(ParenExpr, base)
{
    {
        // (5)
        const ParenExpr expr(IntLiteralExpr::make(5));

        EXPECT_TRUE(expr.is<ParenExpr>());
        ASSERT_NE(nullptr, expr.expr());
        ASSERT_TRUE(expr.expr()->is<IntLiteralExpr>());
        EXPECT_EQ(5, expr.expr()->cast<IntLiteralExpr>().value());
        EXPECT_EQ(5, expr.expr<IntLiteralExpr>().value());
    }

    {
        // ((true))
        const ParenExpr expr(ParenExpr::make(BoolLiteralExpr::make(true)));

        EXPECT_TRUE(expr.is<ParenExpr>());
        ASSERT_NE(nullptr, expr.expr());
        ASSERT_TRUE(expr.expr()->is<ParenExpr>());
        ASSERT_TRUE(expr.expr()->cast<ParenExpr>().expr());
        ASSERT_TRUE(expr.expr<ParenExpr>().expr());
        EXPECT_TRUE(expr.expr()->cast<ParenExpr>().expr()->cast<BoolLiteralExpr>().value());
        EXPECT_TRUE(expr.expr<ParenExpr>().expr<BoolLiteralExpr>().value());
    }

    {
        // (5)
        ParenExpr expr(IntLiteralExpr::make(5));

        EXPECT_TRUE(expr.is<ParenExpr>());
        ASSERT_NE(nullptr, expr.expr());
        ASSERT_TRUE(expr.expr()->is<IntLiteralExpr>());
        EXPECT_EQ(5, expr.expr()->cast<IntLiteralExpr>().value());
        EXPECT_EQ(5, expr.expr<IntLiteralExpr>().value());

        // (true)
        expr.setExpr(BoolLiteralExpr::make(true));
        EXPECT_TRUE(expr.is<ParenExpr>());
        ASSERT_NE(nullptr, expr.expr());
        ASSERT_TRUE(expr.expr()->is<BoolLiteralExpr>());
        EXPECT_TRUE(expr.expr()->cast<BoolLiteralExpr>().value());
        EXPECT_TRUE(expr.expr<BoolLiteralExpr>().value());
    }

    {
        // (5)
        const auto expr = ParenExpr::make(IntLiteralExpr::make(5));
        ASSERT_NE(nullptr, expr);

        EXPECT_TRUE(expr->is<ParenExpr>());
        ASSERT_NE(nullptr, expr->expr());
        ASSERT_TRUE(expr->expr()->is<IntLiteralExpr>());
        EXPECT_EQ(5, expr->expr()->cast<IntLiteralExpr>().value());
        EXPECT_EQ(5, expr->expr<IntLiteralExpr>().value());
    }
}

/* ************************************************************************ */
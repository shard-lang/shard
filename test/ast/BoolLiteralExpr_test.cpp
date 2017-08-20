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

TEST(BoolLiteralExpr, base)
{
    {
        const BoolLiteralExpr expr(true);

        EXPECT_EQ(ExprKind::BoolLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_FALSE(expr.is<NullLiteralExpr>());
        EXPECT_TRUE(expr.is<BoolLiteralExpr>());
        EXPECT_TRUE(expr.getValue());
    }

    {
        const BoolLiteralExpr expr(false);

        EXPECT_EQ(ExprKind::BoolLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_FALSE(expr.is<NullLiteralExpr>());
        EXPECT_TRUE(expr.is<BoolLiteralExpr>());
        EXPECT_FALSE(expr.getValue());
    }

    {
        BoolLiteralExpr expr(false);

        EXPECT_EQ(ExprKind::BoolLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_FALSE(expr.is<NullLiteralExpr>());
        EXPECT_TRUE(expr.is<BoolLiteralExpr>());
        EXPECT_FALSE(expr.getValue());

        // Try to change value
        expr.setValue(true);
        EXPECT_TRUE(expr.getValue());

        expr.setValue(false);
        EXPECT_FALSE(expr.getValue());
    }

    {
        const auto expr = BoolLiteralExpr::make(true);
        ASSERT_NE(nullptr, expr);

        EXPECT_EQ(ExprKind::BoolLiteral, expr->getKind());
        EXPECT_TRUE(expr->is<LiteralExpr>());
        EXPECT_FALSE(expr->is<NullLiteralExpr>());
        EXPECT_TRUE(expr->is<BoolLiteralExpr>());
        EXPECT_TRUE(expr->getValue());
    }
}

/* ************************************************************************ */
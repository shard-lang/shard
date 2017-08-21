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
#include "shard/ast/expr/NullLiteralExpr.hpp"
#include "shard/ast/expr/BoolLiteralExpr.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

TEST(NullLiteralExpr, base)
{
    {
        const NullLiteralExpr expr;

        EXPECT_EQ(ExprKind::NullLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_TRUE(expr.is<NullLiteralExpr>());
        EXPECT_FALSE(expr.is<BoolLiteralExpr>());
        EXPECT_EQ(SourceLocation{}, expr.getSourceStart());
        EXPECT_EQ(SourceLocation{}, expr.getSourceEnd());
    }

    {
        const NullLiteralExpr expr({{123, 456}, {123, 458}});

        EXPECT_EQ(ExprKind::NullLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_TRUE(expr.is<NullLiteralExpr>());
        EXPECT_FALSE(expr.is<BoolLiteralExpr>());
        EXPECT_EQ((SourceLocation{123, 456}), expr.getSourceStart());
        EXPECT_EQ((SourceLocation{123, 458}), expr.getSourceEnd());
    }

    {
        const auto expr = NullLiteralExpr::make();
        ASSERT_NE(nullptr, expr);

        EXPECT_EQ(ExprKind::NullLiteral, expr->getKind());
        EXPECT_TRUE(expr->is<LiteralExpr>());
        EXPECT_TRUE(expr->is<NullLiteralExpr>());
        EXPECT_FALSE(expr->is<BoolLiteralExpr>());
    }
}

/* ************************************************************************ */
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
#include "shard/ast/expr/NullLiteralExpr.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

namespace {

/* ************************************************************************ */

struct TestExpr : public Expr
{

};

/* ************************************************************************ */

}

/* ************************************************************************ */

TEST(NullLiteralExpr, base)
{
    {
        const NullLiteralExpr expr;

        EXPECT_TRUE(expr.is<NullLiteralExpr>());
        EXPECT_FALSE(expr.is<TestExpr>());
        EXPECT_EQ(SourceLocation{}, expr.sourceRange().start());
        EXPECT_EQ(SourceLocation{}, expr.sourceRange().end());
    }

    {
        const NullLiteralExpr expr({{123, 456}, {123, 458}});

        EXPECT_TRUE(expr.is<NullLiteralExpr>());
        EXPECT_FALSE(expr.is<TestExpr>());
        EXPECT_EQ((SourceLocation{123, 456}), expr.sourceRange().start());
        EXPECT_EQ((SourceLocation{123, 458}), expr.sourceRange().end());
    }

    {
        const auto expr = NullLiteralExpr::make();
        ASSERT_NE(nullptr, expr);

        EXPECT_TRUE(expr->is<NullLiteralExpr>());
        EXPECT_FALSE(expr->is<TestExpr>());
    }
}

/* ************************************************************************ */
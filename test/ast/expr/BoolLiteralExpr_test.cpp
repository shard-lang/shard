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
#include "shard/ast/expr/BoolLiteralExpr.hpp"

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

TEST(BoolLiteralExpr, base)
{
    {
        const BoolLiteralExpr expr(true);

        EXPECT_FALSE(expr.is<TestExpr>());
        EXPECT_TRUE(expr.is<BoolLiteralExpr>());
        EXPECT_TRUE(expr.value());
    }

    {
        const BoolLiteralExpr expr(false);

        EXPECT_FALSE(expr.is<TestExpr>());
        EXPECT_TRUE(expr.is<BoolLiteralExpr>());
        EXPECT_FALSE(expr.value());
    }

    {
        BoolLiteralExpr expr(false);

        EXPECT_FALSE(expr.is<TestExpr>());
        EXPECT_TRUE(expr.is<BoolLiteralExpr>());
        EXPECT_FALSE(expr.value());

        // Try to change value
        expr.setValue(true);
        EXPECT_TRUE(expr.value());

        expr.setValue(false);
        EXPECT_FALSE(expr.value());
    }

    {
        const auto expr = BoolLiteralExpr::make(true);
        ASSERT_NE(nullptr, expr);

        EXPECT_FALSE(expr->is<TestExpr>());
        EXPECT_TRUE(expr->is<BoolLiteralExpr>());
        EXPECT_TRUE(expr->value());
    }
}

/* ************************************************************************ */
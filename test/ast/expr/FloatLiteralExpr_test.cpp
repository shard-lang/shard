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

TEST(FloatLiteralExpr, base)
{
    {
        // Zero value
        const FloatLiteralExpr expr(0.0f);

        EXPECT_TRUE(expr.is<FloatLiteralExpr>());
        EXPECT_FALSE(expr.is<TestExpr>());
        EXPECT_FLOAT_EQ(0.0f, expr.value());
    }

    {
        // Random value
        const FloatLiteralExpr expr(0.111f);

        EXPECT_TRUE(expr.is<FloatLiteralExpr>());
        EXPECT_FALSE(expr.is<TestExpr>());
        EXPECT_FLOAT_EQ(0.111f, expr.value());
    }

    {
        // Min value
        const FloatLiteralExpr expr(std::numeric_limits<FloatLiteralExpr::ValueType>::min());

        EXPECT_TRUE(expr.is<FloatLiteralExpr>());
        EXPECT_FALSE(expr.is<TestExpr>());
        EXPECT_FLOAT_EQ(std::numeric_limits<FloatLiteralExpr::ValueType>::min(), expr.value());
    }

    {
        // Max value
        const FloatLiteralExpr expr(std::numeric_limits<FloatLiteralExpr::ValueType>::max());

        EXPECT_TRUE(expr.is<FloatLiteralExpr>());
        EXPECT_FALSE(expr.is<TestExpr>());
        EXPECT_FLOAT_EQ(std::numeric_limits<FloatLiteralExpr::ValueType>::max(), expr.value());
    }

    {
        FloatLiteralExpr expr(0.0f);

        EXPECT_TRUE(expr.is<FloatLiteralExpr>());
        EXPECT_FALSE(expr.is<TestExpr>());
        EXPECT_FLOAT_EQ(0.0f, expr.value());

        // Try to change values
        expr.setValue(0.456e5f);
        EXPECT_FLOAT_EQ(0.456e5f, expr.value());

        expr.setValue(-756e45f);
        EXPECT_FLOAT_EQ(-7560e45f, expr.value());
    }

    {
        // Zero value
        const auto expr = FloatLiteralExpr::make(0.0f);
        ASSERT_NE(nullptr, expr);

        EXPECT_TRUE(expr->is<FloatLiteralExpr>());
        EXPECT_FALSE(expr->is<TestExpr>());
        EXPECT_FLOAT_EQ(0.0f, expr->value());
    }
}

/* ************************************************************************ */
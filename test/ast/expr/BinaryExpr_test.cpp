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
#include "shard/ast/expr/BinaryExpr.hpp"
#include "shard/ast/expr/IntLiteralExpr.hpp"
#include "shard/ast/expr/FloatLiteralExpr.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

TEST(BinaryExpr, base)
{
    {
        // 5 + 2
        const BinaryExpr expr("+", IntLiteralExpr::make(5), IntLiteralExpr::make(2));

        EXPECT_TRUE(expr.is<BinaryExpr>());
        EXPECT_EQ("+", expr.op());
        ASSERT_NE(nullptr, expr.lhs());
        ASSERT_NE(nullptr, expr.rhs());
        ASSERT_TRUE(expr.lhs()->is<IntLiteralExpr>());
        ASSERT_TRUE(expr.rhs()->is<IntLiteralExpr>());
        EXPECT_EQ(5, expr.lhs()->cast<IntLiteralExpr>().value());
        EXPECT_EQ(2, expr.rhs()->cast<IntLiteralExpr>().value());
        EXPECT_EQ(5, expr.lhs<IntLiteralExpr>().value());
        EXPECT_EQ(2, expr.rhs<IntLiteralExpr>().value());
    }

    {
        // 10 * 4.0
        const BinaryExpr expr("*", IntLiteralExpr::make(10), FloatLiteralExpr::make(4.0));

        EXPECT_TRUE(expr.is<BinaryExpr>());
        EXPECT_EQ("*", expr.op());
        ASSERT_NE(nullptr, expr.lhs());
        ASSERT_NE(nullptr, expr.rhs());
        ASSERT_TRUE(expr.lhs()->is<IntLiteralExpr>());
        ASSERT_TRUE(expr.rhs()->is<FloatLiteralExpr>());
        EXPECT_EQ(10, expr.lhs()->cast<IntLiteralExpr>().value());
        EXPECT_FLOAT_EQ(4.0, expr.rhs()->cast<FloatLiteralExpr>().value());
        EXPECT_EQ(10, expr.lhs<IntLiteralExpr>().value());
        EXPECT_FLOAT_EQ(4.0, expr.rhs<FloatLiteralExpr>().value());
    }

    {
        // 10 * 4.0
        BinaryExpr expr("*", IntLiteralExpr::make(10), FloatLiteralExpr::make(4.0));

        EXPECT_TRUE(expr.is<BinaryExpr>());
        EXPECT_EQ("*", expr.op());
        ASSERT_NE(nullptr, expr.lhs());
        ASSERT_NE(nullptr, expr.rhs());
        ASSERT_TRUE(expr.lhs()->is<IntLiteralExpr>());
        ASSERT_TRUE(expr.rhs()->is<FloatLiteralExpr>());
        EXPECT_EQ(10, expr.lhs()->cast<IntLiteralExpr>().value());
        EXPECT_FLOAT_EQ(4.0, expr.rhs()->cast<FloatLiteralExpr>().value());
        EXPECT_EQ(10, expr.lhs<IntLiteralExpr>().value());
        EXPECT_FLOAT_EQ(4.0, expr.rhs<FloatLiteralExpr>().value());

        // 10 + 4.0
        expr.setOp("+");
        EXPECT_EQ("+", expr.op());
        ASSERT_NE(nullptr, expr.lhs());
        ASSERT_NE(nullptr, expr.rhs());
        ASSERT_TRUE(expr.lhs()->is<IntLiteralExpr>());
        ASSERT_TRUE(expr.rhs()->is<FloatLiteralExpr>());
        EXPECT_EQ(10, expr.lhs()->cast<IntLiteralExpr>().value());
        EXPECT_FLOAT_EQ(4.0, expr.rhs()->cast<FloatLiteralExpr>().value());

        // 10 - 4.0
        expr.setOp("-");
        EXPECT_EQ("-", expr.op());
        ASSERT_NE(nullptr, expr.lhs());
        ASSERT_NE(nullptr, expr.rhs());
        ASSERT_TRUE(expr.lhs()->is<IntLiteralExpr>());
        ASSERT_TRUE(expr.rhs()->is<FloatLiteralExpr>());
        EXPECT_EQ(10, expr.lhs()->cast<IntLiteralExpr>().value());
        EXPECT_FLOAT_EQ(4.0, expr.rhs()->cast<FloatLiteralExpr>().value());

        // 1.0 - 4.0
        expr.setLhs(FloatLiteralExpr::make(1.0));
        EXPECT_EQ("-", expr.op());
        ASSERT_NE(nullptr, expr.lhs());
        ASSERT_NE(nullptr, expr.rhs());
        ASSERT_TRUE(expr.lhs()->is<FloatLiteralExpr>());
        ASSERT_TRUE(expr.rhs()->is<FloatLiteralExpr>());
        EXPECT_FLOAT_EQ(1.0, expr.lhs()->cast<FloatLiteralExpr>().value());
        EXPECT_FLOAT_EQ(4.0, expr.rhs()->cast<FloatLiteralExpr>().value());

        expr.setRhs(FloatLiteralExpr::make(50.3));
        EXPECT_EQ("-", expr.op());
        ASSERT_NE(nullptr, expr.lhs());
        ASSERT_NE(nullptr, expr.rhs());
        ASSERT_TRUE(expr.lhs()->is<FloatLiteralExpr>());
        ASSERT_TRUE(expr.rhs()->is<FloatLiteralExpr>());
        EXPECT_FLOAT_EQ(1.0, expr.lhs()->cast<FloatLiteralExpr>().value());
        EXPECT_FLOAT_EQ(50.3, expr.rhs()->cast<FloatLiteralExpr>().value());
    }

    {
        // 5 + 2
        const auto expr = BinaryExpr::make("+", IntLiteralExpr::make(5), IntLiteralExpr::make(2));
        ASSERT_NE(nullptr, expr);

        EXPECT_TRUE(expr->is<BinaryExpr>());
        EXPECT_EQ("+", expr->op());
        ASSERT_NE(nullptr, expr->lhs());
        ASSERT_NE(nullptr, expr->rhs());
        ASSERT_TRUE(expr->lhs()->is<IntLiteralExpr>());
        ASSERT_TRUE(expr->rhs()->is<IntLiteralExpr>());
        EXPECT_EQ(5, expr->lhs()->cast<IntLiteralExpr>().value());
        EXPECT_EQ(2, expr->rhs()->cast<IntLiteralExpr>().value());
    }

}

/* ************************************************************************ */
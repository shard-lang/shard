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
        const BinaryExpr expr(BinaryExpr::OpKind::Add, IntLiteralExpr::make(5), IntLiteralExpr::make(2));

        EXPECT_EQ(ExprKind::Binary, expr.getKind());
        EXPECT_TRUE(expr.is<BinaryExpr>());
        EXPECT_EQ(BinaryExpr::OpKind::Add, expr.getOpKind());
        ASSERT_NE(nullptr, expr.getLhs());
        ASSERT_NE(nullptr, expr.getRhs());
        ASSERT_TRUE(expr.getLhs()->is<IntLiteralExpr>());
        ASSERT_TRUE(expr.getRhs()->is<IntLiteralExpr>());
        EXPECT_EQ(5, expr.getLhs()->cast<IntLiteralExpr>().getValue());
        EXPECT_EQ(2, expr.getRhs()->cast<IntLiteralExpr>().getValue());
    }

    {
        // 10 * 4.0
        const BinaryExpr expr(BinaryExpr::OpKind::Mul, IntLiteralExpr::make(10), FloatLiteralExpr::make(4.0));

        EXPECT_EQ(ExprKind::Binary, expr.getKind());
        EXPECT_TRUE(expr.is<BinaryExpr>());
        EXPECT_EQ(BinaryExpr::OpKind::Mul, expr.getOpKind());
        ASSERT_NE(nullptr, expr.getLhs());
        ASSERT_NE(nullptr, expr.getRhs());
        ASSERT_TRUE(expr.getLhs()->is<IntLiteralExpr>());
        ASSERT_TRUE(expr.getRhs()->is<FloatLiteralExpr>());
        EXPECT_EQ(10, expr.getLhs()->cast<IntLiteralExpr>().getValue());
        EXPECT_FLOAT_EQ(4.0, expr.getRhs()->cast<FloatLiteralExpr>().getValue());
    }

    {
        // 10 * 4.0
        BinaryExpr expr(BinaryExpr::OpKind::Mul, IntLiteralExpr::make(10), FloatLiteralExpr::make(4.0));

        EXPECT_EQ(ExprKind::Binary, expr.getKind());
        EXPECT_TRUE(expr.is<BinaryExpr>());
        EXPECT_EQ(BinaryExpr::OpKind::Mul, expr.getOpKind());
        ASSERT_NE(nullptr, expr.getLhs());
        ASSERT_NE(nullptr, expr.getRhs());
        ASSERT_TRUE(expr.getLhs()->is<IntLiteralExpr>());
        ASSERT_TRUE(expr.getRhs()->is<FloatLiteralExpr>());
        EXPECT_EQ(10, expr.getLhs()->cast<IntLiteralExpr>().getValue());
        EXPECT_FLOAT_EQ(4.0, expr.getRhs()->cast<FloatLiteralExpr>().getValue());

        // 10 + 4.0
        expr.setOpKind(BinaryExpr::OpKind::Add);
        EXPECT_EQ(BinaryExpr::OpKind::Add, expr.getOpKind());
        ASSERT_NE(nullptr, expr.getLhs());
        ASSERT_NE(nullptr, expr.getRhs());
        ASSERT_TRUE(expr.getLhs()->is<IntLiteralExpr>());
        ASSERT_TRUE(expr.getRhs()->is<FloatLiteralExpr>());
        EXPECT_EQ(10, expr.getLhs()->cast<IntLiteralExpr>().getValue());
        EXPECT_FLOAT_EQ(4.0, expr.getRhs()->cast<FloatLiteralExpr>().getValue());

        // 10 - 4.0
        expr.setOpKind(BinaryExpr::OpKind::Sub);
        EXPECT_EQ(BinaryExpr::OpKind::Sub, expr.getOpKind());
        ASSERT_NE(nullptr, expr.getLhs());
        ASSERT_NE(nullptr, expr.getRhs());
        ASSERT_TRUE(expr.getLhs()->is<IntLiteralExpr>());
        ASSERT_TRUE(expr.getRhs()->is<FloatLiteralExpr>());
        EXPECT_EQ(10, expr.getLhs()->cast<IntLiteralExpr>().getValue());
        EXPECT_FLOAT_EQ(4.0, expr.getRhs()->cast<FloatLiteralExpr>().getValue());

        // 1.0 - 4.0
        expr.setLhs(FloatLiteralExpr::make(1.0));
        EXPECT_EQ(BinaryExpr::OpKind::Sub, expr.getOpKind());
        ASSERT_NE(nullptr, expr.getLhs());
        ASSERT_NE(nullptr, expr.getRhs());
        ASSERT_TRUE(expr.getLhs()->is<FloatLiteralExpr>());
        ASSERT_TRUE(expr.getRhs()->is<FloatLiteralExpr>());
        EXPECT_FLOAT_EQ(1.0, expr.getLhs()->cast<FloatLiteralExpr>().getValue());
        EXPECT_FLOAT_EQ(4.0, expr.getRhs()->cast<FloatLiteralExpr>().getValue());

        // 1.0 - 50.3
        expr.setRhs(FloatLiteralExpr::make(50.3));
        EXPECT_EQ(BinaryExpr::OpKind::Sub, expr.getOpKind());
        ASSERT_NE(nullptr, expr.getLhs());
        ASSERT_NE(nullptr, expr.getRhs());
        ASSERT_TRUE(expr.getLhs()->is<FloatLiteralExpr>());
        ASSERT_TRUE(expr.getRhs()->is<FloatLiteralExpr>());
        EXPECT_FLOAT_EQ(1.0, expr.getLhs()->cast<FloatLiteralExpr>().getValue());
        EXPECT_FLOAT_EQ(50.3, expr.getRhs()->cast<FloatLiteralExpr>().getValue());
    }

    {
        // 5 + 2
        const auto expr = BinaryExpr::make(BinaryExpr::OpKind::Add, IntLiteralExpr::make(5), IntLiteralExpr::make(2));
        ASSERT_NE(nullptr, expr);

        EXPECT_EQ(ExprKind::Binary, expr->getKind());
        EXPECT_TRUE(expr->is<BinaryExpr>());
        EXPECT_EQ(BinaryExpr::OpKind::Add, expr->getOpKind());
        ASSERT_NE(nullptr, expr->getLhs());
        ASSERT_NE(nullptr, expr->getRhs());
        ASSERT_TRUE(expr->getLhs()->is<IntLiteralExpr>());
        ASSERT_TRUE(expr->getRhs()->is<IntLiteralExpr>());
        EXPECT_EQ(5, expr->getLhs()->cast<IntLiteralExpr>().getValue());
        EXPECT_EQ(2, expr->getRhs()->cast<IntLiteralExpr>().getValue());
    }

}

/* ************************************************************************ */
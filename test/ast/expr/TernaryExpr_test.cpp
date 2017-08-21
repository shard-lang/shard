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
#include "shard/ast/expr/TernaryExpr.hpp"
#include "shard/ast/expr/BoolLiteralExpr.hpp"
#include "shard/ast/expr/IntLiteralExpr.hpp"
#include "shard/ast/expr/IdentifierExpr.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

TEST(TernaryExpr, base)
{
    {
        // true ? 1 : 2
        const TernaryExpr expr(BoolLiteralExpr::make(true), IntLiteralExpr::make(1), IntLiteralExpr::make(2));

        EXPECT_EQ(ExprKind::Ternary, expr.getKind());
        EXPECT_TRUE(expr.is<TernaryExpr>());
        ASSERT_NE(nullptr, expr.getCondExpr());
        ASSERT_NE(nullptr, expr.getTrueExpr());
        ASSERT_NE(nullptr, expr.getFalseExpr());
        ASSERT_TRUE(expr.getCondExpr()->is<BoolLiteralExpr>());
        ASSERT_TRUE(expr.getTrueExpr()->is<IntLiteralExpr>());
        ASSERT_TRUE(expr.getFalseExpr()->is<IntLiteralExpr>());
        EXPECT_TRUE(expr.getCondExpr()->cast<BoolLiteralExpr>().getValue());
        EXPECT_EQ(1, expr.getTrueExpr()->cast<IntLiteralExpr>().getValue());
        EXPECT_EQ(2, expr.getFalseExpr()->cast<IntLiteralExpr>().getValue());
    }

    {
        // true ? 1 : 2
        TernaryExpr expr(BoolLiteralExpr::make(true), IntLiteralExpr::make(1), IntLiteralExpr::make(2));

        EXPECT_EQ(ExprKind::Ternary, expr.getKind());
        EXPECT_TRUE(expr.is<TernaryExpr>());
        ASSERT_NE(nullptr, expr.getCondExpr());
        ASSERT_NE(nullptr, expr.getTrueExpr());
        ASSERT_NE(nullptr, expr.getFalseExpr());
        ASSERT_TRUE(expr.getCondExpr()->is<BoolLiteralExpr>());
        ASSERT_TRUE(expr.getTrueExpr()->is<IntLiteralExpr>());
        ASSERT_TRUE(expr.getFalseExpr()->is<IntLiteralExpr>());
        EXPECT_TRUE(expr.getCondExpr()->cast<BoolLiteralExpr>().getValue());
        EXPECT_EQ(1, expr.getTrueExpr()->cast<IntLiteralExpr>().getValue());
        EXPECT_EQ(2, expr.getFalseExpr()->cast<IntLiteralExpr>().getValue());

        // cond ? 1 : 2
        expr.setCondExpr(IdentifierExpr::make("cond"));
        EXPECT_TRUE(expr.is<TernaryExpr>());
        ASSERT_NE(nullptr, expr.getCondExpr());
        ASSERT_NE(nullptr, expr.getTrueExpr());
        ASSERT_NE(nullptr, expr.getFalseExpr());
        ASSERT_TRUE(expr.getCondExpr()->is<IdentifierExpr>());
        ASSERT_TRUE(expr.getTrueExpr()->is<IntLiteralExpr>());
        ASSERT_TRUE(expr.getFalseExpr()->is<IntLiteralExpr>());
        EXPECT_EQ("cond", expr.getCondExpr()->cast<IdentifierExpr>().getName());
        EXPECT_EQ(1, expr.getTrueExpr()->cast<IntLiteralExpr>().getValue());
        EXPECT_EQ(2, expr.getFalseExpr()->cast<IntLiteralExpr>().getValue());

        // cond ? true : 2
        expr.setTrueExpr(BoolLiteralExpr::make(true));
        EXPECT_TRUE(expr.is<TernaryExpr>());
        ASSERT_NE(nullptr, expr.getCondExpr());
        ASSERT_NE(nullptr, expr.getTrueExpr());
        ASSERT_NE(nullptr, expr.getFalseExpr());
        ASSERT_TRUE(expr.getCondExpr()->is<IdentifierExpr>());
        ASSERT_TRUE(expr.getTrueExpr()->is<BoolLiteralExpr>());
        ASSERT_TRUE(expr.getFalseExpr()->is<IntLiteralExpr>());
        EXPECT_EQ("cond", expr.getCondExpr()->cast<IdentifierExpr>().getName());
        EXPECT_TRUE(expr.getTrueExpr()->cast<BoolLiteralExpr>().getValue());
        EXPECT_EQ(2, expr.getFalseExpr()->cast<IntLiteralExpr>().getValue());

        // cond ? true : false
        expr.setFalseExpr(BoolLiteralExpr::make(false));
        EXPECT_TRUE(expr.is<TernaryExpr>());
        ASSERT_NE(nullptr, expr.getCondExpr());
        ASSERT_NE(nullptr, expr.getTrueExpr());
        ASSERT_NE(nullptr, expr.getFalseExpr());
        ASSERT_TRUE(expr.getCondExpr()->is<IdentifierExpr>());
        ASSERT_TRUE(expr.getTrueExpr()->is<BoolLiteralExpr>());
        ASSERT_TRUE(expr.getFalseExpr()->is<BoolLiteralExpr>());
        EXPECT_EQ("cond", expr.getCondExpr()->cast<IdentifierExpr>().getName());
        EXPECT_TRUE(expr.getTrueExpr()->cast<BoolLiteralExpr>().getValue());
        EXPECT_FALSE(expr.getFalseExpr()->cast<BoolLiteralExpr>().getValue());
    }

    {
        // true ? 1 : 2
        const auto expr = TernaryExpr::make(BoolLiteralExpr::make(true), IntLiteralExpr::make(1), IntLiteralExpr::make(2));
        ASSERT_NE(nullptr, expr);

        EXPECT_EQ(ExprKind::Ternary, expr->getKind());
        EXPECT_TRUE(expr->is<TernaryExpr>());
        ASSERT_NE(nullptr, expr->getCondExpr());
        ASSERT_NE(nullptr, expr->getTrueExpr());
        ASSERT_NE(nullptr, expr->getFalseExpr());
        ASSERT_TRUE(expr->getCondExpr()->is<BoolLiteralExpr>());
        ASSERT_TRUE(expr->getTrueExpr()->is<IntLiteralExpr>());
        ASSERT_TRUE(expr->getFalseExpr()->is<IntLiteralExpr>());
        EXPECT_TRUE(expr->getCondExpr()->cast<BoolLiteralExpr>().getValue());
        EXPECT_EQ(1, expr->getTrueExpr()->cast<IntLiteralExpr>().getValue());
        EXPECT_EQ(2, expr->getFalseExpr()->cast<IntLiteralExpr>().getValue());
    }
}

/* ************************************************************************ */
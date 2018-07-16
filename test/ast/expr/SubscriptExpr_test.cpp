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
#include "shard/utility.hpp"
#include "shard/ast/expr/SubscriptExpr.hpp"
#include "shard/ast/expr/IdentifierExpr.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

TEST(SubscriptExpr, base)
{
    {
        // obj[]
        const SubscriptExpr expr(IdentifierExpr::make("obj"), {});

        EXPECT_EQ(ExprKind::Subscript, expr.getKind());
        EXPECT_TRUE(expr.is<SubscriptExpr>());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<IdentifierExpr>());
        EXPECT_EQ("obj", expr.getExpr()->cast<IdentifierExpr>().getName());
        EXPECT_TRUE(expr.getArguments().empty());
    }

    {
        // obj[]
        SubscriptExpr expr(IdentifierExpr::make("obj"), {});

        EXPECT_EQ(ExprKind::Subscript, expr.getKind());
        EXPECT_TRUE(expr.is<SubscriptExpr>());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<IdentifierExpr>());
        EXPECT_EQ("obj", expr.getExpr()->cast<IdentifierExpr>().getName());
        EXPECT_TRUE(expr.getArguments().empty());

        // val[]
        expr.setExpr(IdentifierExpr::make("val"));
        EXPECT_TRUE(expr.is<SubscriptExpr>());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<IdentifierExpr>());
        EXPECT_EQ("val", expr.getExpr()->cast<IdentifierExpr>().getName());
        EXPECT_TRUE(expr.getArguments().empty());

        // val[x, y]
        PtrVector<Expr> args;
        args.push_back(IdentifierExpr::make("x"));
        args.push_back(IdentifierExpr::make("y"));

        expr.setArguments(std::move(args));
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<IdentifierExpr>());
        EXPECT_EQ("val", expr.getExpr()->cast<IdentifierExpr>().getName());
        EXPECT_FALSE(expr.getArguments().empty());
        ASSERT_EQ(2, expr.getArguments().size());
        ASSERT_TRUE(expr.getArguments()[0]->is<IdentifierExpr>());
        ASSERT_TRUE(expr.getArguments()[1]->is<IdentifierExpr>());
        EXPECT_EQ("x", expr.getArguments()[0]->cast<IdentifierExpr>().getName());
        EXPECT_EQ("y", expr.getArguments()[1]->cast<IdentifierExpr>().getName());
    }

    {
        // obj[]
        const auto expr = SubscriptExpr::make(IdentifierExpr::make("obj"), {});
        ASSERT_NE(nullptr, expr);

        EXPECT_EQ(ExprKind::Subscript, expr->getKind());
        EXPECT_TRUE(expr->is<SubscriptExpr>());
        ASSERT_NE(nullptr, expr->getExpr());
        ASSERT_TRUE(expr->getExpr()->is<IdentifierExpr>());
        EXPECT_EQ("obj", expr->getExpr()->cast<IdentifierExpr>().getName());
        EXPECT_TRUE(expr->getArguments().empty());
    }
}

/* ************************************************************************ */
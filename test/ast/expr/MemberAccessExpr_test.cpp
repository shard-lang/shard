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

TEST(MemberAccessExpr, base)
{
    {
        // obj.x
        const MemberAccessExpr expr(IdentifierExpr::make("obj"), "x");

        EXPECT_EQ(ExprKind::MemberAccess, expr.getKind());
        EXPECT_TRUE(expr.is<MemberAccessExpr>());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<IdentifierExpr>());
        EXPECT_EQ("obj", expr.getExpr()->cast<IdentifierExpr>().getName());
        EXPECT_EQ("x", expr.getName());
    }

    {
        // obj.x
        MemberAccessExpr expr(IdentifierExpr::make("obj"), "x");

        EXPECT_EQ(ExprKind::MemberAccess, expr.getKind());
        EXPECT_TRUE(expr.is<MemberAccessExpr>());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<IdentifierExpr>());
        EXPECT_EQ("obj", expr.getExpr()->cast<IdentifierExpr>().getName());
        EXPECT_EQ("x", expr.getName());

        // (obj).x
        expr.setExpr(ParenExpr::make(IdentifierExpr::make("obj")));
        EXPECT_TRUE(expr.is<MemberAccessExpr>());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<ParenExpr>());
        EXPECT_EQ("x", expr.getName());

        // (obj).y
        expr.setName("y");
        EXPECT_TRUE(expr.is<MemberAccessExpr>());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<ParenExpr>());
        EXPECT_EQ("y", expr.getName());
    }

    {
        // obj.x
        const auto expr = MemberAccessExpr::make(IdentifierExpr::make("obj"), "x");
        ASSERT_NE(nullptr, expr);

        EXPECT_EQ(ExprKind::MemberAccess, expr->getKind());
        EXPECT_TRUE(expr->is<MemberAccessExpr>());
        ASSERT_NE(nullptr, expr->getExpr());
        ASSERT_TRUE(expr->getExpr()->is<IdentifierExpr>());
        EXPECT_EQ("obj", expr->getExpr()->cast<IdentifierExpr>().getName());
        EXPECT_EQ("x", expr->getName());
    }
}

/* ************************************************************************ */
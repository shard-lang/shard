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
#include "shard/ast/expr/FunctionCallExpr.hpp"
#include "shard/ast/expr/IdentifierExpr.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

TEST(FunctionCallExpr, base)
{
    {
        // obj()
        const FunctionCallExpr expr(IdentifierExpr::make("obj"), {});

        EXPECT_TRUE(expr.is<FunctionCallExpr>());
        ASSERT_NE(nullptr, expr.expr());
        ASSERT_TRUE(expr.expr()->is<IdentifierExpr>());
        EXPECT_EQ("obj", expr.expr()->cast<IdentifierExpr>().name());
        EXPECT_EQ("obj", expr.expr<IdentifierExpr>().name());
        EXPECT_TRUE(expr.args().empty());
        EXPECT_EQ(0, expr.argsCount());
    }

    {
        // obj()
        FunctionCallExpr expr(IdentifierExpr::make("obj"), {});

        EXPECT_TRUE(expr.is<FunctionCallExpr>());
        ASSERT_NE(nullptr, expr.expr());
        ASSERT_TRUE(expr.expr()->is<IdentifierExpr>());
        EXPECT_EQ("obj", expr.expr()->cast<IdentifierExpr>().name());
        EXPECT_TRUE(expr.args().empty());

        // val()
        expr.setExpr(IdentifierExpr::make("val"));
        EXPECT_TRUE(expr.is<FunctionCallExpr>());
        ASSERT_NE(nullptr, expr.expr());
        ASSERT_TRUE(expr.expr()->is<IdentifierExpr>());
        EXPECT_EQ("val", expr.expr()->cast<IdentifierExpr>().name());
        EXPECT_EQ("val", expr.expr<IdentifierExpr>().name());
        EXPECT_TRUE(expr.args().empty());

        // val(x, y)
        ExprPtrVector args;
        args.push_back(IdentifierExpr::make("x"));
        args.push_back(IdentifierExpr::make("y"));

        expr.setArguments(std::move(args));
        ASSERT_NE(nullptr, expr.expr());
        ASSERT_TRUE(expr.expr()->is<IdentifierExpr>());
        EXPECT_EQ("val", expr.expr()->cast<IdentifierExpr>().name());
        EXPECT_FALSE(expr.args().empty());
        ASSERT_EQ(2, expr.args().size());
        ASSERT_TRUE(expr.args()[0]->is<IdentifierExpr>());
        ASSERT_TRUE(expr.args()[1]->is<IdentifierExpr>());
        ASSERT_TRUE(expr.arg(0)->is<IdentifierExpr>());
        ASSERT_TRUE(expr.arg(1)->is<IdentifierExpr>());
        EXPECT_EQ("x", expr.args()[0]->cast<IdentifierExpr>().name());
        EXPECT_EQ("y", expr.args()[1]->cast<IdentifierExpr>().name());
        EXPECT_EQ("x", expr.arg<IdentifierExpr>(0).name());
        EXPECT_EQ("y", expr.arg<IdentifierExpr>(1).name());
    }

    {
        // obj()
        const auto expr = FunctionCallExpr::make(IdentifierExpr::make("obj"), {});
        ASSERT_NE(nullptr, expr);

        EXPECT_TRUE(expr->is<FunctionCallExpr>());
        ASSERT_NE(nullptr, expr->expr());
        ASSERT_TRUE(expr->expr()->is<IdentifierExpr>());
        EXPECT_EQ("obj", expr->expr()->cast<IdentifierExpr>().name());
        EXPECT_EQ("obj", expr->expr<IdentifierExpr>().name());
        EXPECT_TRUE(expr->args().empty());
    }
}

/* ************************************************************************ */
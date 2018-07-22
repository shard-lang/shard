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
#include "shard/ast/expr/StringLiteralExpr.hpp"

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

TEST(StringLiteralExpr, base)
{
    {
        const StringLiteralExpr expr({});

        EXPECT_TRUE(expr.is<StringLiteralExpr>());
        EXPECT_FALSE(expr.is<TestExpr>());
        EXPECT_TRUE(expr.value().empty());
        EXPECT_EQ(StringLiteralExpr::ValueType{}, expr.value());
    }

    {
        const StringLiteralExpr expr("");

        EXPECT_TRUE(expr.is<StringLiteralExpr>());
        EXPECT_FALSE(expr.is<TestExpr>());
        EXPECT_TRUE(expr.value().empty());
        EXPECT_EQ("", expr.value());
    }

    {
        const StringLiteralExpr expr("Hello world");

        EXPECT_TRUE(expr.is<StringLiteralExpr>());
        EXPECT_FALSE(expr.is<TestExpr>());
        EXPECT_FALSE(expr.value().empty());
        EXPECT_EQ("Hello world", expr.value());
    }

    {
        StringLiteralExpr expr({});

        EXPECT_TRUE(expr.is<StringLiteralExpr>());
        EXPECT_FALSE(expr.is<TestExpr>());
        EXPECT_TRUE(expr.value().empty());
        EXPECT_EQ(StringLiteralExpr::ValueType{}, expr.value());

        // Try to change values
        expr.setValue("Hello world");
        EXPECT_EQ("Hello world", expr.value());

        expr.setValue("Maybe");
        EXPECT_EQ("Maybe", expr.value());
    }

    {
        const auto expr = StringLiteralExpr::make({});
        ASSERT_NE(nullptr, expr);

        EXPECT_TRUE(expr->is<StringLiteralExpr>());
        EXPECT_FALSE(expr->is<TestExpr>());
        EXPECT_TRUE(expr->value().empty());
        EXPECT_EQ(StringLiteralExpr::ValueType{}, expr->value());
    }
}

/* ************************************************************************ */
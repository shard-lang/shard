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
#include "shard/ast/expr/CharLiteralExpr.hpp"

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

TEST(CharLiteralExpr, base)
{
    {
        // Zero value
        const CharLiteralExpr expr('\0');

        EXPECT_TRUE(expr.is<CharLiteralExpr>());
        EXPECT_FALSE(expr.is<TestExpr>());
        EXPECT_EQ('\0', expr.value());
    }

    {
        const CharLiteralExpr expr(L'á');

        EXPECT_TRUE(expr.is<CharLiteralExpr>());
        EXPECT_FALSE(expr.is<TestExpr>());
        EXPECT_EQ(L'á', expr.value());
    }

    {
        const CharLiteralExpr expr(L'\xf09eb888');

        EXPECT_TRUE(expr.is<CharLiteralExpr>());
        EXPECT_FALSE(expr.is<TestExpr>());
        EXPECT_EQ(0xf09eb888, expr.value());
    }

    {
        const CharLiteralExpr expr(L'\U0001EE08');

        EXPECT_TRUE(expr.is<CharLiteralExpr>());
        EXPECT_FALSE(expr.is<TestExpr>());
        EXPECT_EQ(0x0001EE08, expr.value());
    }

    {
        // Maximum valid UNICODE code point
        const CharLiteralExpr expr(0x10FFFF);

        EXPECT_TRUE(expr.is<CharLiteralExpr>());
        EXPECT_FALSE(expr.is<TestExpr>());
        EXPECT_EQ(0x10FFFF, expr.value());
    }

    {
        CharLiteralExpr expr(0);

        EXPECT_TRUE(expr.is<CharLiteralExpr>());
        EXPECT_FALSE(expr.is<TestExpr>());
        EXPECT_EQ(0, expr.value());

        // Try to change values
        expr.setValue(0x123);
        EXPECT_EQ(0x123, expr.value());

        expr.setValue(0xFF00);
        EXPECT_EQ(0xFF00, expr.value());
    }

    {
        // Zero value
        const auto expr = CharLiteralExpr::make('\0');
        ASSERT_NE(nullptr, expr);

        EXPECT_TRUE(expr->is<CharLiteralExpr>());
        EXPECT_FALSE(expr->is<TestExpr>());
        EXPECT_EQ('\0', expr->value());
    }
}

/* ************************************************************************ */
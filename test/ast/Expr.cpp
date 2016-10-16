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

TEST(NullLiteralExpr, construction)
{
    {
        const NullLiteralExpr expr;

        EXPECT_EQ(ExprKind::NullLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(NullLiteralExpr::is(expr));
        EXPECT_FALSE(BoolLiteralExpr::is(expr));
        EXPECT_EQ(SourceLocation{}, expr.getSourceStart());
        EXPECT_EQ(SourceLocation{}, expr.getSourceEnd());
    }

    {
        const NullLiteralExpr expr({{123, 456}, {123, 458}});

        EXPECT_EQ(ExprKind::NullLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(NullLiteralExpr::is(expr));
        EXPECT_FALSE(BoolLiteralExpr::is(expr));
        EXPECT_EQ((SourceLocation{123, 456}), expr.getSourceStart());
        EXPECT_EQ((SourceLocation{123, 458}), expr.getSourceEnd());
    }
}

/* ************************************************************************ */

TEST(BoolLiteralExpr, construction)
{
    {
        const BoolLiteralExpr expr(true);

        EXPECT_EQ(ExprKind::BoolLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_FALSE(NullLiteralExpr::is(expr));
        EXPECT_TRUE(BoolLiteralExpr::is(expr));
        EXPECT_TRUE(expr.getValue());
    }

    {
        const BoolLiteralExpr expr(false);

        EXPECT_EQ(ExprKind::BoolLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_FALSE(NullLiteralExpr::is(expr));
        EXPECT_TRUE(BoolLiteralExpr::is(expr));
        EXPECT_FALSE(expr.getValue());
    }
}

/* ************************************************************************ */

TEST(IntLiteralExpr, construction)
{
    {
        const IntLiteralExpr expr(0);

        EXPECT_EQ(ExprKind::IntLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(NumberLiteralExpr::is(expr));
        EXPECT_TRUE(IntLiteralExpr::is(expr));
        EXPECT_FALSE(FloatLiteralExpr::is(expr));
        EXPECT_EQ(0, expr.getValue());
    }

    {
        const IntLiteralExpr expr(123);

        EXPECT_EQ(ExprKind::IntLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(NumberLiteralExpr::is(expr));
        EXPECT_TRUE(IntLiteralExpr::is(expr));
        EXPECT_FALSE(FloatLiteralExpr::is(expr));
        EXPECT_EQ(123, expr.getValue());
    }

    {
        const IntLiteralExpr expr(std::numeric_limits<IntLiteralExpr::ValueType>::min());

        EXPECT_EQ(ExprKind::IntLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(NumberLiteralExpr::is(expr));
        EXPECT_TRUE(IntLiteralExpr::is(expr));
        EXPECT_FALSE(FloatLiteralExpr::is(expr));
        EXPECT_EQ(std::numeric_limits<IntLiteralExpr::ValueType>::min(), expr.getValue());
    }

    {
        const IntLiteralExpr expr(std::numeric_limits<IntLiteralExpr::ValueType>::max());

        EXPECT_EQ(ExprKind::IntLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(NumberLiteralExpr::is(expr));
        EXPECT_TRUE(IntLiteralExpr::is(expr));
        EXPECT_FALSE(FloatLiteralExpr::is(expr));
        EXPECT_EQ(std::numeric_limits<IntLiteralExpr::ValueType>::max(), expr.getValue());
    }
}

/* ************************************************************************ */

TEST(FloatLiteralExpr, construction)
{
    {
        const FloatLiteralExpr expr(0);

        EXPECT_EQ(ExprKind::FloatLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(NumberLiteralExpr::is(expr));
        EXPECT_TRUE(FloatLiteralExpr::is(expr));
        EXPECT_FALSE(IntLiteralExpr::is(expr));
        EXPECT_FLOAT_EQ(0, expr.getValue());
    }

    {
        const FloatLiteralExpr expr(0.111);

        EXPECT_EQ(ExprKind::FloatLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(NumberLiteralExpr::is(expr));
        EXPECT_TRUE(FloatLiteralExpr::is(expr));
        EXPECT_FALSE(IntLiteralExpr::is(expr));
        EXPECT_FLOAT_EQ(0.111, expr.getValue());
    }

    {
        const FloatLiteralExpr expr(std::numeric_limits<FloatLiteralExpr::ValueType>::min());

        EXPECT_EQ(ExprKind::FloatLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(NumberLiteralExpr::is(expr));
        EXPECT_TRUE(FloatLiteralExpr::is(expr));
        EXPECT_FALSE(IntLiteralExpr::is(expr));
        EXPECT_FLOAT_EQ(std::numeric_limits<FloatLiteralExpr::ValueType>::min(), expr.getValue());
    }

    {
        const FloatLiteralExpr expr(std::numeric_limits<FloatLiteralExpr::ValueType>::max());

        EXPECT_EQ(ExprKind::FloatLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(NumberLiteralExpr::is(expr));
        EXPECT_TRUE(FloatLiteralExpr::is(expr));
        EXPECT_FALSE(IntLiteralExpr::is(expr));
        EXPECT_FLOAT_EQ(std::numeric_limits<FloatLiteralExpr::ValueType>::max(), expr.getValue());
    }
}

/* ************************************************************************ */

TEST(CharLiteralExpr, construction)
{
    {
        const CharLiteralExpr expr('\0');

        EXPECT_EQ(ExprKind::CharLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(CharLiteralExpr::is(expr));
        EXPECT_FALSE(NumberLiteralExpr::is(expr));
        EXPECT_FALSE(IntLiteralExpr::is(expr));
        EXPECT_EQ('\0', expr.getValue());
    }

    {
        const CharLiteralExpr expr(L'á');

        EXPECT_EQ(ExprKind::CharLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(CharLiteralExpr::is(expr));
        EXPECT_FALSE(NumberLiteralExpr::is(expr));
        EXPECT_FALSE(IntLiteralExpr::is(expr));
        EXPECT_EQ(L'á', expr.getValue());
    }

    {
        const CharLiteralExpr expr(L'\xf09eb888');

        EXPECT_EQ(ExprKind::CharLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(CharLiteralExpr::is(expr));
        EXPECT_FALSE(NumberLiteralExpr::is(expr));
        EXPECT_FALSE(IntLiteralExpr::is(expr));
        EXPECT_EQ(0xf09eb888, expr.getValue());
    }

    {
        const CharLiteralExpr expr(L'\U0001EE08');

        EXPECT_EQ(ExprKind::CharLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(CharLiteralExpr::is(expr));
        EXPECT_FALSE(NumberLiteralExpr::is(expr));
        EXPECT_FALSE(IntLiteralExpr::is(expr));
        EXPECT_EQ(0x0001EE08, expr.getValue());
    }
}

/* ************************************************************************ */

TEST(StringLiteralExpr, construction)
{
    {
        const StringLiteralExpr expr({});

        EXPECT_EQ(ExprKind::StringLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(StringLiteralExpr::is(expr));
        EXPECT_FALSE(NumberLiteralExpr::is(expr));
        EXPECT_TRUE(expr.getValue().empty());
        EXPECT_EQ("", expr.getValue());
    }

    {
        const StringLiteralExpr expr("");

        EXPECT_EQ(ExprKind::StringLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(StringLiteralExpr::is(expr));
        EXPECT_FALSE(NumberLiteralExpr::is(expr));
        EXPECT_TRUE(expr.getValue().empty());
        EXPECT_EQ("", expr.getValue());
    }

    {
        const StringLiteralExpr expr("Hello world");

        EXPECT_EQ(ExprKind::StringLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(StringLiteralExpr::is(expr));
        EXPECT_FALSE(NumberLiteralExpr::is(expr));
        EXPECT_FALSE(expr.getValue().empty());
        EXPECT_EQ("Hello world", expr.getValue());
    }
}

/* ************************************************************************ */

TEST(BinaryExpr, construction)
{
    {
        // 5 + 2
        const BinaryExpr expr(BinaryExpr::Operator::Add, makeUnique<IntLiteralExpr>(5), makeUnique<IntLiteralExpr>(2));

        EXPECT_EQ(ExprKind::Binary, expr.getKind());
        EXPECT_TRUE(BinaryExpr::is(expr));
        EXPECT_FALSE(LiteralExpr::is(expr));
        EXPECT_EQ(BinaryExpr::Operator::Add, expr.getOperator());
        ASSERT_TRUE(expr.getLeftOperand());
        ASSERT_TRUE(expr.getRightOperand());
        ASSERT_TRUE(IntLiteralExpr::is(expr.getLeftOperand()));
        ASSERT_TRUE(IntLiteralExpr::is(expr.getRightOperand()));
        EXPECT_EQ(5, IntLiteralExpr::cast(expr.getLeftOperand())->getValue());
        EXPECT_EQ(2, IntLiteralExpr::cast(expr.getRightOperand())->getValue());
    }

    {
        // 10 * 4.0
        const BinaryExpr expr(BinaryExpr::Operator::Multiply, makeUnique<IntLiteralExpr>(10), makeUnique<FloatLiteralExpr>(4.0));

        EXPECT_EQ(ExprKind::Binary, expr.getKind());
        EXPECT_TRUE(BinaryExpr::is(expr));
        EXPECT_FALSE(LiteralExpr::is(expr));
        EXPECT_EQ(BinaryExpr::Operator::Multiply, expr.getOperator());
        ASSERT_TRUE(expr.getLeftOperand());
        ASSERT_TRUE(expr.getRightOperand());
        ASSERT_TRUE(IntLiteralExpr::is(expr.getLeftOperand()));
        ASSERT_TRUE(FloatLiteralExpr::is(expr.getRightOperand()));
        EXPECT_EQ(10, IntLiteralExpr::cast(expr.getLeftOperand())->getValue());
        EXPECT_FLOAT_EQ(4.0, FloatLiteralExpr::cast(expr.getRightOperand())->getValue());
    }
}

/* ************************************************************************ */

TEST(PrefixUnaryExpr, construction)
{
    {
        // !true
        const PrefixUnaryExpr expr(PrefixUnaryExpr::Operator::Negate, makeUnique<BoolLiteralExpr>(true));

        EXPECT_EQ(ExprKind::PrefixUnary, expr.getKind());
        EXPECT_TRUE(PrefixUnaryExpr::is(expr));
        EXPECT_EQ(PrefixUnaryExpr::Operator::Negate, expr.getOperator());
        ASSERT_TRUE(expr.getOperand());
        ASSERT_TRUE(BoolLiteralExpr::is(expr.getOperand()));
        EXPECT_TRUE(BoolLiteralExpr::cast(expr.getOperand())->getValue());
    }

    {
        // -10
        const PrefixUnaryExpr expr(PrefixUnaryExpr::Operator::Minus, makeUnique<IntLiteralExpr>(10));

        EXPECT_EQ(ExprKind::PrefixUnary, expr.getKind());
        EXPECT_TRUE(PrefixUnaryExpr::is(expr));
        EXPECT_EQ(PrefixUnaryExpr::Operator::Minus, expr.getOperator());
        ASSERT_TRUE(expr.getOperand());
        ASSERT_TRUE(IntLiteralExpr::is(expr.getOperand()));
        EXPECT_EQ(10, IntLiteralExpr::cast(expr.getOperand())->getValue());
    }
}

/* ************************************************************************ */

TEST(PostfixUnaryExpr, construction)
{
    {
        // 5++
        const PostfixUnaryExpr expr(PostfixUnaryExpr::Operator::Increment, makeUnique<IntLiteralExpr>(5));

        EXPECT_EQ(ExprKind::PostfixUnary, expr.getKind());
        EXPECT_TRUE(PostfixUnaryExpr::is(expr));
        EXPECT_EQ(PostfixUnaryExpr::Operator::Increment, expr.getOperator());
        ASSERT_TRUE(expr.getOperand());
        ASSERT_TRUE(IntLiteralExpr::is(expr.getOperand()));
        EXPECT_EQ(5, IntLiteralExpr::cast(expr.getOperand())->getValue());
    }

    {
        // true--
        const PostfixUnaryExpr expr(PostfixUnaryExpr::Operator::Decrement, makeUnique<BoolLiteralExpr>(true));

        EXPECT_EQ(ExprKind::PostfixUnary, expr.getKind());
        EXPECT_TRUE(PostfixUnaryExpr::is(expr));
        EXPECT_EQ(PostfixUnaryExpr::Operator::Decrement, expr.getOperator());
        ASSERT_TRUE(expr.getOperand());
        ASSERT_TRUE(BoolLiteralExpr::is(expr.getOperand()));
        EXPECT_TRUE(BoolLiteralExpr::cast(expr.getOperand())->getValue());
    }
}

/* ************************************************************************ */

TEST(TernaryExpr, construction)
{
    {
        // true ? 1 : 2
        const TernaryExpr expr(makeUnique<BoolLiteralExpr>(true), makeUnique<IntLiteralExpr>(1), makeUnique<IntLiteralExpr>(2));

        EXPECT_EQ(ExprKind::Ternary, expr.getKind());
        EXPECT_TRUE(TernaryExpr::is(expr));
        ASSERT_TRUE(expr.getCondExpr());
        ASSERT_TRUE(expr.getTrueExpr());
        ASSERT_TRUE(expr.getFalseExpr());
        ASSERT_TRUE(BoolLiteralExpr::is(expr.getCondExpr()));
        ASSERT_TRUE(IntLiteralExpr::is(expr.getTrueExpr()));
        ASSERT_TRUE(IntLiteralExpr::is(expr.getFalseExpr()));
        EXPECT_TRUE(BoolLiteralExpr::cast(expr.getCondExpr())->getValue());
        EXPECT_EQ(1, IntLiteralExpr::cast(expr.getTrueExpr())->getValue());
        EXPECT_EQ(2, IntLiteralExpr::cast(expr.getFalseExpr())->getValue());
    }
}

/* ************************************************************************ */

TEST(ParenExpr, construction)
{
    {
        // (5)
        const ParenExpr expr(makeUnique<IntLiteralExpr>(5));

        EXPECT_EQ(ExprKind::Paren, expr.getKind());
        EXPECT_TRUE(ParenExpr::is(expr));
        ASSERT_TRUE(expr.getExpr());
        ASSERT_TRUE(IntLiteralExpr::is(expr.getExpr()));
        EXPECT_EQ(5, IntLiteralExpr::cast(expr.getExpr())->getValue());
    }

    {
        // ((true))
        const ParenExpr expr(makeUnique<ParenExpr>(makeUnique<BoolLiteralExpr>(true)));

        EXPECT_EQ(ExprKind::Paren, expr.getKind());
        EXPECT_TRUE(ParenExpr::is(expr));
        ASSERT_TRUE(expr.getExpr());
        ASSERT_TRUE(ParenExpr::is(expr.getExpr()));
        ASSERT_TRUE(ParenExpr::cast(expr.getExpr())->getExpr());
        ASSERT_TRUE(BoolLiteralExpr::cast(ParenExpr::cast(expr.getExpr())->getExpr()));
        EXPECT_TRUE(BoolLiteralExpr::cast(ParenExpr::cast(expr.getExpr())->getExpr())->getValue());
    }
}

/* ************************************************************************ */

TEST(IdentifierExpr, construction)
{
    {
        // id
        const IdentifierExpr expr("id");

        EXPECT_EQ(ExprKind::Identifier, expr.getKind());
        EXPECT_TRUE(IdentifierExpr::is(expr));
        ASSERT_FALSE(expr.getName().empty());
        EXPECT_EQ("id", expr.getName());
    }

#if !defined(NDEBUG) && !defined(_WIN32)
    {
        // empty
        EXPECT_EXIT({ const IdentifierExpr expr(""); }, ::testing::KilledBySignal(SIGABRT), ".*");
    }
#endif
}

/* ************************************************************************ */
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

TEST(NullLiteralExpr, base)
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

TEST(BoolLiteralExpr, base)
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

    {
        BoolLiteralExpr expr(false);

        EXPECT_EQ(ExprKind::BoolLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_FALSE(NullLiteralExpr::is(expr));
        EXPECT_TRUE(BoolLiteralExpr::is(expr));
        EXPECT_FALSE(expr.getValue());

        // Try to change value
        expr.setValue(true);
        EXPECT_TRUE(expr.getValue());

        expr.setValue(false);
        EXPECT_FALSE(expr.getValue());
    }
}

/* ************************************************************************ */

TEST(IntLiteralExpr, base)
{
    {
        // Zero value
        const IntLiteralExpr expr(0);

        EXPECT_EQ(ExprKind::IntLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(NumberLiteralExpr::is(expr));
        EXPECT_TRUE(IntLiteralExpr::is(expr));
        EXPECT_FALSE(FloatLiteralExpr::is(expr));
        EXPECT_EQ(0, expr.getValue());
    }

    {
        // Random value
        const IntLiteralExpr expr(123);

        EXPECT_EQ(ExprKind::IntLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(NumberLiteralExpr::is(expr));
        EXPECT_TRUE(IntLiteralExpr::is(expr));
        EXPECT_FALSE(FloatLiteralExpr::is(expr));
        EXPECT_EQ(123, expr.getValue());
    }

    {
        // Min value
        const IntLiteralExpr expr(std::numeric_limits<IntLiteralExpr::ValueType>::min());

        EXPECT_EQ(ExprKind::IntLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(NumberLiteralExpr::is(expr));
        EXPECT_TRUE(IntLiteralExpr::is(expr));
        EXPECT_FALSE(FloatLiteralExpr::is(expr));
        EXPECT_EQ(std::numeric_limits<IntLiteralExpr::ValueType>::min(), expr.getValue());
    }

    {
        // Max value
        const IntLiteralExpr expr(std::numeric_limits<IntLiteralExpr::ValueType>::max());

        EXPECT_EQ(ExprKind::IntLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(NumberLiteralExpr::is(expr));
        EXPECT_TRUE(IntLiteralExpr::is(expr));
        EXPECT_FALSE(FloatLiteralExpr::is(expr));
        EXPECT_EQ(std::numeric_limits<IntLiteralExpr::ValueType>::max(), expr.getValue());
    }

    {
        IntLiteralExpr expr(0);

        EXPECT_EQ(ExprKind::IntLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(NumberLiteralExpr::is(expr));
        EXPECT_TRUE(IntLiteralExpr::is(expr));
        EXPECT_FALSE(FloatLiteralExpr::is(expr));
        EXPECT_EQ(0, expr.getValue());

        // Try to change values
        expr.setValue(4877);
        EXPECT_EQ(4877, expr.getValue());

        expr.setValue(-488932);
        EXPECT_EQ(-488932, expr.getValue());
    }

}

/* ************************************************************************ */

TEST(FloatLiteralExpr, base)
{
    {
        // Zero value
        const FloatLiteralExpr expr(0);

        EXPECT_EQ(ExprKind::FloatLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(NumberLiteralExpr::is(expr));
        EXPECT_TRUE(FloatLiteralExpr::is(expr));
        EXPECT_FALSE(IntLiteralExpr::is(expr));
        EXPECT_FLOAT_EQ(0, expr.getValue());
    }

    {
        // Random value
        const FloatLiteralExpr expr(0.111);

        EXPECT_EQ(ExprKind::FloatLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(NumberLiteralExpr::is(expr));
        EXPECT_TRUE(FloatLiteralExpr::is(expr));
        EXPECT_FALSE(IntLiteralExpr::is(expr));
        EXPECT_FLOAT_EQ(0.111, expr.getValue());
    }

    {
        // Min value
        const FloatLiteralExpr expr(std::numeric_limits<FloatLiteralExpr::ValueType>::min());

        EXPECT_EQ(ExprKind::FloatLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(NumberLiteralExpr::is(expr));
        EXPECT_TRUE(FloatLiteralExpr::is(expr));
        EXPECT_FALSE(IntLiteralExpr::is(expr));
        EXPECT_FLOAT_EQ(std::numeric_limits<FloatLiteralExpr::ValueType>::min(), expr.getValue());
    }

    {
        // Max value
        const FloatLiteralExpr expr(std::numeric_limits<FloatLiteralExpr::ValueType>::max());

        EXPECT_EQ(ExprKind::FloatLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(NumberLiteralExpr::is(expr));
        EXPECT_TRUE(FloatLiteralExpr::is(expr));
        EXPECT_FALSE(IntLiteralExpr::is(expr));
        EXPECT_FLOAT_EQ(std::numeric_limits<FloatLiteralExpr::ValueType>::max(), expr.getValue());
    }

    {
        FloatLiteralExpr expr(0);

        EXPECT_EQ(ExprKind::FloatLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(NumberLiteralExpr::is(expr));
        EXPECT_TRUE(FloatLiteralExpr::is(expr));
        EXPECT_FALSE(IntLiteralExpr::is(expr));
        EXPECT_FLOAT_EQ(0, expr.getValue());

        // Try to change values
        expr.setValue(0.456e5);
        EXPECT_FLOAT_EQ(0.456e5, expr.getValue());

        expr.setValue(-756e45);
        EXPECT_FLOAT_EQ(-756e45, expr.getValue());
    }

}

/* ************************************************************************ */

TEST(CharLiteralExpr, base)
{
    {
        // Zero value
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

    {
        // Maximum valid UNICODE code point
        const CharLiteralExpr expr(0x10FFFF);

        EXPECT_EQ(ExprKind::CharLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(CharLiteralExpr::is(expr));
        EXPECT_FALSE(NumberLiteralExpr::is(expr));
        EXPECT_FALSE(IntLiteralExpr::is(expr));
        EXPECT_EQ(0x10FFFF, expr.getValue());
    }

    {
        CharLiteralExpr expr(0);

        EXPECT_EQ(ExprKind::CharLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(CharLiteralExpr::is(expr));
        EXPECT_FALSE(NumberLiteralExpr::is(expr));
        EXPECT_FALSE(IntLiteralExpr::is(expr));
        EXPECT_EQ(0, expr.getValue());

        // Try to change values
        expr.setValue(0x123);
        EXPECT_EQ(0x123, expr.getValue());

        expr.setValue(0xFF00);
        EXPECT_EQ(0xFF00, expr.getValue());
    }

}

/* ************************************************************************ */

TEST(StringLiteralExpr, base)
{
    {
        const StringLiteralExpr expr({});

        EXPECT_EQ(ExprKind::StringLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(StringLiteralExpr::is(expr));
        EXPECT_FALSE(NumberLiteralExpr::is(expr));
        EXPECT_TRUE(expr.getValue().empty());
        EXPECT_EQ(StringLiteralExpr::ValueType{}, expr.getValue());
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

    {
        StringLiteralExpr expr({});

        EXPECT_EQ(ExprKind::StringLiteral, expr.getKind());
        EXPECT_TRUE(LiteralExpr::is(expr));
        EXPECT_TRUE(StringLiteralExpr::is(expr));
        EXPECT_FALSE(NumberLiteralExpr::is(expr));
        EXPECT_TRUE(expr.getValue().empty());
        EXPECT_EQ(StringLiteralExpr::ValueType{}, expr.getValue());

        // Try to change values
        expr.setValue("Hello world");
        EXPECT_EQ("Hello world", expr.getValue());

        expr.setValue("Maybe");
        EXPECT_EQ("Maybe", expr.getValue());
    }
}

/* ************************************************************************ */

TEST(BinaryExpr, base)
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

    {
        // 10 * 4.0
        BinaryExpr expr(BinaryExpr::Operator::Multiply, makeUnique<IntLiteralExpr>(10), makeUnique<FloatLiteralExpr>(4.0));

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

        // 10 + 4.0
        expr.setOperator(BinaryExpr::Operator::Add);
        EXPECT_EQ(BinaryExpr::Operator::Add, expr.getOperator());
        ASSERT_TRUE(expr.getLeftOperand());
        ASSERT_TRUE(expr.getRightOperand());
        ASSERT_TRUE(IntLiteralExpr::is(expr.getLeftOperand()));
        ASSERT_TRUE(FloatLiteralExpr::is(expr.getRightOperand()));
        EXPECT_EQ(10, IntLiteralExpr::cast(expr.getLeftOperand())->getValue());
        EXPECT_FLOAT_EQ(4.0, FloatLiteralExpr::cast(expr.getRightOperand())->getValue());

        // 10 - 4.0
        expr.setOperator(BinaryExpr::Operator::Subtract);
        EXPECT_EQ(BinaryExpr::Operator::Subtract, expr.getOperator());
        ASSERT_TRUE(expr.getLeftOperand());
        ASSERT_TRUE(expr.getRightOperand());
        ASSERT_TRUE(IntLiteralExpr::is(expr.getLeftOperand()));
        ASSERT_TRUE(FloatLiteralExpr::is(expr.getRightOperand()));
        EXPECT_EQ(10, IntLiteralExpr::cast(expr.getLeftOperand())->getValue());
        EXPECT_FLOAT_EQ(4.0, FloatLiteralExpr::cast(expr.getRightOperand())->getValue());

        // 1.0 - 4.0
        expr.setLeftOperand(makeUnique<FloatLiteralExpr>(1.0));
        EXPECT_EQ(BinaryExpr::Operator::Subtract, expr.getOperator());
        ASSERT_TRUE(expr.getLeftOperand());
        ASSERT_TRUE(expr.getRightOperand());
        ASSERT_TRUE(FloatLiteralExpr::is(expr.getLeftOperand()));
        ASSERT_TRUE(FloatLiteralExpr::is(expr.getRightOperand()));
        EXPECT_FLOAT_EQ(1.0, FloatLiteralExpr::cast(expr.getLeftOperand())->getValue());
        EXPECT_FLOAT_EQ(4.0, FloatLiteralExpr::cast(expr.getRightOperand())->getValue());

        expr.setRightOperand(makeUnique<FloatLiteralExpr>(50.3));
        EXPECT_EQ(BinaryExpr::Operator::Subtract, expr.getOperator());
        ASSERT_TRUE(expr.getLeftOperand());
        ASSERT_TRUE(expr.getRightOperand());
        ASSERT_TRUE(FloatLiteralExpr::is(expr.getLeftOperand()));
        ASSERT_TRUE(FloatLiteralExpr::is(expr.getRightOperand()));
        EXPECT_FLOAT_EQ(1.0, FloatLiteralExpr::cast(expr.getLeftOperand())->getValue());
        EXPECT_FLOAT_EQ(50.3, FloatLiteralExpr::cast(expr.getRightOperand())->getValue());
    }
}

/* ************************************************************************ */

TEST(PrefixUnaryExpr, base)
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

    {
        // -10
        PrefixUnaryExpr expr(PrefixUnaryExpr::Operator::Minus, makeUnique<IntLiteralExpr>(0));

        EXPECT_EQ(ExprKind::PrefixUnary, expr.getKind());
        EXPECT_TRUE(PrefixUnaryExpr::is(expr));
        EXPECT_EQ(PrefixUnaryExpr::Operator::Minus, expr.getOperator());
        ASSERT_TRUE(expr.getOperand());
        ASSERT_TRUE(IntLiteralExpr::is(expr.getOperand()));
        EXPECT_EQ(0, IntLiteralExpr::cast(expr.getOperand())->getValue());

        // !0
        expr.setOperator(PrefixUnaryExpr::Operator::Negate);
        EXPECT_EQ(ExprKind::PrefixUnary, expr.getKind());
        EXPECT_TRUE(PrefixUnaryExpr::is(expr));
        EXPECT_EQ(PrefixUnaryExpr::Operator::Negate, expr.getOperator());
        ASSERT_TRUE(expr.getOperand());
        ASSERT_TRUE(IntLiteralExpr::is(expr.getOperand()));
        EXPECT_EQ(0, IntLiteralExpr::cast(expr.getOperand())->getValue());

        // !true
        expr.setOperand(makeUnique<BoolLiteralExpr>(true));
        EXPECT_EQ(ExprKind::PrefixUnary, expr.getKind());
        EXPECT_TRUE(PrefixUnaryExpr::is(expr));
        EXPECT_EQ(PrefixUnaryExpr::Operator::Negate, expr.getOperator());
        ASSERT_TRUE(expr.getOperand());
        ASSERT_TRUE(BoolLiteralExpr::is(expr.getOperand()));
        EXPECT_TRUE(BoolLiteralExpr::cast(expr.getOperand())->getValue());
    }
}

/* ************************************************************************ */

TEST(PostfixUnaryExpr, base)
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

    {
        // i--
        PostfixUnaryExpr expr(PostfixUnaryExpr::Operator::Decrement, makeUnique<IdentifierExpr>("i"));

        EXPECT_EQ(ExprKind::PostfixUnary, expr.getKind());
        EXPECT_TRUE(PostfixUnaryExpr::is(expr));
        EXPECT_EQ(PostfixUnaryExpr::Operator::Decrement, expr.getOperator());
        ASSERT_TRUE(expr.getOperand());
        ASSERT_TRUE(IdentifierExpr::is(expr.getOperand()));
        EXPECT_EQ("i", IdentifierExpr::cast(expr.getOperand())->getName());

        // i++
        expr.setOperator(PostfixUnaryExpr::Operator::Increment);
        EXPECT_EQ(ExprKind::PostfixUnary, expr.getKind());
        EXPECT_TRUE(PostfixUnaryExpr::is(expr));
        EXPECT_EQ(PostfixUnaryExpr::Operator::Increment, expr.getOperator());
        ASSERT_TRUE(expr.getOperand());
        ASSERT_TRUE(IdentifierExpr::is(expr.getOperand()));
        EXPECT_EQ("i", IdentifierExpr::cast(expr.getOperand())->getName());

        // "i"++
        expr.setOperand(makeUnique<StringLiteralExpr>("i"));
        EXPECT_EQ(ExprKind::PostfixUnary, expr.getKind());
        EXPECT_TRUE(PostfixUnaryExpr::is(expr));
        EXPECT_EQ(PostfixUnaryExpr::Operator::Increment, expr.getOperator());
        ASSERT_TRUE(expr.getOperand());
        ASSERT_TRUE(StringLiteralExpr::is(expr.getOperand()));
        EXPECT_EQ("i", StringLiteralExpr::cast(expr.getOperand())->getValue());
    }
}

/* ************************************************************************ */

TEST(TernaryExpr, base)
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

    {
        // true ? 1 : 2
        TernaryExpr expr(makeUnique<BoolLiteralExpr>(true), makeUnique<IntLiteralExpr>(1), makeUnique<IntLiteralExpr>(2));

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

        // cond ? 1 : 2
        expr.setCondExpr(makeUnique<IdentifierExpr>("cond"));
        EXPECT_TRUE(TernaryExpr::is(expr));
        ASSERT_TRUE(expr.getCondExpr());
        ASSERT_TRUE(expr.getTrueExpr());
        ASSERT_TRUE(expr.getFalseExpr());
        ASSERT_TRUE(IdentifierExpr::is(expr.getCondExpr()));
        ASSERT_TRUE(IntLiteralExpr::is(expr.getTrueExpr()));
        ASSERT_TRUE(IntLiteralExpr::is(expr.getFalseExpr()));
        EXPECT_EQ("cond", IdentifierExpr::cast(expr.getCondExpr())->getName());
        EXPECT_EQ(1, IntLiteralExpr::cast(expr.getTrueExpr())->getValue());
        EXPECT_EQ(2, IntLiteralExpr::cast(expr.getFalseExpr())->getValue());

        // cond ? true : 2
        expr.setTrueExpr(makeUnique<BoolLiteralExpr>(true));
        EXPECT_TRUE(TernaryExpr::is(expr));
        ASSERT_TRUE(expr.getCondExpr());
        ASSERT_TRUE(expr.getTrueExpr());
        ASSERT_TRUE(expr.getFalseExpr());
        ASSERT_TRUE(IdentifierExpr::is(expr.getCondExpr()));
        ASSERT_TRUE(BoolLiteralExpr::is(expr.getTrueExpr()));
        ASSERT_TRUE(IntLiteralExpr::is(expr.getFalseExpr()));
        EXPECT_EQ("cond", IdentifierExpr::cast(expr.getCondExpr())->getName());
        EXPECT_TRUE(BoolLiteralExpr::cast(expr.getTrueExpr())->getValue());
        EXPECT_EQ(2, IntLiteralExpr::cast(expr.getFalseExpr())->getValue());

        // cond ? true : false
        expr.setFalseExpr(makeUnique<BoolLiteralExpr>(false));
        EXPECT_TRUE(TernaryExpr::is(expr));
        ASSERT_TRUE(expr.getCondExpr());
        ASSERT_TRUE(expr.getTrueExpr());
        ASSERT_TRUE(expr.getFalseExpr());
        ASSERT_TRUE(IdentifierExpr::is(expr.getCondExpr()));
        ASSERT_TRUE(BoolLiteralExpr::is(expr.getTrueExpr()));
        ASSERT_TRUE(BoolLiteralExpr::is(expr.getFalseExpr()));
        EXPECT_EQ("cond", IdentifierExpr::cast(expr.getCondExpr())->getName());
        EXPECT_TRUE(BoolLiteralExpr::cast(expr.getTrueExpr())->getValue());
        EXPECT_FALSE(BoolLiteralExpr::cast(expr.getFalseExpr())->getValue());
    }
}

/* ************************************************************************ */

TEST(ParenExpr, base)
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

    {
        // (5)
        ParenExpr expr(makeUnique<IntLiteralExpr>(5));

        EXPECT_EQ(ExprKind::Paren, expr.getKind());
        EXPECT_TRUE(ParenExpr::is(expr));
        ASSERT_TRUE(expr.getExpr());
        ASSERT_TRUE(IntLiteralExpr::is(expr.getExpr()));
        EXPECT_EQ(5, IntLiteralExpr::cast(expr.getExpr())->getValue());

        // (true)
        expr.setExpr(makeUnique<BoolLiteralExpr>(true));
        EXPECT_EQ(ExprKind::Paren, expr.getKind());
        EXPECT_TRUE(ParenExpr::is(expr));
        ASSERT_TRUE(expr.getExpr());
        ASSERT_TRUE(BoolLiteralExpr::is(expr.getExpr()));
        EXPECT_TRUE(BoolLiteralExpr::cast(expr.getExpr())->getValue());
    }

}

/* ************************************************************************ */

TEST(IdentifierExpr, base)
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

    {
        // id
        IdentifierExpr expr("id");

        EXPECT_EQ(ExprKind::Identifier, expr.getKind());
        EXPECT_TRUE(IdentifierExpr::is(expr));
        ASSERT_FALSE(expr.getName().empty());
        EXPECT_EQ("id", expr.getName());

        expr.setName("my_id");
        EXPECT_EQ("my_id", expr.getName());
    }

}

/* ************************************************************************ */

TEST(MemberAccessExpr, base)
{
    {
        // obj.x
        const MemberAccessExpr expr(makeUnique<IdentifierExpr>("obj"), "x");

        EXPECT_EQ(ExprKind::MemberAccess, expr.getKind());
        EXPECT_TRUE(MemberAccessExpr::is(expr));
        ASSERT_TRUE(expr.getExpr());
        ASSERT_TRUE(IdentifierExpr::is(expr.getExpr()));
        EXPECT_EQ("obj", IdentifierExpr::cast(expr.getExpr())->getName());
        EXPECT_EQ("x", expr.getName());
    }

    {
        // obj.x
        MemberAccessExpr expr(makeUnique<IdentifierExpr>("obj"), "x");

        EXPECT_EQ(ExprKind::MemberAccess, expr.getKind());
        EXPECT_TRUE(MemberAccessExpr::is(expr));
        ASSERT_TRUE(expr.getExpr());
        ASSERT_TRUE(IdentifierExpr::is(expr.getExpr()));
        EXPECT_EQ("obj", IdentifierExpr::cast(expr.getExpr())->getName());
        EXPECT_EQ("x", expr.getName());

        // (obj).x
        expr.setExpr(makeUnique<ParenExpr>(makeUnique<IdentifierExpr>("obj")));
        EXPECT_TRUE(MemberAccessExpr::is(expr));
        ASSERT_TRUE(expr.getExpr());
        ASSERT_TRUE(ParenExpr::is(expr.getExpr()));
        EXPECT_EQ("x", expr.getName());

        // (obj).y
        expr.setName("y");
        EXPECT_TRUE(MemberAccessExpr::is(expr));
        ASSERT_TRUE(expr.getExpr());
        ASSERT_TRUE(ParenExpr::is(expr.getExpr()));
        EXPECT_EQ("y", expr.getName());
    }
}

/* ************************************************************************ */

TEST(FunctionCallExpr, base)
{
    {
        // obj()
        const FunctionCallExpr expr(makeUnique<IdentifierExpr>("obj"), {});

        EXPECT_EQ(ExprKind::FunctionCall, expr.getKind());
        EXPECT_TRUE(FunctionCallExpr::is(expr));
        ASSERT_TRUE(expr.getExpr());
        ASSERT_TRUE(IdentifierExpr::is(expr.getExpr()));
        EXPECT_EQ("obj", IdentifierExpr::cast(expr.getExpr())->getName());
        EXPECT_TRUE(expr.getArguments().empty());
    }

    {
        // obj()
        FunctionCallExpr expr(makeUnique<IdentifierExpr>("obj"), {});

        EXPECT_EQ(ExprKind::FunctionCall, expr.getKind());
        EXPECT_TRUE(FunctionCallExpr::is(expr));
        ASSERT_TRUE(expr.getExpr());
        ASSERT_TRUE(IdentifierExpr::is(expr.getExpr()));
        EXPECT_EQ("obj", IdentifierExpr::cast(expr.getExpr())->getName());
        EXPECT_TRUE(expr.getArguments().empty());

        // val()
        expr.setExpr(makeUnique<IdentifierExpr>("val"));
        EXPECT_TRUE(FunctionCallExpr::is(expr));
        ASSERT_TRUE(expr.getExpr());
        ASSERT_TRUE(IdentifierExpr::is(expr.getExpr()));
        EXPECT_EQ("val", IdentifierExpr::cast(expr.getExpr())->getName());
        EXPECT_TRUE(expr.getArguments().empty());

        // val(x, y)
        PtrDynamicArray<Expr> args;
        args.push_back(makeUnique<IdentifierExpr>("x"));
        args.push_back(makeUnique<IdentifierExpr>("y"));

        expr.setArguments(moveValue(args));
        ASSERT_TRUE(expr.getExpr());
        ASSERT_TRUE(IdentifierExpr::is(expr.getExpr()));
        EXPECT_EQ("val", IdentifierExpr::cast(expr.getExpr())->getName());
        EXPECT_FALSE(expr.getArguments().empty());
        ASSERT_EQ(2, expr.getArguments().size());
        ASSERT_TRUE(IdentifierExpr::is(expr.getArguments()[0]));
        ASSERT_TRUE(IdentifierExpr::is(expr.getArguments()[1]));
        EXPECT_EQ("x", IdentifierExpr::cast(expr.getArguments()[0])->getName());
        EXPECT_EQ("y", IdentifierExpr::cast(expr.getArguments()[1])->getName());
    }
}

/* ************************************************************************ */

TEST(SubscriptExpr, base)
{
    {
        // obj[]
        const SubscriptExpr expr(makeUnique<IdentifierExpr>("obj"), {});

        EXPECT_EQ(ExprKind::Subscript, expr.getKind());
        EXPECT_TRUE(SubscriptExpr::is(expr));
        ASSERT_TRUE(expr.getExpr());
        ASSERT_TRUE(IdentifierExpr::is(expr.getExpr()));
        EXPECT_EQ("obj", IdentifierExpr::cast(expr.getExpr())->getName());
        EXPECT_TRUE(expr.getArguments().empty());
    }

    {
        // obj[]
        SubscriptExpr expr(makeUnique<IdentifierExpr>("obj"), {});

        EXPECT_EQ(ExprKind::Subscript, expr.getKind());
        EXPECT_TRUE(SubscriptExpr::is(expr));
        ASSERT_TRUE(expr.getExpr());
        ASSERT_TRUE(IdentifierExpr::is(expr.getExpr()));
        EXPECT_EQ("obj", IdentifierExpr::cast(expr.getExpr())->getName());
        EXPECT_TRUE(expr.getArguments().empty());

        // val[]
        expr.setExpr(makeUnique<IdentifierExpr>("val"));
        EXPECT_TRUE(SubscriptExpr::is(expr));
        ASSERT_TRUE(expr.getExpr());
        ASSERT_TRUE(IdentifierExpr::is(expr.getExpr()));
        EXPECT_EQ("val", IdentifierExpr::cast(expr.getExpr())->getName());
        EXPECT_TRUE(expr.getArguments().empty());

        // val[x, y]
        PtrDynamicArray<Expr> args;
        args.push_back(makeUnique<IdentifierExpr>("x"));
        args.push_back(makeUnique<IdentifierExpr>("y"));

        expr.setArguments(moveValue(args));
        ASSERT_TRUE(expr.getExpr());
        ASSERT_TRUE(IdentifierExpr::is(expr.getExpr()));
        EXPECT_EQ("val", IdentifierExpr::cast(expr.getExpr())->getName());
        EXPECT_FALSE(expr.getArguments().empty());
        ASSERT_EQ(2, expr.getArguments().size());
        ASSERT_TRUE(IdentifierExpr::is(expr.getArguments()[0]));
        ASSERT_TRUE(IdentifierExpr::is(expr.getArguments()[1]));
        EXPECT_EQ("x", IdentifierExpr::cast(expr.getArguments()[0])->getName());
        EXPECT_EQ("y", IdentifierExpr::cast(expr.getArguments()[1])->getName());
    }
}

/* ************************************************************************ */

TEST(Expr, vtable)
{
    UniquePtr<Expr> expr = makeUnique<IdentifierExpr>("variable");

    EXPECT_EQ(ExprKind::Identifier, expr->getKind());
    EXPECT_TRUE(IdentifierExpr::is(expr));
    ASSERT_FALSE(IdentifierExpr::cast(expr)->getName().empty());
    EXPECT_EQ("variable", IdentifierExpr::cast(expr)->getName());
}

/* ************************************************************************ */
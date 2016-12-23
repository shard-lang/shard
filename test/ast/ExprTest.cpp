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
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_TRUE(expr.is<NullLiteralExpr>());
        EXPECT_FALSE(expr.is<BoolLiteralExpr>());
        EXPECT_EQ(SourceLocation{}, expr.getSourceStart());
        EXPECT_EQ(SourceLocation{}, expr.getSourceEnd());
    }

    {
        const NullLiteralExpr expr({{123, 456}, {123, 458}});

        EXPECT_EQ(ExprKind::NullLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_TRUE(expr.is<NullLiteralExpr>());
        EXPECT_FALSE(expr.is<BoolLiteralExpr>());
        EXPECT_EQ((SourceLocation{123, 456}), expr.getSourceStart());
        EXPECT_EQ((SourceLocation{123, 458}), expr.getSourceEnd());
    }

    {
        const auto expr = NullLiteralExpr::make();
        ASSERT_NE(nullptr, expr);

        EXPECT_EQ(ExprKind::NullLiteral, expr->getKind());
        EXPECT_TRUE(expr->is<LiteralExpr>());
        EXPECT_TRUE(expr->is<NullLiteralExpr>());
        EXPECT_FALSE(expr->is<BoolLiteralExpr>());
    }
}

/* ************************************************************************ */

TEST(BoolLiteralExpr, base)
{
    {
        const BoolLiteralExpr expr(true);

        EXPECT_EQ(ExprKind::BoolLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_FALSE(expr.is<NullLiteralExpr>());
        EXPECT_TRUE(expr.is<BoolLiteralExpr>());
        EXPECT_TRUE(expr.getValue());
    }

    {
        const BoolLiteralExpr expr(false);

        EXPECT_EQ(ExprKind::BoolLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_FALSE(expr.is<NullLiteralExpr>());
        EXPECT_TRUE(expr.is<BoolLiteralExpr>());
        EXPECT_FALSE(expr.getValue());
    }

    {
        BoolLiteralExpr expr(false);

        EXPECT_EQ(ExprKind::BoolLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_FALSE(expr.is<NullLiteralExpr>());
        EXPECT_TRUE(expr.is<BoolLiteralExpr>());
        EXPECT_FALSE(expr.getValue());

        // Try to change value
        expr.setValue(true);
        EXPECT_TRUE(expr.getValue());

        expr.setValue(false);
        EXPECT_FALSE(expr.getValue());
    }

    {
        const auto expr = BoolLiteralExpr::make(true);
        ASSERT_NE(nullptr, expr);

        EXPECT_EQ(ExprKind::BoolLiteral, expr->getKind());
        EXPECT_TRUE(expr->is<LiteralExpr>());
        EXPECT_FALSE(expr->is<NullLiteralExpr>());
        EXPECT_TRUE(expr->is<BoolLiteralExpr>());
        EXPECT_TRUE(expr->getValue());
    }
}

/* ************************************************************************ */

TEST(IntLiteralExpr, base)
{
    {
        // Zero value
        const IntLiteralExpr expr(0);

        EXPECT_EQ(ExprKind::IntLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_TRUE(expr.is<NumberLiteralExpr>());
        EXPECT_TRUE(expr.is<IntLiteralExpr>());
        EXPECT_FALSE(expr.is<FloatLiteralExpr>());
        EXPECT_EQ(0, expr.getValue());
    }

    {
        // Random value
        const IntLiteralExpr expr(123);

        EXPECT_EQ(ExprKind::IntLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_TRUE(expr.is<NumberLiteralExpr>());
        EXPECT_TRUE(expr.is<IntLiteralExpr>());
        EXPECT_FALSE(expr.is<FloatLiteralExpr>());
        EXPECT_EQ(123, expr.getValue());
    }

    {
        // Min value
        const IntLiteralExpr expr(std::numeric_limits<IntLiteralExpr::ValueType>::min());

        EXPECT_EQ(ExprKind::IntLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_TRUE(expr.is<NumberLiteralExpr>());
        EXPECT_TRUE(expr.is<IntLiteralExpr>());
        EXPECT_FALSE(expr.is<FloatLiteralExpr>());
        EXPECT_EQ(std::numeric_limits<IntLiteralExpr::ValueType>::min(), expr.getValue());
    }

    {
        // Max value
        const IntLiteralExpr expr(std::numeric_limits<IntLiteralExpr::ValueType>::max());

        EXPECT_EQ(ExprKind::IntLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_TRUE(expr.is<NumberLiteralExpr>());
        EXPECT_TRUE(expr.is<IntLiteralExpr>());
        EXPECT_FALSE(expr.is<FloatLiteralExpr>());
        EXPECT_EQ(std::numeric_limits<IntLiteralExpr::ValueType>::max(), expr.getValue());
    }

    {
        IntLiteralExpr expr(0);

        EXPECT_EQ(ExprKind::IntLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_TRUE(expr.is<NumberLiteralExpr>());
        EXPECT_TRUE(expr.is<IntLiteralExpr>());
        EXPECT_FALSE(expr.is<FloatLiteralExpr>());
        EXPECT_EQ(0, expr.getValue());

        // Try to change values
        expr.setValue(4877);
        EXPECT_EQ(4877, expr.getValue());

        expr.setValue(-488932);
        EXPECT_EQ(-488932, expr.getValue());
    }

    {
        // Zero value
        const auto expr = IntLiteralExpr::make(0);
        ASSERT_NE(nullptr, expr);

        EXPECT_EQ(ExprKind::IntLiteral, expr->getKind());
        EXPECT_TRUE(expr->is<LiteralExpr>());
        EXPECT_TRUE(expr->is<NumberLiteralExpr>());
        EXPECT_TRUE(expr->is<IntLiteralExpr>());
        EXPECT_FALSE(expr->is<FloatLiteralExpr>());
        EXPECT_EQ(0, expr->getValue());
    }
}

/* ************************************************************************ */

TEST(FloatLiteralExpr, base)
{
    {
        // Zero value
        const FloatLiteralExpr expr(0);

        EXPECT_EQ(ExprKind::FloatLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_TRUE(expr.is<NumberLiteralExpr>());
        EXPECT_TRUE(expr.is<FloatLiteralExpr>());
        EXPECT_FALSE(expr.is<IntLiteralExpr>());
        EXPECT_FLOAT_EQ(0, expr.getValue());
    }

    {
        // Random value
        const FloatLiteralExpr expr(0.111);

        EXPECT_EQ(ExprKind::FloatLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_TRUE(expr.is<NumberLiteralExpr>());
        EXPECT_TRUE(expr.is<FloatLiteralExpr>());
        EXPECT_FALSE(expr.is<IntLiteralExpr>());
        EXPECT_FLOAT_EQ(0.111, expr.getValue());
    }

    {
        // Min value
        const FloatLiteralExpr expr(std::numeric_limits<FloatLiteralExpr::ValueType>::min());

        EXPECT_EQ(ExprKind::FloatLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_TRUE(expr.is<NumberLiteralExpr>());
        EXPECT_TRUE(expr.is<FloatLiteralExpr>());
        EXPECT_FALSE(expr.is<IntLiteralExpr>());
        EXPECT_FLOAT_EQ(std::numeric_limits<FloatLiteralExpr::ValueType>::min(), expr.getValue());
    }

    {
        // Max value
        const FloatLiteralExpr expr(std::numeric_limits<FloatLiteralExpr::ValueType>::max());

        EXPECT_EQ(ExprKind::FloatLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_TRUE(expr.is<NumberLiteralExpr>());
        EXPECT_TRUE(expr.is<FloatLiteralExpr>());
        EXPECT_FALSE(expr.is<IntLiteralExpr>());
        EXPECT_FLOAT_EQ(std::numeric_limits<FloatLiteralExpr::ValueType>::max(), expr.getValue());
    }

    {
        FloatLiteralExpr expr(0);

        EXPECT_EQ(ExprKind::FloatLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_TRUE(expr.is<NumberLiteralExpr>());
        EXPECT_TRUE(expr.is<FloatLiteralExpr>());
        EXPECT_FALSE(expr.is<IntLiteralExpr>());
        EXPECT_FLOAT_EQ(0, expr.getValue());

        // Try to change values
        expr.setValue(0.456e5);
        EXPECT_FLOAT_EQ(0.456e5, expr.getValue());

        expr.setValue(-756e45);
        EXPECT_FLOAT_EQ(-756e45, expr.getValue());
    }

    {
        // Zero value
        const auto expr = FloatLiteralExpr::make(0);
        ASSERT_NE(nullptr, expr);

        EXPECT_EQ(ExprKind::FloatLiteral, expr->getKind());
        EXPECT_TRUE(expr->is<LiteralExpr>());
        EXPECT_TRUE(expr->is<NumberLiteralExpr>());
        EXPECT_TRUE(expr->is<FloatLiteralExpr>());
        EXPECT_FALSE(expr->is<IntLiteralExpr>());
        EXPECT_FLOAT_EQ(0, expr->getValue());
    }
}

/* ************************************************************************ */

TEST(CharLiteralExpr, base)
{
    {
        // Zero value
        const CharLiteralExpr expr('\0');

        EXPECT_EQ(ExprKind::CharLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_TRUE(expr.is<CharLiteralExpr>());
        EXPECT_FALSE(expr.is<NumberLiteralExpr>());
        EXPECT_FALSE(expr.is<IntLiteralExpr>());
        EXPECT_EQ('\0', expr.getValue());
    }

    {
        const CharLiteralExpr expr(L'á');

        EXPECT_EQ(ExprKind::CharLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_TRUE(expr.is<CharLiteralExpr>());
        EXPECT_FALSE(expr.is<NumberLiteralExpr>());
        EXPECT_FALSE(expr.is<IntLiteralExpr>());
        EXPECT_EQ(L'á', expr.getValue());
    }

    {
        const CharLiteralExpr expr(L'\xf09eb888');

        EXPECT_EQ(ExprKind::CharLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_TRUE(expr.is<CharLiteralExpr>());
        EXPECT_FALSE(expr.is<NumberLiteralExpr>());
        EXPECT_FALSE(expr.is<IntLiteralExpr>());
        EXPECT_EQ(0xf09eb888, expr.getValue());
    }

    {
        const CharLiteralExpr expr(L'\U0001EE08');

        EXPECT_EQ(ExprKind::CharLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_TRUE(expr.is<CharLiteralExpr>());
        EXPECT_FALSE(expr.is<NumberLiteralExpr>());
        EXPECT_FALSE(expr.is<IntLiteralExpr>());
        EXPECT_EQ(0x0001EE08, expr.getValue());
    }

    {
        // Maximum valid UNICODE code point
        const CharLiteralExpr expr(0x10FFFF);

        EXPECT_EQ(ExprKind::CharLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_TRUE(expr.is<CharLiteralExpr>());
        EXPECT_FALSE(expr.is<NumberLiteralExpr>());
        EXPECT_FALSE(expr.is<IntLiteralExpr>());
        EXPECT_EQ(0x10FFFF, expr.getValue());
    }

    {
        CharLiteralExpr expr(0);

        EXPECT_EQ(ExprKind::CharLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_TRUE(expr.is<CharLiteralExpr>());
        EXPECT_FALSE(expr.is<NumberLiteralExpr>());
        EXPECT_FALSE(expr.is<IntLiteralExpr>());
        EXPECT_EQ(0, expr.getValue());

        // Try to change values
        expr.setValue(0x123);
        EXPECT_EQ(0x123, expr.getValue());

        expr.setValue(0xFF00);
        EXPECT_EQ(0xFF00, expr.getValue());
    }

    {
        // Zero value
        const auto expr = CharLiteralExpr::make('\0');
        ASSERT_NE(nullptr, expr);

        EXPECT_EQ(ExprKind::CharLiteral, expr->getKind());
        EXPECT_TRUE(expr->is<LiteralExpr>());
        EXPECT_TRUE(expr->is<CharLiteralExpr>());
        EXPECT_FALSE(expr->is<NumberLiteralExpr>());
        EXPECT_FALSE(expr->is<IntLiteralExpr>());
        EXPECT_EQ('\0', expr->getValue());
    }
}

/* ************************************************************************ */

TEST(StringLiteralExpr, base)
{
    {
        const StringLiteralExpr expr({});

        EXPECT_EQ(ExprKind::StringLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_TRUE(expr.is<StringLiteralExpr>());
        EXPECT_FALSE(expr.is<NumberLiteralExpr>());
        EXPECT_TRUE(expr.getValue().empty());
        EXPECT_EQ(StringLiteralExpr::ValueType{}, expr.getValue());
    }

    {
        const StringLiteralExpr expr("");

        EXPECT_EQ(ExprKind::StringLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_TRUE(expr.is<StringLiteralExpr>());
        EXPECT_FALSE(expr.is<NumberLiteralExpr>());
        EXPECT_TRUE(expr.getValue().empty());
        EXPECT_EQ("", expr.getValue());
    }

    {
        const StringLiteralExpr expr("Hello world");

        EXPECT_EQ(ExprKind::StringLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_TRUE(expr.is<StringLiteralExpr>());
        EXPECT_FALSE(expr.is<NumberLiteralExpr>());
        EXPECT_FALSE(expr.getValue().empty());
        EXPECT_EQ("Hello world", expr.getValue());
    }

    {
        StringLiteralExpr expr({});

        EXPECT_EQ(ExprKind::StringLiteral, expr.getKind());
        EXPECT_TRUE(expr.is<LiteralExpr>());
        EXPECT_TRUE(expr.is<StringLiteralExpr>());
        EXPECT_FALSE(expr.is<NumberLiteralExpr>());
        EXPECT_TRUE(expr.getValue().empty());
        EXPECT_EQ(StringLiteralExpr::ValueType{}, expr.getValue());

        // Try to change values
        expr.setValue("Hello world");
        EXPECT_EQ("Hello world", expr.getValue());

        expr.setValue("Maybe");
        EXPECT_EQ("Maybe", expr.getValue());
    }

    {
        const auto expr = StringLiteralExpr::make({});
        ASSERT_NE(nullptr, expr);

        EXPECT_EQ(ExprKind::StringLiteral, expr->getKind());
        EXPECT_TRUE(expr->is<LiteralExpr>());
        EXPECT_TRUE(expr->is<StringLiteralExpr>());
        EXPECT_FALSE(expr->is<NumberLiteralExpr>());
        EXPECT_TRUE(expr->getValue().empty());
        EXPECT_EQ(StringLiteralExpr::ValueType{}, expr->getValue());
    }
}

/* ************************************************************************ */

TEST(BinaryExpr, base)
{
    {
        // 5 + 2
        const BinaryExpr expr(BinaryExpr::OpKind::Add, IntLiteralExpr::make(5), IntLiteralExpr::make(2));

        EXPECT_EQ(ExprKind::Binary, expr.getKind());
        EXPECT_TRUE(expr.is<BinaryExpr>());
        EXPECT_FALSE(expr.is<LiteralExpr>());
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
        EXPECT_FALSE(expr.is<LiteralExpr>());
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
        EXPECT_FALSE(expr.is<LiteralExpr>());
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
        EXPECT_FALSE(expr->is<LiteralExpr>());
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

TEST(UnaryExpr, base)
{
    {
        // !true
        const UnaryExpr expr(UnaryExpr::OpKind::Not, BoolLiteralExpr::make(true));

        EXPECT_EQ(ExprKind::Unary, expr.getKind());
        EXPECT_TRUE(expr.is<UnaryExpr>());
        EXPECT_EQ(UnaryExpr::OpKind::Not, expr.getOpKind());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<BoolLiteralExpr>());
        EXPECT_TRUE(expr.getExpr()->cast<BoolLiteralExpr>().getValue());
    }

    {
        // -10
        const UnaryExpr expr(UnaryExpr::OpKind::Minus, IntLiteralExpr::make(10));

        EXPECT_EQ(ExprKind::Unary, expr.getKind());
        EXPECT_TRUE(expr.is<UnaryExpr>());
        EXPECT_EQ(UnaryExpr::OpKind::Minus, expr.getOpKind());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<IntLiteralExpr>());
        EXPECT_EQ(10, expr.getExpr()->cast<IntLiteralExpr>().getValue());
    }

    {
        // 5++
        const UnaryExpr expr(UnaryExpr::OpKind::PostInc, IntLiteralExpr::make(5));

        EXPECT_EQ(ExprKind::Unary, expr.getKind());
        EXPECT_TRUE(expr.is<UnaryExpr>());
        EXPECT_EQ(UnaryExpr::OpKind::PostInc, expr.getOpKind());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<IntLiteralExpr>());
        EXPECT_EQ(5, expr.getExpr()->cast<IntLiteralExpr>().getValue());
    }

    {
        // true--
        const UnaryExpr expr(UnaryExpr::OpKind::PostDec, BoolLiteralExpr::make(true));

        EXPECT_EQ(ExprKind::Unary, expr.getKind());
        EXPECT_TRUE(expr.is<UnaryExpr>());
        EXPECT_EQ(UnaryExpr::OpKind::PostDec, expr.getOpKind());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<BoolLiteralExpr>());
        EXPECT_TRUE(expr.getExpr()->cast<BoolLiteralExpr>().getValue());
    }

    {
        // -10
        UnaryExpr expr(UnaryExpr::OpKind::Minus, IntLiteralExpr::make(0));

        EXPECT_EQ(ExprKind::Unary, expr.getKind());
        EXPECT_TRUE(expr.is<UnaryExpr>());
        EXPECT_EQ(UnaryExpr::OpKind::Minus, expr.getOpKind());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<IntLiteralExpr>());
        EXPECT_EQ(0, expr.getExpr()->cast<IntLiteralExpr>().getValue());

        // !0
        expr.setOpKind(UnaryExpr::OpKind::Not);
        EXPECT_EQ(ExprKind::Unary, expr.getKind());
        EXPECT_TRUE(expr.is<UnaryExpr>());
        EXPECT_EQ(UnaryExpr::OpKind::Not, expr.getOpKind());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<IntLiteralExpr>());
        EXPECT_EQ(0, expr.getExpr()->cast<IntLiteralExpr>().getValue());

        // !true
        expr.setExpr(BoolLiteralExpr::make(true));
        EXPECT_EQ(ExprKind::Unary, expr.getKind());
        EXPECT_TRUE(expr.is<UnaryExpr>());
        EXPECT_EQ(UnaryExpr::OpKind::Not, expr.getOpKind());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<BoolLiteralExpr>());
        EXPECT_TRUE(expr.getExpr()->cast<BoolLiteralExpr>().getValue());
    }

    {
        // !true
        const auto expr = UnaryExpr::make(UnaryExpr::OpKind::Not, BoolLiteralExpr::make(true));
        ASSERT_NE(nullptr, expr);

        EXPECT_EQ(ExprKind::Unary, expr->getKind());
        EXPECT_TRUE(expr->is<UnaryExpr>());
        EXPECT_EQ(UnaryExpr::OpKind::Not, expr->getOpKind());
        ASSERT_NE(nullptr, expr->getExpr());
        ASSERT_TRUE(expr->getExpr()->is<BoolLiteralExpr>());
        EXPECT_TRUE(expr->getExpr()->cast<BoolLiteralExpr>().getValue());
    }
}

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

TEST(ParenExpr, base)
{
    {
        // (5)
        const ParenExpr expr(IntLiteralExpr::make(5));

        EXPECT_EQ(ExprKind::Paren, expr.getKind());
        EXPECT_TRUE(expr.is<ParenExpr>());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<IntLiteralExpr>());
        EXPECT_EQ(5, expr.getExpr()->cast<IntLiteralExpr>().getValue());
    }

    {
        // ((true))
        const ParenExpr expr(ParenExpr::make(BoolLiteralExpr::make(true)));

        EXPECT_EQ(ExprKind::Paren, expr.getKind());
        EXPECT_TRUE(expr.is<ParenExpr>());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<ParenExpr>());
        ASSERT_TRUE(expr.getExpr()->cast<ParenExpr>().getExpr());
        EXPECT_TRUE(expr.getExpr()->cast<ParenExpr>().getExpr()->cast<BoolLiteralExpr>().getValue());
    }

    {
        // (5)
        ParenExpr expr(IntLiteralExpr::make(5));

        EXPECT_EQ(ExprKind::Paren, expr.getKind());
        EXPECT_TRUE(expr.is<ParenExpr>());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<IntLiteralExpr>());
        EXPECT_EQ(5, expr.getExpr()->cast<IntLiteralExpr>().getValue());

        // (true)
        expr.setExpr(BoolLiteralExpr::make(true));
        EXPECT_EQ(ExprKind::Paren, expr.getKind());
        EXPECT_TRUE(expr.is<ParenExpr>());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<BoolLiteralExpr>());
        EXPECT_TRUE(expr.getExpr()->cast<BoolLiteralExpr>().getValue());
    }

    {
        // (5)
        const auto expr = ParenExpr::make(IntLiteralExpr::make(5));
        ASSERT_NE(nullptr, expr);

        EXPECT_EQ(ExprKind::Paren, expr->getKind());
        EXPECT_TRUE(expr->is<ParenExpr>());
        ASSERT_NE(nullptr, expr->getExpr());
        ASSERT_TRUE(expr->getExpr()->is<IntLiteralExpr>());
        EXPECT_EQ(5, expr->getExpr()->cast<IntLiteralExpr>().getValue());
    }
}

/* ************************************************************************ */

TEST(IdentifierExpr, base)
{
    {
        // id
        const IdentifierExpr expr("id");

        EXPECT_EQ(ExprKind::Identifier, expr.getKind());
        EXPECT_TRUE(expr.is<IdentifierExpr>());
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
        EXPECT_TRUE(expr.is<IdentifierExpr>());
        ASSERT_FALSE(expr.getName().empty());
        EXPECT_EQ("id", expr.getName());

        expr.setName("my_id");
        EXPECT_EQ("my_id", expr.getName());
    }

    {
        // id
        const auto expr = IdentifierExpr::make("id");
        ASSERT_NE(nullptr, expr);

        EXPECT_EQ(ExprKind::Identifier, expr->getKind());
        EXPECT_TRUE(expr->is<IdentifierExpr>());
        ASSERT_FALSE(expr->getName().empty());
        EXPECT_EQ("id", expr->getName());
    }
}

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

TEST(FunctionCallExpr, base)
{
    {
        // obj()
        const FunctionCallExpr expr(IdentifierExpr::make("obj"), {});

        EXPECT_EQ(ExprKind::FunctionCall, expr.getKind());
        EXPECT_TRUE(expr.is<FunctionCallExpr>());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<IdentifierExpr>());
        EXPECT_EQ("obj", expr.getExpr()->cast<IdentifierExpr>().getName());
        EXPECT_TRUE(expr.getArguments().empty());
    }

    {
        // obj()
        FunctionCallExpr expr(IdentifierExpr::make("obj"), {});

        EXPECT_EQ(ExprKind::FunctionCall, expr.getKind());
        EXPECT_TRUE(expr.is<FunctionCallExpr>());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<IdentifierExpr>());
        EXPECT_EQ("obj", expr.getExpr()->cast<IdentifierExpr>().getName());
        EXPECT_TRUE(expr.getArguments().empty());

        // val()
        expr.setExpr(IdentifierExpr::make("val"));
        EXPECT_TRUE(expr.is<FunctionCallExpr>());
        ASSERT_NE(nullptr, expr.getExpr());
        ASSERT_TRUE(expr.getExpr()->is<IdentifierExpr>());
        EXPECT_EQ("val", expr.getExpr()->cast<IdentifierExpr>().getName());
        EXPECT_TRUE(expr.getArguments().empty());

        // val(x, y)
        PtrDynamicArray<Expr> args;
        args.push_back(IdentifierExpr::make("x"));
        args.push_back(IdentifierExpr::make("y"));

        expr.setArguments(moveValue(args));
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
        // obj()
        const auto expr = FunctionCallExpr::make(IdentifierExpr::make("obj"), {});
        ASSERT_NE(nullptr, expr);

        EXPECT_EQ(ExprKind::FunctionCall, expr->getKind());
        EXPECT_TRUE(expr->is<FunctionCallExpr>());
        ASSERT_NE(nullptr, expr->getExpr());
        ASSERT_TRUE(expr->getExpr()->is<IdentifierExpr>());
        EXPECT_EQ("obj", expr->getExpr()->cast<IdentifierExpr>().getName());
        EXPECT_TRUE(expr->getArguments().empty());
    }
}

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
        PtrDynamicArray<Expr> args;
        args.push_back(IdentifierExpr::make("x"));
        args.push_back(IdentifierExpr::make("y"));

        expr.setArguments(moveValue(args));
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

TEST(Expr, vtable)
{
    UniquePtr<Expr> expr = IdentifierExpr::make("variable");

    EXPECT_EQ(ExprKind::Identifier, expr->getKind());
    EXPECT_TRUE(expr->is<IdentifierExpr>());
    ASSERT_FALSE(expr->cast<IdentifierExpr>().getName().empty());
    EXPECT_EQ("variable", expr->cast<IdentifierExpr>().getName());
}

/* ************************************************************************ */
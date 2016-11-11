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

// Declaration
#include "shard/ast/Expr.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

Expr::Expr(ExprKind kind, SourceRange range)
    : LocationInfo(range)
    , m_kind(kind)
{
    // Nothing to do
}

/* ************************************************************************* */

Expr::~Expr() = default;

/* ************************************************************************* */

NullLiteralExpr::NullLiteralExpr(SourceRange range)
    : LiteralExpr(ExprKind::NullLiteral, range)
{
    // Nothing to do
}

/* ************************************************************************* */

BoolLiteralExpr::BoolLiteralExpr(ValueType value, SourceRange range)
    : LiteralExpr(ExprKind::BoolLiteral, range)
    , m_value(value)
{
    // Nothing to do
}

/* ************************************************************************* */

IntLiteralExpr::IntLiteralExpr(ValueType value, SourceRange range)
    : NumberLiteralExpr(ExprKind::IntLiteral, range)
    , m_value(value)
{
    // Nothing to do
}

/* ************************************************************************* */

FloatLiteralExpr::FloatLiteralExpr(ValueType value, SourceRange range)
    : NumberLiteralExpr(ExprKind::FloatLiteral, range)
    , m_value(value)
{
    // Nothing to do
}

/* ************************************************************************* */

CharLiteralExpr::CharLiteralExpr(ValueType value, SourceRange range)
    : LiteralExpr(ExprKind::CharLiteral, range)
    , m_value(value)
{
    // Nothing to do
}

/* ************************************************************************* */

StringLiteralExpr::StringLiteralExpr(ValueType value, SourceRange range)
    : LiteralExpr(ExprKind::StringLiteral, range)
    , m_value(moveValue(value))
{
    // Nothing to do
}

/* ************************************************************************* */

BinaryExpr::BinaryExpr(Operator op, UniquePtr<Expr> lhs, UniquePtr<Expr> rhs, SourceRange range)
    : Expr(ExprKind::Binary, range)
    , m_operator(op)
    , m_lhs(moveValue(lhs))
    , m_rhs(moveValue(rhs))
{
    // Nothing to do
}

/* ************************************************************************* */

PrefixUnaryExpr::PrefixUnaryExpr(Operator op, UniquePtr<Expr> expr, SourceRange range)
    : Expr(ExprKind::PrefixUnary, range)
    , m_operator(op)
    , m_expr(moveValue(expr))
{
    // Nothing to do
}

/* ************************************************************************* */

PostfixUnaryExpr::PostfixUnaryExpr(Operator op, UniquePtr<Expr> expr, SourceRange range)
    : Expr(ExprKind::PostfixUnary, range)
    , m_operator(op)
    , m_expr(moveValue(expr))
{
    // Nothing to do
}

/* ************************************************************************* */

TernaryExpr::TernaryExpr(UniquePtr<Expr> condExpr, UniquePtr<Expr> trueExpr, UniquePtr<Expr> falseExpr, SourceRange range)
    : Expr(ExprKind::Ternary, range)
    , m_condExpr(moveValue(condExpr))
    , m_trueExpr(moveValue(trueExpr))
    , m_falseExpr(moveValue(falseExpr))
{
    // Nothing to do
}

/* ************************************************************************* */

ParenExpr::ParenExpr(UniquePtr<Expr> expr, SourceRange range)
    : Expr(ExprKind::Paren, range)
    , m_expr(moveValue(expr))
{
    SHARD_ASSERT(m_expr);
}

/* ************************************************************************* */

IdentifierExpr::IdentifierExpr(String name, SourceRange range)
    : Expr(ExprKind::Identifier, range)
    , m_name(moveValue(name))
{
    SHARD_ASSERT(!m_name.empty());
}

/* ************************************************************************* */

MemberAccessExpr::MemberAccessExpr(UniquePtr<Expr> expr, String name, SourceRange range)
    : Expr(ExprKind::Identifier, range)
    , m_expr(moveValue(expr))
    , m_name(moveValue(name))
{
    SHARD_ASSERT(!m_name.empty());
}

/* ************************************************************************* */

FunctionCallExpr::FunctionCallExpr(UniquePtr<Expr> expr, DynamicArray<UniquePtr<Expr>> args, SourceRange range)
    : Expr(ExprKind::FunctionCall, range)
    , m_expr(moveValue(expr))
    , m_arguments(moveValue(args))
{
    SHARD_ASSERT(m_expr);
}

/* ************************************************************************* */

SubscriptExpr::SubscriptExpr(UniquePtr<Expr> expr, DynamicArray<UniquePtr<Expr>> args, SourceRange range)
    : Expr(ExprKind::Subscript, range)
    , m_expr(moveValue(expr))
    , m_arguments(moveValue(args))
{
    SHARD_ASSERT(m_expr);
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

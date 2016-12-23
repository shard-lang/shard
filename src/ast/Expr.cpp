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

// Shard
#include "shard/Assert.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

Expr::Expr(ExprKind kind, SourceRange range) noexcept
    : Node(range)
    , m_kind(kind)
{
    // Nothing to do
}

/* ************************************************************************* */

Expr::~Expr() = default;

/* ************************************************************************* */

constexpr KindRange<ExprKind> LiteralExpr::Kind;

/* ************************************************************************* */

NullLiteralExpr::NullLiteralExpr(SourceRange range) noexcept
    : LiteralExpr(Kind, range)
{
    // Nothing to do
}

/* ************************************************************************* */

NullLiteralExpr::~NullLiteralExpr() = default;

/* ************************************************************************* */

UniquePtr<NullLiteralExpr> NullLiteralExpr::make(SourceRange range)
{
    return makeUnique<NullLiteralExpr>(moveValue(range));
}

/* ************************************************************************* */

BoolLiteralExpr::BoolLiteralExpr(ValueType value, SourceRange range) noexcept
    : LiteralExpr(Kind, range)
    , m_value(value)
{
    // Nothing to do
}

/* ************************************************************************* */

BoolLiteralExpr::~BoolLiteralExpr() = default;

/* ************************************************************************* */

void BoolLiteralExpr::setValue(ValueType value)
{
    m_value = value;
}

/* ************************************************************************* */

UniquePtr<BoolLiteralExpr> BoolLiteralExpr::make(ValueType value, SourceRange range)
{
    return makeUnique<BoolLiteralExpr>(moveValue(value), moveValue(range));
}

/* ************************************************************************* */

constexpr KindRange<ExprKind> NumberLiteralExpr::Kind;

/* ************************************************************************* */

IntLiteralExpr::IntLiteralExpr(ValueType value, SourceRange range) noexcept
    : NumberLiteralExpr(Kind, range)
    , m_value(value)
{
    // Nothing to do
}

/* ************************************************************************* */

IntLiteralExpr::~IntLiteralExpr() = default;

/* ************************************************************************* */

void IntLiteralExpr::setValue(ValueType value)
{
    m_value = value;
}

/* ************************************************************************* */

UniquePtr<IntLiteralExpr> IntLiteralExpr::make(ValueType value, SourceRange range)
{
    return makeUnique<IntLiteralExpr>(moveValue(value), moveValue(range));
}

/* ************************************************************************* */

FloatLiteralExpr::FloatLiteralExpr(ValueType value, SourceRange range) noexcept
    : NumberLiteralExpr(Kind, range)
    , m_value(value)
{
    // Nothing to do
}

/* ************************************************************************* */

FloatLiteralExpr::~FloatLiteralExpr() = default;

/* ************************************************************************* */

void FloatLiteralExpr::setValue(ValueType value)
{
    m_value = value;
}

/* ************************************************************************* */

UniquePtr<FloatLiteralExpr> FloatLiteralExpr::make(ValueType value, SourceRange range)
{
    return makeUnique<FloatLiteralExpr>(moveValue(value), moveValue(range));
}

/* ************************************************************************* */

CharLiteralExpr::CharLiteralExpr(ValueType value, SourceRange range) noexcept
    : LiteralExpr(Kind, range)
    , m_value(value)
{
    // Nothing to do
}

/* ************************************************************************* */

CharLiteralExpr::~CharLiteralExpr() = default;

/* ************************************************************************* */

void CharLiteralExpr::setValue(ValueType value)
{
    m_value = value;
}

/* ************************************************************************* */

UniquePtr<CharLiteralExpr> CharLiteralExpr::make(ValueType value, SourceRange range)
{
    return makeUnique<CharLiteralExpr>(moveValue(value), moveValue(range));
}

/* ************************************************************************* */

StringLiteralExpr::StringLiteralExpr(ValueType value, SourceRange range)
    : LiteralExpr(Kind, range)
    , m_value(moveValue(value))
{
    // Nothing to do
}

/* ************************************************************************* */

StringLiteralExpr::~StringLiteralExpr() = default;

/* ************************************************************************* */

void StringLiteralExpr::setValue(ValueType value)
{
    m_value = moveValue(value);
}

/* ************************************************************************* */

UniquePtr<StringLiteralExpr> StringLiteralExpr::make(ValueType value, SourceRange range)
{
    return makeUnique<StringLiteralExpr>(moveValue(value), moveValue(range));
}

/* ************************************************************************* */

BinaryExpr::BinaryExpr(OpKind op, UniquePtr<Expr> lhs, UniquePtr<Expr> rhs, SourceRange range)
    : Expr(Kind, range)
    , m_operator(op)
    , m_lhs(moveValue(lhs))
    , m_rhs(moveValue(rhs))
{
    // Nothing to do
}

/* ************************************************************************* */

BinaryExpr::~BinaryExpr() = default;

/* ************************************************************************* */

void BinaryExpr::setOpKind(OpKind op)
{
    m_operator = op;
}

/* ************************************************************************* */

void BinaryExpr::setLhs(UniquePtr<Expr> lhs)
{
    SHARD_ASSERT(lhs);
    m_lhs = moveValue(lhs);
}

/* ************************************************************************* */

void BinaryExpr::setRhs(UniquePtr<Expr> rhs)
{
    SHARD_ASSERT(rhs);
    m_rhs = moveValue(rhs);
}

/* ************************************************************************* */

UniquePtr<BinaryExpr> BinaryExpr::make(OpKind op, UniquePtr<Expr> lhs, UniquePtr<Expr> rhs, SourceRange range)
{
    return makeUnique<BinaryExpr>(op, moveValue(lhs), moveValue(rhs), moveValue(range));
}

/* ************************************************************************* */

UnaryExpr::UnaryExpr(OpKind op, UniquePtr<Expr> expr, SourceRange range)
    : Expr(Kind, range)
    , m_operator(op)
    , m_expr(moveValue(expr))
{
    // Nothing to do
}

/* ************************************************************************* */

UnaryExpr::~UnaryExpr() = default;

/* ************************************************************************* */

void UnaryExpr::setOpKind(OpKind op)
{
    m_operator = op;
}

/* ************************************************************************* */

void UnaryExpr::setExpr(UniquePtr<Expr> expr)
{
    SHARD_ASSERT(expr);
    m_expr = moveValue(expr);
}

/* ************************************************************************* */

UniquePtr<UnaryExpr> UnaryExpr::make(OpKind op, UniquePtr<Expr> expr, SourceRange range)
{
    return makeUnique<UnaryExpr>(op, moveValue(expr), moveValue(range));
}

/* ************************************************************************* */

TernaryExpr::TernaryExpr(UniquePtr<Expr> condExpr, UniquePtr<Expr> trueExpr, UniquePtr<Expr> falseExpr, SourceRange range)
    : Expr(Kind, range)
    , m_condExpr(moveValue(condExpr))
    , m_trueExpr(moveValue(trueExpr))
    , m_falseExpr(moveValue(falseExpr))
{
    // Nothing to do
}

/* ************************************************************************* */

TernaryExpr::~TernaryExpr() = default;

/* ************************************************************************* */

void TernaryExpr::setCondExpr(UniquePtr<Expr> expr)
{
    SHARD_ASSERT(expr);
    m_condExpr = moveValue(expr);
}

/* ************************************************************************* */

void TernaryExpr::setTrueExpr(UniquePtr<Expr> expr)
{
    SHARD_ASSERT(expr);
    m_trueExpr = moveValue(expr);
}

/* ************************************************************************* */

void TernaryExpr::setFalseExpr(UniquePtr<Expr> expr)
{
    SHARD_ASSERT(expr);
    m_falseExpr = moveValue(expr);
}

/* ************************************************************************* */

UniquePtr<TernaryExpr> TernaryExpr::make(UniquePtr<Expr> condExpr, UniquePtr<Expr> trueExpr, UniquePtr<Expr> falseExpr, SourceRange range)
{
    return makeUnique<TernaryExpr>(moveValue(condExpr), moveValue(trueExpr), moveValue(falseExpr), moveValue(range));
}

/* ************************************************************************* */

ParenExpr::ParenExpr(UniquePtr<Expr> expr, SourceRange range)
    : Expr(Kind, range)
    , m_expr(moveValue(expr))
{
    SHARD_ASSERT(m_expr);
}

/* ************************************************************************* */

ParenExpr::~ParenExpr() = default;

/* ************************************************************************* */

void ParenExpr::setExpr(UniquePtr<Expr> expr)
{
    SHARD_ASSERT(expr);
    m_expr = moveValue(expr);
}

/* ************************************************************************* */

UniquePtr<ParenExpr> ParenExpr::make(UniquePtr<Expr> expr, SourceRange range)
{
    return makeUnique<ParenExpr>(moveValue(expr), moveValue(range));
}

/* ************************************************************************* */

IdentifierExpr::IdentifierExpr(String name, SourceRange range)
    : Expr(Kind, range)
    , m_name(moveValue(name))
{
    SHARD_ASSERT(!m_name.empty());
}

/* ************************************************************************* */

IdentifierExpr::~IdentifierExpr() = default;

/* ************************************************************************* */

void IdentifierExpr::setName(String name)
{
    SHARD_ASSERT(!name.empty());
    m_name = moveValue(name);
}

/* ************************************************************************* */

UniquePtr<IdentifierExpr> IdentifierExpr::make(String name, SourceRange range)
{
    return makeUnique<IdentifierExpr>(moveValue(name), moveValue(range));
}

/* ************************************************************************* */

MemberAccessExpr::MemberAccessExpr(UniquePtr<Expr> expr, String name, SourceRange range)
    : Expr(Kind, range)
    , m_expr(moveValue(expr))
    , m_name(moveValue(name))
{
    SHARD_ASSERT(!m_name.empty());
}

/* ************************************************************************* */

MemberAccessExpr::~MemberAccessExpr() = default;

/* ************************************************************************* */

void MemberAccessExpr::setExpr(UniquePtr<Expr> expr)
{
    SHARD_ASSERT(expr);
    m_expr = moveValue(expr);
}

/* ************************************************************************* */

void MemberAccessExpr::setName(String name)
{
    SHARD_ASSERT(!name.empty());
    m_name = moveValue(name);
}

/* ************************************************************************* */

UniquePtr<MemberAccessExpr> MemberAccessExpr::make(UniquePtr<Expr> expr, String name, SourceRange range)
{
    return makeUnique<MemberAccessExpr>(moveValue(expr), moveValue(name), moveValue(range));
}

/* ************************************************************************* */

FunctionCallExpr::FunctionCallExpr(UniquePtr<Expr> expr, PtrDynamicArray<Expr> args, SourceRange range)
    : Expr(Kind, range)
    , m_expr(moveValue(expr))
    , m_arguments(moveValue(args))
{
    SHARD_ASSERT(m_expr);
}

/* ************************************************************************* */

FunctionCallExpr::~FunctionCallExpr() = default;

/* ************************************************************************* */

void FunctionCallExpr::setExpr(UniquePtr<Expr> expr)
{
    SHARD_ASSERT(expr);
    m_expr = moveValue(expr);
}

/* ************************************************************************* */

void FunctionCallExpr::setArguments(PtrDynamicArray<Expr> args)
{
    m_arguments = moveValue(args);
}

/* ************************************************************************* */

UniquePtr<FunctionCallExpr> FunctionCallExpr::make(UniquePtr<Expr> expr, PtrDynamicArray<Expr> args, SourceRange range)
{
    return makeUnique<FunctionCallExpr>(moveValue(expr), moveValue(args), moveValue(range));
}

/* ************************************************************************* */

SubscriptExpr::SubscriptExpr(UniquePtr<Expr> expr, PtrDynamicArray<Expr> args, SourceRange range)
    : Expr(Kind, range)
    , m_expr(moveValue(expr))
    , m_arguments(moveValue(args))
{
    SHARD_ASSERT(m_expr);
}

/* ************************************************************************* */

SubscriptExpr::~SubscriptExpr() = default;

/* ************************************************************************* */

void SubscriptExpr::setExpr(UniquePtr<Expr> expr)
{
    SHARD_ASSERT(expr);
    m_expr = moveValue(expr);
}

/* ************************************************************************* */

void SubscriptExpr::setArguments(PtrDynamicArray<Expr> args)
{
    m_arguments = moveValue(args);
}

/* ************************************************************************* */

UniquePtr<SubscriptExpr> SubscriptExpr::make(UniquePtr<Expr> expr, PtrDynamicArray<Expr> args, SourceRange range)
{
    return makeUnique<SubscriptExpr>(moveValue(expr), moveValue(args), moveValue(range));
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

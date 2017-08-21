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
#include "shard/ast/expr/BinaryExpr.hpp"

// Shard
#include "shard/utility.hpp"
#include "shard/Assert.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

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

}
}
}

/* ************************************************************************* */

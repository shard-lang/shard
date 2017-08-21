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
#include "shard/ast/expr/UnaryExpr.hpp"

// Shard
#include "shard/utility.hpp"
#include "shard/Assert.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

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

}
}
}

/* ************************************************************************* */

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
#include "shard/ast/stmt/ExprStmt.hpp"

// Shard
#include "shard/utility.hpp"
#include "shard/Assert.hpp"
#include "shard/ast/Expr.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

ExprStmt::ExprStmt(UniquePtr<Expr> expr, SourceRange range)
    : Stmt(Kind, moveValue(range))
    , m_expr(moveValue(expr))
{
    // Nothing to do
}

/* ************************************************************************* */

ExprStmt::~ExprStmt() = default;

/* ************************************************************************* */

void ExprStmt::setExpr(UniquePtr<Expr> expr)
{
    SHARD_ASSERT(expr);
    m_expr = moveValue(expr);
}

/* ************************************************************************* */

UniquePtr<ExprStmt> ExprStmt::make(UniquePtr<Expr> expr, SourceRange range)
{
    return makeUnique<ExprStmt>(moveValue(expr), moveValue(range));
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */
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
#include "shard/ast/stmt/ReturnStmt.hpp"

// Shard
#include "shard/utility.hpp"
#include "shard/Assert.hpp"
#include "shard/ast/Expr.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

ReturnStmt::ReturnStmt(UniquePtr<Expr> resExpr, SourceRange range)
    : Stmt(Kind, moveValue(range))
    , m_resExpr(moveValue(resExpr))
{
    // Nothing to do
}

/* ************************************************************************* */

ReturnStmt::~ReturnStmt() = default;

/* ************************************************************************* */

void ReturnStmt::setResExpr(UniquePtr<Expr> expr)
{
    m_resExpr = moveValue(expr);
}

/* ************************************************************************* */

UniquePtr<ReturnStmt> ReturnStmt::make(UniquePtr<Expr> resExpr, SourceRange range)
{
    return makeUnique<ReturnStmt>(moveValue(resExpr), moveValue(range));
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

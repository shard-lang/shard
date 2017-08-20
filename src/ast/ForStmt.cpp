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
#include "shard/ast/ForStmt.hpp"

// Shard
#include "shard/utility.hpp"
#include "shard/Assert.hpp"
#include "shard/ast/Expr.hpp"
#include "shard/ast/Stmt.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

ForStmt::ForStmt(UniquePtr<Stmt> initStmt, UniquePtr<Expr> condExpr, UniquePtr<Expr> incExpr, UniquePtr<Stmt> bodyStmt, SourceRange range)
    : Stmt(Kind, moveValue(range))
    , m_initStmt(moveValue(initStmt))
    , m_condExpr(moveValue(condExpr))
    , m_incExpr(moveValue(incExpr))
    , m_bodyStmt(moveValue(bodyStmt))
{
    SHARD_ASSERT(m_bodyStmt);
}

/* ************************************************************************* */

ForStmt::~ForStmt() = default;

/* ************************************************************************* */

void ForStmt::setInitStmt(UniquePtr<Stmt> stmt)
{
    SHARD_ASSERT(stmt);
    m_initStmt = moveValue(stmt);
}

/* ************************************************************************* */

void ForStmt::setCondExpr(UniquePtr<Expr> expr)
{
    SHARD_ASSERT(expr);
    m_condExpr = moveValue(expr);
}

/* ************************************************************************* */

void ForStmt::setIncExpr(UniquePtr<Expr> expr)
{
    SHARD_ASSERT(expr);
    m_incExpr = moveValue(expr);
}

/* ************************************************************************* */

void ForStmt::setBodyStmt(UniquePtr<Stmt> stmt)
{
    SHARD_ASSERT(stmt);
    m_bodyStmt = moveValue(stmt);
}

/* ************************************************************************* */

UniquePtr<ForStmt> ForStmt::make(UniquePtr<Stmt> initStmt, UniquePtr<Expr> condExpr, UniquePtr<Expr> incExpr, UniquePtr<Stmt> bodyStmt, SourceRange range)
{
    return makeUnique<ForStmt>(moveValue(initStmt), moveValue(condExpr), moveValue(incExpr), moveValue(bodyStmt), moveValue(range));
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

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
#include "shard/ast/IfStmt.hpp"

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

IfStmt::IfStmt(UniquePtr<Expr> condExpr, UniquePtr<Stmt> thenStmt, UniquePtr<Stmt> elseStmt, SourceRange range)
    : Stmt(Kind, moveValue(range))
    , m_condExpr(moveValue(condExpr))
    , m_thenStmt(moveValue(thenStmt))
    , m_elseStmt(moveValue(elseStmt))
{
    SHARD_ASSERT(m_condExpr);
    SHARD_ASSERT(m_thenStmt);
}

/* ************************************************************************* */

IfStmt::~IfStmt() = default;

/* ************************************************************************* */

void IfStmt::setCondExpr(UniquePtr<Expr> expr)
{
    SHARD_ASSERT(expr);
    m_condExpr = moveValue(expr);
}

/* ************************************************************************* */

void IfStmt::setThenStmt(UniquePtr<Stmt> stmt)
{
    SHARD_ASSERT(stmt);
    m_thenStmt = moveValue(stmt);
}

/* ************************************************************************* */

void IfStmt::setElseStmt(UniquePtr<Stmt> stmt)
{
    m_elseStmt = moveValue(stmt);
}

/* ************************************************************************* */

UniquePtr<IfStmt> IfStmt::make(UniquePtr<Expr> condExpr, UniquePtr<Stmt> thenStmt, UniquePtr<Stmt> elseStmt, SourceRange range)
{
    return makeUnique<IfStmt>(moveValue(condExpr), moveValue(thenStmt), moveValue(elseStmt), moveValue(range));
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

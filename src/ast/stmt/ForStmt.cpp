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
#include "shard/ast/stmt/ForStmt.hpp"

// Shard
#include "shard/utility.hpp"
#include "shard/Assert.hpp"
#include "shard/ast/Expr.hpp"
#include "shard/ast/Stmt.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

ForStmt::ForStmt(UniquePtr<Stmt> initStmt, UniquePtr<Expr> condExpr, UniquePtr<Expr> incExpr, UniquePtr<Stmt> bodyStmt, SourceRange range)
    : Stmt(range)
    , m_initStmt(std::move(initStmt))
    , m_condExpr(std::move(condExpr))
    , m_incExpr(std::move(incExpr))
    , m_bodyStmt(std::move(bodyStmt))
{
    SHARD_ASSERT(m_bodyStmt);
}

/* ************************************************************************* */

ForStmt::~ForStmt() = default;

/* ************************************************************************* */

void ForStmt::setInitStmt(UniquePtr<Stmt> stmt)
{
    SHARD_ASSERT(stmt);
    m_initStmt = std::move(stmt);
}

/* ************************************************************************* */

void ForStmt::setCondExpr(UniquePtr<Expr> expr)
{
    SHARD_ASSERT(expr);
    m_condExpr = std::move(expr);
}

/* ************************************************************************* */

void ForStmt::setIncExpr(UniquePtr<Expr> expr)
{
    SHARD_ASSERT(expr);
    m_incExpr = std::move(expr);
}

/* ************************************************************************* */

void ForStmt::setBodyStmt(UniquePtr<Stmt> stmt)
{
    SHARD_ASSERT(stmt);
    m_bodyStmt = std::move(stmt);
}

/* ************************************************************************* */

UniquePtr<ForStmt> ForStmt::make(UniquePtr<Stmt> initStmt, UniquePtr<Expr> condExpr, UniquePtr<Expr> incExpr, UniquePtr<Stmt> bodyStmt, SourceRange range)
{
    return makeUnique<ForStmt>(std::move(initStmt), std::move(condExpr), std::move(incExpr), std::move(bodyStmt), range);
}

/* ************************************************************************* */

}

/* ************************************************************************* */

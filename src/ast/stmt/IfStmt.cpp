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
#include "shard/ast/stmt/IfStmt.hpp"

// Shard
#include "shard/Assert.hpp"
#include "shard/ast/Expr.hpp"
#include "shard/ast/Stmt.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

IfStmt::IfStmt(UniquePtr<Expr> condExpr, UniquePtr<Stmt> thenStmt, UniquePtr<Stmt> elseStmt, SourceRange range)
    : Stmt(Kind, range)
    , m_condExpr(std::move(condExpr))
    , m_thenStmt(std::move(thenStmt))
    , m_elseStmt(std::move(elseStmt))
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
    m_condExpr = std::move(expr);
}

/* ************************************************************************* */

void IfStmt::setThenStmt(UniquePtr<Stmt> stmt)
{
    SHARD_ASSERT(stmt);
    m_thenStmt = std::move(stmt);
}

/* ************************************************************************* */

void IfStmt::setElseStmt(UniquePtr<Stmt> stmt)
{
    m_elseStmt = std::move(stmt);
}

/* ************************************************************************* */

UniquePtr<IfStmt> IfStmt::make(UniquePtr<Expr> condExpr, UniquePtr<Stmt> thenStmt, UniquePtr<Stmt> elseStmt, SourceRange range)
{
    return makeUnique<IfStmt>(std::move(condExpr), std::move(thenStmt), std::move(elseStmt), range);
}

/* ************************************************************************* */

}

/* ************************************************************************* */

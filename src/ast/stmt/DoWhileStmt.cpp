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
#include "shard/ast/stmt/DoWhileStmt.hpp"

// Shard
#include "shard/Assert.hpp"
#include "shard/ast/Expr.hpp"
#include "shard/ast/stmt/CompoundStmt.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

DoWhileStmt::DoWhileStmt(UniquePtr<Expr> condExpr, UniquePtr<CompoundStmt> bodyStmt, SourceRange range)
    : Stmt(Kind, range)
    , m_condExpr(std::move(condExpr))
    , m_bodyStmt(std::move(bodyStmt))
{
    SHARD_ASSERT(m_condExpr);
    SHARD_ASSERT(m_bodyStmt);
}

/* ************************************************************************* */

DoWhileStmt::~DoWhileStmt() = default;

/* ************************************************************************* */

void DoWhileStmt::setCondExpr(UniquePtr<Expr> expr)
{
    SHARD_ASSERT(expr);
    m_condExpr = std::move(expr);
}

/* ************************************************************************* */

void DoWhileStmt::setBodyStmt(UniquePtr<CompoundStmt> stmt)
{
    SHARD_ASSERT(stmt);
    m_bodyStmt = std::move(stmt);
}

/* ************************************************************************* */

UniquePtr<DoWhileStmt> DoWhileStmt::make(UniquePtr<Expr> condExpr, UniquePtr<CompoundStmt> bodyStmt, SourceRange range)
{
    return makeUnique<DoWhileStmt>(std::move(condExpr), std::move(bodyStmt), range);
}

/* ************************************************************************* */

}

/* ************************************************************************* */

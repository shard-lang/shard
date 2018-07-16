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
#include "shard/ast/stmt/SwitchStmt.hpp"

// Shard
#include "shard/Assert.hpp"
#include "shard/ast/Expr.hpp"
#include "shard/ast/stmt/CompoundStmt.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

SwitchStmt::SwitchStmt(UniquePtr<Expr> condExpr, UniquePtr<CompoundStmt> bodyStmt, SourceRange range)
    : Stmt(Kind, range)
    , m_condExpr(std::move(condExpr))
    , m_bodyStmt(std::move(bodyStmt))
{
    SHARD_ASSERT(m_condExpr);
    SHARD_ASSERT(m_bodyStmt);
}

/* ************************************************************************* */

SwitchStmt::~SwitchStmt() = default;

/* ************************************************************************* */

void SwitchStmt::setCondExpr(UniquePtr<Expr> expr)
{
    SHARD_ASSERT(expr);
    m_condExpr = std::move(expr);
}

/* ************************************************************************* */

void SwitchStmt::setBodyStmt(UniquePtr<CompoundStmt> stmt)
{
    SHARD_ASSERT(stmt);
    m_bodyStmt = std::move(stmt);
}

/* ************************************************************************* */

UniquePtr<SwitchStmt> SwitchStmt::make(UniquePtr<Expr> condExpr, UniquePtr<CompoundStmt> bodyStmt, SourceRange range)
{
    return makeUnique<SwitchStmt>(std::move(condExpr), std::move(bodyStmt), range);
}

/* ************************************************************************* */

}

/* ************************************************************************* */

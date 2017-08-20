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
#include "shard/ast/SwitchStmt.hpp"

// Shard
#include "shard/utility.hpp"
#include "shard/Assert.hpp"
#include "shard/ast/Expr.hpp"
#include "shard/ast/CompoundStmt.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

SwitchStmt::SwitchStmt(UniquePtr<Expr> condExpr, UniquePtr<CompoundStmt> bodyStmt, SourceRange range)
    : Stmt(Kind, moveValue(range))
    , m_condExpr(moveValue(condExpr))
    , m_bodyStmt(moveValue(bodyStmt))
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
    m_condExpr = moveValue(expr);
}

/* ************************************************************************* */

void SwitchStmt::setBodyStmt(UniquePtr<CompoundStmt> stmt)
{
    SHARD_ASSERT(stmt);
    m_bodyStmt = moveValue(stmt);
}

/* ************************************************************************* */

UniquePtr<SwitchStmt> SwitchStmt::make(UniquePtr<Expr> condExpr, UniquePtr<CompoundStmt> bodyStmt, SourceRange range)
{
    return makeUnique<SwitchStmt>(moveValue(condExpr), moveValue(bodyStmt), moveValue(range));
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

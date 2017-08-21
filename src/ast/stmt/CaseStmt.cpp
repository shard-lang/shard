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
#include "shard/ast/stmt/CaseStmt.hpp"

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

CaseStmt::CaseStmt(UniquePtr<Expr> expr, PtrDynamicArray<Stmt> stmts, SourceRange range)
    : Stmt(Kind, moveValue(range))
    , m_expr(moveValue(expr))
    , m_statements(moveValue(stmts))
{
    SHARD_ASSERT(m_expr);
}

/* ************************************************************************* */

CaseStmt::~CaseStmt() = default;

/* ************************************************************************* */

void CaseStmt::setExpr(UniquePtr<Expr> expr)
{
    SHARD_ASSERT(expr);
    m_expr = moveValue(expr);
}

/* ************************************************************************* */

void CaseStmt::setStmts(PtrDynamicArray<Stmt> stmts)
{
    m_statements = moveValue(stmts);
}

/* ************************************************************************* */

void CaseStmt::addStmt(UniquePtr<Stmt> stmt)
{
    m_statements.push_back(moveValue(stmt));
}

/* ************************************************************************* */

UniquePtr<CaseStmt> CaseStmt::make(UniquePtr<Expr> expr, PtrDynamicArray<Stmt> stmts, SourceRange range)
{
    return makeUnique<CaseStmt>(moveValue(expr), moveValue(stmts), moveValue(range));
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

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
#include "shard/ast/Stmt.hpp"

// Shard
#include "shard/ast/Expr.hpp"
#include "shard/ast/Decl.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

Stmt::Stmt(StmtKind kind, SourceRange range) noexcept
    : LocationInfo(moveValue(range))
    , m_kind(kind)
{
    // Nothing to do
}

/* ************************************************************************* */

Stmt::~Stmt() = default;

/* ************************************************************************* */

ExprStmt::ExprStmt(UniquePtr<Expr> expr, SourceRange range) noexcept
    : Stmt(StmtKind::Expr, moveValue(range))
    , m_expr(moveValue(expr))
{
    // Nothing to do
}

/* ************************************************************************* */

DeclStmt::DeclStmt(UniquePtr<Decl> decl, SourceRange range) noexcept
    : Stmt(StmtKind::Decl, moveValue(range))
    , m_decl(moveValue(decl))
{
    // Nothing to do
}

/* ************************************************************************* */

DeclStmt::~DeclStmt() = default;

/* ************************************************************************* */

CompoundStmt::CompoundStmt(DynamicArray<UniquePtr<Stmt>> stmts, SourceRange range) noexcept
    : Stmt(StmtKind::Compound, moveValue(range))
    , StmtContainer(moveValue(stmts))
{
    // Nothing to do
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

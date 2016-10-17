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

IfStmt::IfStmt(UniquePtr<Expr> cond, UniquePtr<Stmt> trueStmt, UniquePtr<Stmt> falseStmt, SourceRange range) noexcept
    : Stmt(StmtKind::If, moveValue(range))
    , m_cond(moveValue(cond))
    , m_trueStmt(moveValue(trueStmt))
    , m_falseStmt(moveValue(falseStmt))
{
    // Nothing to do
}

/* ************************************************************************* */

WhileStmt::WhileStmt(UniquePtr<Expr> cond, UniquePtr<Stmt> stmt, SourceRange range) noexcept
    : Stmt(StmtKind::While, moveValue(range))
    , m_cond(moveValue(cond))
    , m_stmt(moveValue(stmt))
{
    // Nothing to do
}

/* ************************************************************************* */

DoWhileStmt::DoWhileStmt(UniquePtr<Expr> cond, UniquePtr<Stmt> stmt, SourceRange range) noexcept
    : Stmt(StmtKind::DoWhile, moveValue(range))
    , m_cond(moveValue(cond))
    , m_stmt(moveValue(stmt))
{
    // Nothing to do
}

/* ************************************************************************* */

ForStmt::ForStmt(UniquePtr<Stmt> init, UniquePtr<Expr> cond, UniquePtr<Expr> inc, UniquePtr<Stmt> stmt, SourceRange range) noexcept
    : Stmt(StmtKind::For, moveValue(range))
    , m_init(moveValue(init))
    , m_cond(moveValue(cond))
    , m_inc(moveValue(inc))
    , m_stmt(moveValue(stmt))
{
    // Nothing to do
}

/* ************************************************************************* */

SwitchStmt::SwitchStmt(UniquePtr<Expr> test, UniquePtr<CompoundStmt> stmt, SourceRange range) noexcept
    : Stmt(StmtKind::Switch, moveValue(range))
    , m_test(moveValue(test))
    , m_stmt(moveValue(stmt))
{
    // Nothing to do
}

/* ************************************************************************* */

CaseStmt::CaseStmt(UniquePtr<Expr> test, UniquePtr<Stmt> stmt, SourceRange range) noexcept
    : Stmt(StmtKind::Case, moveValue(range))
    , m_test(moveValue(test))
    , m_stmt(moveValue(stmt))
{
    // Nothing to do
}

/* ************************************************************************* */

DefaultStmt::DefaultStmt(UniquePtr<Stmt> stmt, SourceRange range) noexcept
    : Stmt(StmtKind::Default, moveValue(range))
    , m_stmt(moveValue(stmt))
{
    // Nothing to do
}

/* ************************************************************************* */

ContinueStmt::ContinueStmt(SourceRange range) noexcept
    : Stmt(StmtKind::Continue, moveValue(range))
{
    // Nothing to do
}

/* ************************************************************************* */

BreakStmt::BreakStmt(SourceRange range) noexcept
    : Stmt(StmtKind::Break, moveValue(range))
{
    // Nothing to do
}

/* ************************************************************************* */

ReturnStmt::ReturnStmt(UniquePtr<Expr> res, SourceRange range) noexcept
    : Stmt(StmtKind::Return, moveValue(range))
    , m_res(moveValue(res))
{
    // Nothing to do
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

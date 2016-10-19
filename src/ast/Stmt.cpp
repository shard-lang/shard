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
#include "shard/Assert.hpp"
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
    SHARD_ASSERT(m_decl);
}

/* ************************************************************************* */

CompoundStmt::CompoundStmt(DynamicArray<UniquePtr<Stmt>> stmts, SourceRange range) noexcept
    : Stmt(StmtKind::Compound, moveValue(range))
    , StmtContainer(moveValue(stmts))
{
    // Nothing to do
}

/* ************************************************************************* */

IfStmt::IfStmt(UniquePtr<Expr> condExpr, UniquePtr<Stmt> thenStmt, UniquePtr<Stmt> elseStmt, SourceRange range) noexcept
    : Stmt(StmtKind::If, moveValue(range))
    , m_condExpr(moveValue(condExpr))
    , m_thenStmt(moveValue(thenStmt))
    , m_elseStmt(moveValue(elseStmt))
{
    SHARD_ASSERT(m_condExpr);
    SHARD_ASSERT(m_thenStmt);
}

/* ************************************************************************* */

WhileStmt::WhileStmt(UniquePtr<Expr> condExpr, UniquePtr<Stmt> bodyStmt, SourceRange range) noexcept
    : Stmt(StmtKind::While, moveValue(range))
    , m_condExpr(moveValue(condExpr))
    , m_bodyStmt(moveValue(bodyStmt))
{
    SHARD_ASSERT(m_condExpr);
    SHARD_ASSERT(m_bodyStmt);
}

/* ************************************************************************* */

DoWhileStmt::DoWhileStmt(UniquePtr<Expr> condExpr, UniquePtr<CompoundStmt> bodyStmt, SourceRange range) noexcept
    : Stmt(StmtKind::DoWhile, moveValue(range))
    , m_condExpr(moveValue(condExpr))
    , m_bodyStmt(moveValue(bodyStmt))
{
    SHARD_ASSERT(m_condExpr);
    SHARD_ASSERT(m_bodyStmt);
}

/* ************************************************************************* */

ForStmt::ForStmt(UniquePtr<Stmt> initStmt, UniquePtr<Expr> condExpr, UniquePtr<Expr> incExpr, UniquePtr<Stmt> bodyStmt, SourceRange range) noexcept
    : Stmt(StmtKind::For, moveValue(range))
    , m_initStmt(moveValue(initStmt))
    , m_condExpr(moveValue(condExpr))
    , m_incExpr(moveValue(incExpr))
    , m_bodyStmt(moveValue(bodyStmt))
{
    SHARD_ASSERT(m_initStmt);
    SHARD_ASSERT(m_bodyStmt);
}

/* ************************************************************************* */

SwitchStmt::SwitchStmt(UniquePtr<Expr> condExpr, UniquePtr<CompoundStmt> bodyStmt, SourceRange range) noexcept
    : Stmt(StmtKind::Switch, moveValue(range))
    , m_condExpr(moveValue(condExpr))
    , m_bodyStmt(moveValue(bodyStmt))
{
    SHARD_ASSERT(m_condExpr);
    SHARD_ASSERT(m_bodyStmt);
}

/* ************************************************************************* */

CaseStmt::CaseStmt(UniquePtr<Expr> expr, UniquePtr<Stmt> bodyStmt, SourceRange range) noexcept
    : Stmt(StmtKind::Case, moveValue(range))
    , m_expr(moveValue(expr))
    , m_bodyStmt(moveValue(bodyStmt))
{
    SHARD_ASSERT(m_expr);
}

/* ************************************************************************* */

DefaultStmt::DefaultStmt(UniquePtr<Stmt> bodyStmt, SourceRange range) noexcept
    : Stmt(StmtKind::Default, moveValue(range))
    , m_bodyStmt(moveValue(bodyStmt))
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

ReturnStmt::ReturnStmt(UniquePtr<Expr> resExpr, SourceRange range) noexcept
    : Stmt(StmtKind::Return, moveValue(range))
    , m_resExpr(moveValue(resExpr))
{
    // Nothing to do
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

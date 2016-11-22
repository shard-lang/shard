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

Stmt::~Stmt() = default;

/* ************************************************************************* */

Stmt::Stmt(StmtKind kind, SourceRange range) noexcept
    : LocationInfo(moveValue(range))
    , m_kind(kind)
{
    // Nothing to do
}

/* ************************************************************************* */

ExprStmt::ExprStmt(UniquePtr<Expr> expr, SourceRange range) noexcept
    : Stmt(StmtKind::Expr, moveValue(range))
    , m_expr(moveValue(expr))
{
    // Nothing to do
}

/* ************************************************************************* */

ExprStmt::~ExprStmt() = default;

/* ************************************************************************* */

void ExprStmt::setExpr(UniquePtr<Expr> expr) noexcept
{
    SHARD_ASSERT(expr);
    m_expr = moveValue(expr);
}

/* ************************************************************************* */

DeclStmt::DeclStmt(UniquePtr<Decl> decl, SourceRange range) noexcept
    : Stmt(StmtKind::Decl, moveValue(range))
    , m_decl(moveValue(decl))
{
    SHARD_ASSERT(m_decl);
}

/* ************************************************************************* */

DeclStmt::~DeclStmt() = default;

/* ************************************************************************* */

void DeclStmt::setDecl(UniquePtr<Decl> decl) noexcept
{
    SHARD_ASSERT(decl);
    m_decl = moveValue(decl);
}

/* ************************************************************************* */

CompoundStmt::CompoundStmt(PtrDynamicArray<Stmt> stmts, SourceRange range) noexcept
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

IfStmt::~IfStmt() = default;

/* ************************************************************************* */

void IfStmt::setCondExpr(UniquePtr<Expr> expr) noexcept
{
    SHARD_ASSERT(expr);
    m_condExpr = moveValue(expr);
}

/* ************************************************************************* */

void IfStmt::setThenStmt(UniquePtr<Stmt> stmt) noexcept
{
    SHARD_ASSERT(stmt);
    m_thenStmt = moveValue(stmt);
}

/* ************************************************************************* */

void IfStmt::setElseStmt(UniquePtr<Stmt> stmt) noexcept
{
    m_elseStmt = moveValue(stmt);
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

WhileStmt::~WhileStmt() = default;

/* ************************************************************************* */

void WhileStmt::setCondExpr(UniquePtr<Expr> expr) noexcept
{
    SHARD_ASSERT(expr);
    m_condExpr = moveValue(expr);
}

/* ************************************************************************* */

void WhileStmt::setBodyStmt(UniquePtr<Stmt> stmt) noexcept
{
    SHARD_ASSERT(stmt);
    m_bodyStmt = moveValue(stmt);
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

DoWhileStmt::~DoWhileStmt() = default;

/* ************************************************************************* */

void DoWhileStmt::setCondExpr(UniquePtr<Expr> expr) noexcept
{
    SHARD_ASSERT(expr);
    m_condExpr = moveValue(expr);
}

/* ************************************************************************* */

void DoWhileStmt::setBodyStmt(UniquePtr<CompoundStmt> stmt) noexcept
{
    SHARD_ASSERT(stmt);
    m_bodyStmt = moveValue(stmt);
}

/* ************************************************************************* */

ForStmt::ForStmt(UniquePtr<Stmt> initStmt, UniquePtr<Expr> condExpr, UniquePtr<Expr> incExpr, UniquePtr<Stmt> bodyStmt, SourceRange range) noexcept
    : Stmt(StmtKind::For, moveValue(range))
    , m_initStmt(moveValue(initStmt))
    , m_condExpr(moveValue(condExpr))
    , m_incExpr(moveValue(incExpr))
    , m_bodyStmt(moveValue(bodyStmt))
{
    //SHARD_ASSERT(m_initStmt);
    SHARD_ASSERT(m_bodyStmt);
}

/* ************************************************************************* */

ForStmt::~ForStmt() = default;

/* ************************************************************************* */

void ForStmt::setInitStmt(UniquePtr<Stmt> stmt) noexcept
{
    SHARD_ASSERT(stmt);
    m_initStmt = moveValue(stmt);
}

/* ************************************************************************* */

void ForStmt::setCondExpr(UniquePtr<Expr> expr) noexcept
{
    SHARD_ASSERT(expr);
    m_condExpr = moveValue(expr);
}

/* ************************************************************************* */

void ForStmt::setIncExpr(UniquePtr<Expr> expr) noexcept
{
    SHARD_ASSERT(expr);
    m_incExpr = moveValue(expr);
}

/* ************************************************************************* */

void ForStmt::setBodyStmt(UniquePtr<Stmt> stmt) noexcept
{
    SHARD_ASSERT(stmt);
    m_bodyStmt = moveValue(stmt);
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

SwitchStmt::~SwitchStmt() = default;

/* ************************************************************************* */

void SwitchStmt::setCondExpr(UniquePtr<Expr> expr) noexcept
{
    SHARD_ASSERT(expr);
    m_condExpr = moveValue(expr);
}

/* ************************************************************************* */

void SwitchStmt::setBodyStmt(UniquePtr<CompoundStmt> stmt) noexcept
{
    SHARD_ASSERT(stmt);
    m_bodyStmt = moveValue(stmt);
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

CaseStmt::~CaseStmt() = default;

/* ************************************************************************* */

void CaseStmt::setExpr(UniquePtr<Expr> expr) noexcept
{
    SHARD_ASSERT(expr);
    m_expr = moveValue(expr);
}

/* ************************************************************************* */

void CaseStmt::setBodyStmt(UniquePtr<Stmt> stmt) noexcept
{
    SHARD_ASSERT(stmt);
    m_bodyStmt = moveValue(stmt);
}

/* ************************************************************************* */

DefaultStmt::DefaultStmt(UniquePtr<Stmt> bodyStmt, SourceRange range) noexcept
    : Stmt(StmtKind::Default, moveValue(range))
    , m_bodyStmt(moveValue(bodyStmt))
{
    // Nothing to do
}

/* ************************************************************************* */

DefaultStmt::~DefaultStmt() = default;

/* ************************************************************************* */

void DefaultStmt::setBodyStmt(UniquePtr<Stmt> stmt) noexcept
{
    SHARD_ASSERT(stmt);
    m_bodyStmt = moveValue(stmt);
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

ReturnStmt::~ReturnStmt() = default;

/* ************************************************************************* */

void ReturnStmt::setResExpr(UniquePtr<Expr> expr) noexcept
{
    m_resExpr = moveValue(expr);
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

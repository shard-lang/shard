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

Stmt::Stmt(StmtKind kind, SourceRange range)
    : Node(moveValue(range))
    , m_kind(kind)
{
    // Nothing to do
}

/* ************************************************************************* */

ExprStmt::ExprStmt(UniquePtr<Expr> expr, SourceRange range)
    : Stmt(Kind, moveValue(range))
    , m_expr(moveValue(expr))
{
    // Nothing to do
}

/* ************************************************************************* */

ExprStmt::~ExprStmt() = default;

/* ************************************************************************* */

void ExprStmt::setExpr(UniquePtr<Expr> expr)
{
    SHARD_ASSERT(expr);
    m_expr = moveValue(expr);
}

/* ************************************************************************* */

UniquePtr<ExprStmt> ExprStmt::make(UniquePtr<Expr> expr, SourceRange range)
{
    return makeUnique<ExprStmt>(moveValue(expr), moveValue(range));
}

/* ************************************************************************* */

DeclStmt::DeclStmt(UniquePtr<Decl> decl, SourceRange range)
    : Stmt(Kind, moveValue(range))
    , m_decl(moveValue(decl))
{
    SHARD_ASSERT(m_decl);
}

/* ************************************************************************* */

DeclStmt::~DeclStmt() = default;

/* ************************************************************************* */

void DeclStmt::setDecl(UniquePtr<Decl> decl)
{
    SHARD_ASSERT(decl);
    m_decl = moveValue(decl);
}

/* ************************************************************************* */

UniquePtr<DeclStmt> DeclStmt::make(UniquePtr<Decl> decl, SourceRange range)
{
    return makeUnique<DeclStmt>(moveValue(decl), moveValue(range));
}

/* ************************************************************************* */

CompoundStmt::CompoundStmt(PtrDynamicArray<Stmt> stmts, SourceRange range)
    : Stmt(Kind, moveValue(range))
    , m_statements(moveValue(stmts))
{
    // Nothing to do
}

/* ************************************************************************* */

CompoundStmt::~CompoundStmt() = default;

/* ************************************************************************* */

void CompoundStmt::setStmts(PtrDynamicArray<Stmt> stmts)
{
    m_statements = moveValue(stmts);
}

/* ************************************************************************* */

void CompoundStmt::addStmt(UniquePtr<Stmt> stmt)
{
    m_statements.push_back(moveValue(stmt));
}

/* ************************************************************************* */

UniquePtr<CompoundStmt> CompoundStmt::make(PtrDynamicArray<Stmt> stmts, SourceRange range)
{
    return makeUnique<CompoundStmt>(moveValue(stmts), moveValue(range));
}

/* ************************************************************************* */

IfStmt::IfStmt(UniquePtr<Expr> condExpr, UniquePtr<Stmt> thenStmt, UniquePtr<Stmt> elseStmt, SourceRange range)
    : Stmt(Kind, moveValue(range))
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

void IfStmt::setCondExpr(UniquePtr<Expr> expr)
{
    SHARD_ASSERT(expr);
    m_condExpr = moveValue(expr);
}

/* ************************************************************************* */

void IfStmt::setThenStmt(UniquePtr<Stmt> stmt)
{
    SHARD_ASSERT(stmt);
    m_thenStmt = moveValue(stmt);
}

/* ************************************************************************* */

void IfStmt::setElseStmt(UniquePtr<Stmt> stmt)
{
    m_elseStmt = moveValue(stmt);
}

/* ************************************************************************* */

UniquePtr<IfStmt> IfStmt::make(UniquePtr<Expr> condExpr, UniquePtr<Stmt> thenStmt, UniquePtr<Stmt> elseStmt, SourceRange range)
{
    return makeUnique<IfStmt>(moveValue(condExpr), moveValue(thenStmt), moveValue(elseStmt), moveValue(range));
}

/* ************************************************************************* */

WhileStmt::WhileStmt(UniquePtr<Expr> condExpr, UniquePtr<Stmt> bodyStmt, SourceRange range)
    : Stmt(Kind, moveValue(range))
    , m_condExpr(moveValue(condExpr))
    , m_bodyStmt(moveValue(bodyStmt))
{
    SHARD_ASSERT(m_condExpr);
    SHARD_ASSERT(m_bodyStmt);
}

/* ************************************************************************* */

WhileStmt::~WhileStmt() = default;

/* ************************************************************************* */

void WhileStmt::setCondExpr(UniquePtr<Expr> expr)
{
    SHARD_ASSERT(expr);
    m_condExpr = moveValue(expr);
}

/* ************************************************************************* */

void WhileStmt::setBodyStmt(UniquePtr<Stmt> stmt)
{
    SHARD_ASSERT(stmt);
    m_bodyStmt = moveValue(stmt);
}

/* ************************************************************************* */

UniquePtr<WhileStmt> WhileStmt::make(UniquePtr<Expr> condExpr, UniquePtr<Stmt> bodyStmt, SourceRange range)
{
    return makeUnique<WhileStmt>(moveValue(condExpr), moveValue(bodyStmt), moveValue(range));
}

/* ************************************************************************* */

DoWhileStmt::DoWhileStmt(UniquePtr<Expr> condExpr, UniquePtr<CompoundStmt> bodyStmt, SourceRange range)
    : Stmt(Kind, moveValue(range))
    , m_condExpr(moveValue(condExpr))
    , m_bodyStmt(moveValue(bodyStmt))
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
    m_condExpr = moveValue(expr);
}

/* ************************************************************************* */

void DoWhileStmt::setBodyStmt(UniquePtr<CompoundStmt> stmt)
{
    SHARD_ASSERT(stmt);
    m_bodyStmt = moveValue(stmt);
}

/* ************************************************************************* */

UniquePtr<DoWhileStmt> DoWhileStmt::make(UniquePtr<Expr> condExpr, UniquePtr<CompoundStmt> bodyStmt, SourceRange range)
{
    return makeUnique<DoWhileStmt>(moveValue(condExpr), moveValue(bodyStmt), moveValue(range));
}

/* ************************************************************************* */

ForStmt::ForStmt(UniquePtr<Stmt> initStmt, UniquePtr<Expr> condExpr, UniquePtr<Expr> incExpr, UniquePtr<Stmt> bodyStmt, SourceRange range)
    : Stmt(Kind, moveValue(range))
    , m_initStmt(moveValue(initStmt))
    , m_condExpr(moveValue(condExpr))
    , m_incExpr(moveValue(incExpr))
    , m_bodyStmt(moveValue(bodyStmt))
{
    SHARD_ASSERT(m_bodyStmt);
}

/* ************************************************************************* */

ForStmt::~ForStmt() = default;

/* ************************************************************************* */

void ForStmt::setInitStmt(UniquePtr<Stmt> stmt)
{
    SHARD_ASSERT(stmt);
    m_initStmt = moveValue(stmt);
}

/* ************************************************************************* */

void ForStmt::setCondExpr(UniquePtr<Expr> expr)
{
    SHARD_ASSERT(expr);
    m_condExpr = moveValue(expr);
}

/* ************************************************************************* */

void ForStmt::setIncExpr(UniquePtr<Expr> expr)
{
    SHARD_ASSERT(expr);
    m_incExpr = moveValue(expr);
}

/* ************************************************************************* */

void ForStmt::setBodyStmt(UniquePtr<Stmt> stmt)
{
    SHARD_ASSERT(stmt);
    m_bodyStmt = moveValue(stmt);
}

/* ************************************************************************* */

UniquePtr<ForStmt> ForStmt::make(UniquePtr<Stmt> initStmt, UniquePtr<Expr> condExpr, UniquePtr<Expr> incExpr, UniquePtr<Stmt> bodyStmt, SourceRange range)
{
    return makeUnique<ForStmt>(moveValue(initStmt), moveValue(condExpr), moveValue(incExpr), moveValue(bodyStmt), moveValue(range));
}

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

DefaultStmt::DefaultStmt(PtrDynamicArray<Stmt> stmts, SourceRange range)
    : Stmt(Kind, moveValue(range))
    , m_statements(moveValue(stmts))
{
    // Nothing to do
}

/* ************************************************************************* */

DefaultStmt::~DefaultStmt() = default;

/* ************************************************************************* */

void DefaultStmt::setStmts(PtrDynamicArray<Stmt> stmts)
{
    m_statements = moveValue(stmts);
}

/* ************************************************************************* */

void DefaultStmt::addStmt(UniquePtr<Stmt> stmt)
{
    m_statements.push_back(moveValue(stmt));
}

/* ************************************************************************* */

UniquePtr<DefaultStmt> DefaultStmt::make(PtrDynamicArray<Stmt> body, SourceRange range)
{
    return makeUnique<DefaultStmt>(moveValue(body), moveValue(range));
}

/* ************************************************************************* */

ContinueStmt::ContinueStmt(SourceRange range)
    : Stmt(Kind, moveValue(range))
{
    // Nothing to do
}

/* ************************************************************************* */

ContinueStmt::~ContinueStmt() = default;

/* ************************************************************************* */

UniquePtr<ContinueStmt> ContinueStmt::make(SourceRange range)
{
    return makeUnique<ContinueStmt>(moveValue(range));
}

/* ************************************************************************* */

BreakStmt::BreakStmt(SourceRange range)
    : Stmt(Kind, moveValue(range))
{
    // Nothing to do
}

/* ************************************************************************* */

BreakStmt::~BreakStmt() = default;

/* ************************************************************************* */

UniquePtr<BreakStmt> BreakStmt::make(SourceRange range)
{
    return makeUnique<BreakStmt>(moveValue(range));
}

/* ************************************************************************* */

ReturnStmt::ReturnStmt(UniquePtr<Expr> resExpr, SourceRange range)
    : Stmt(Kind, moveValue(range))
    , m_resExpr(moveValue(resExpr))
{
    // Nothing to do
}

/* ************************************************************************* */

ReturnStmt::~ReturnStmt() = default;

/* ************************************************************************* */

void ReturnStmt::setResExpr(UniquePtr<Expr> expr)
{
    m_resExpr = moveValue(expr);
}

/* ************************************************************************* */

UniquePtr<ReturnStmt> ReturnStmt::make(UniquePtr<Expr> resExpr, SourceRange range)
{
    return makeUnique<ReturnStmt>(moveValue(resExpr), moveValue(range));
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

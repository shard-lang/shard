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
#include "shard/ast/Decl.hpp"

// Shard
#include "shard/Assert.hpp"
#include "shard/ast/DeclContext.hpp"
#include "shard/ast/Stmt.hpp"
#include "shard/ast/Expr.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

Decl::Decl(ViewPtr<DeclContext> context, DeclKind kind, SourceRange range) noexcept
    : LocationInfo(moveValue(range))
    , m_kind(kind)
{
    // Nothing to do
}

/* ************************************************************************* */

Decl::~Decl() = default;

/* ************************************************************************* */

NamedDecl::NamedDecl(ViewPtr<DeclContext> context, DeclKind kind, String name,
    SourceRange range) noexcept
    : Decl(context, kind, moveValue(range))
    , m_name(moveValue(name))
{
    SHARD_ASSERT(!m_name.empty());
}

/* ************************************************************************* */

VariableDecl::VariableDecl(ViewPtr<DeclContext> context, TypeInfo type,
    String name, UniquePtr<Expr> initExpr, SourceRange range) noexcept
    : NamedDecl(context, DeclKind::Variable, moveValue(name), moveValue(range))
    , m_typeInfo(moveValue(type))
    , m_initExpr(moveValue(initExpr))
{
    // Nothing to do
}

/* ************************************************************************* */

VariableDecl::VariableDecl(ViewPtr<DeclContext> context,
    ViewPtr<const Type> type, String name, UniquePtr<Expr> initExpr,
    SourceRange range) noexcept
    : VariableDecl(context, TypeInfo{type}, moveValue(name),
          moveValue(initExpr), moveValue(range))
{
    // Nothing to do
}

/* ************************************************************************* */

VariableDecl::~VariableDecl() = default;

/* ************************************************************************* */

void VariableDecl::setInitExpr(UniquePtr<Expr> expr) noexcept
{
    m_initExpr = moveValue(expr);
}

/* ************************************************************************* */

FunctionDecl::FunctionDecl(ViewPtr<DeclContext> context, TypeInfo retType,
    String name, UniquePtr<CompoundStmt> bodyStmt,
    PtrDynamicArray<VariableDecl> params, SourceRange range) noexcept
    : NamedDecl(context, DeclKind::Function, moveValue(name), moveValue(range))
    , DeclContext(context)
    , m_retTypeInfo(moveValue(retType))
    , m_bodyStmt(moveValue(bodyStmt))
{
    SHARD_ASSERT(m_bodyStmt);

    // Add parameters
    addDeclarations(moveValue(params));
}

/* ************************************************************************* */

FunctionDecl::~FunctionDecl() = default;

/* ************************************************************************* */

void FunctionDecl::setBodyStmt(UniquePtr<CompoundStmt> stmt) noexcept
{
    SHARD_ASSERT(stmt);
    m_bodyStmt = moveValue(stmt);
}

/* ************************************************************************* */

void FunctionDecl::setParameters(PtrDynamicArray<VariableDecl> params) noexcept
{
    removeDeclarations();
    addDeclarations(moveValue(params));
}

/* ************************************************************************* */

ClassDecl::ClassDecl(ViewPtr<DeclContext> context, String name,
    PtrDynamicArray<Decl> decls, SourceRange range) noexcept
    : NamedDecl(context, DeclKind::Class, moveValue(name), moveValue(range))
    , DeclContext(context)
{
    addDeclarations(moveValue(decls));
}

/* ************************************************************************* */

ClassDecl::~ClassDecl() = default;

/* ************************************************************************* */

// NamespaceDecl::NamespaceDecl(ViewPtr<DeclContext> context, String name, PtrDynamicArray<Decl> decls, SourceRange range) noexcept
//     : NamedDecl(context, DeclKind::Namespace, moveValue(name), moveValue(range))
//     , DeclContext(context)
// {
//     addDeclarations(moveValue(decls));
// }

/* ************************************************************************* */

// NamespaceDecl::~NamespaceDecl() = default;

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

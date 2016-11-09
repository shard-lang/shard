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
    , m_context(context)
    , m_kind(kind)
{
    // Nothing to do
}

/* ************************************************************************* */

Decl::~Decl() = default;

/* ************************************************************************* */

NamedDecl::NamedDecl(ViewPtr<DeclContext> context, DeclKind kind, String name, SourceRange range) noexcept
    : Decl(context, kind, moveValue(range))
    , m_name(moveValue(name))
{
    SHARD_ASSERT(!m_name.empty());
}

/* ************************************************************************* */

VariableDecl::VariableDecl(ViewPtr<DeclContext> context, String name, TypeInfo type, UniquePtr<Expr> initExpr, SourceRange range) noexcept
    : NamedDecl(context, DeclKind::Variable, moveValue(name), moveValue(range))
    , m_typeInfo(moveValue(type))
    , m_initExpr(moveValue(initExpr))
{
    // Nothing to do
}

/* ************************************************************************* */

VariableDecl::~VariableDecl() = default;

/* ************************************************************************* */

FunctionDecl::FunctionDecl(ViewPtr<DeclContext> context, String name,
    TypeInfo retType, UniquePtr<CompoundStmt> bodyStmt,
    DynamicArray<UniquePtr<VariableDecl>> params, SourceRange range
) noexcept
    : NamedDecl(context, DeclKind::Function, moveValue(name), moveValue(range))
    , DeclContext(context)
    , m_retTypeInfo(moveValue(retType))
    , m_bodyStmt(moveValue(bodyStmt))
{
    SHARD_ASSERT(m_bodyStmt);

    // Add parameters
    for (auto&& param : params)
        addDeclaration(moveValue(param));
}

/* ************************************************************************* */

FunctionDecl::~FunctionDecl() = default;

/* ************************************************************************* */

ClassDecl::ClassDecl(ViewPtr<DeclContext> context, String name, DynamicArray<UniquePtr<Decl>> decls, SourceRange range) noexcept
    : NamedDecl(context, DeclKind::Class, moveValue(name), moveValue(range))
    , DeclContext(context)
{
    for (auto&& decl : decls)
        addDeclaration(moveValue(decl));
}

/* ************************************************************************* */

ClassDecl::~ClassDecl() = default;

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

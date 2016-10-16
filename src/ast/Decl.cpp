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
    // Register declaration
    if (m_context)
        m_context->addDeclaration(this);
}

/* ************************************************************************* */

Decl::~Decl()
{
    // Unregister declaration
    if (m_context)
        m_context->removeDeclaration(this);
}

/* ************************************************************************* */

NamedDecl::NamedDecl(ViewPtr<DeclContext> context, DeclKind kind, String name, SourceRange range) noexcept
    : Decl(context, kind, moveValue(range))
    , m_name(moveValue(name))
{
    // Nothing to do
}

/* ************************************************************************* */

VariableDecl::VariableDecl(ViewPtr<DeclContext> context, String name, TypeInfo type, UniquePtr<Expr> init, SourceRange range) noexcept
    : NamedDecl(context, DeclKind::Variable, moveValue(name), moveValue(range))
    , m_typeInfo(moveValue(type))
    , m_initializer(moveValue(init))
{
    // Nothing to do
}

/* ************************************************************************* */

VariableDecl::~VariableDecl() = default;

/* ************************************************************************* */

FunctionDecl::FunctionDecl(ViewPtr<DeclContext> context, String name,
    TypeInfo retType, DynamicArray<UniquePtr<VariableDecl>> params,
    UniquePtr<CompoundStmt> body, SourceRange range
) noexcept
    : NamedDecl(context, DeclKind::Function, moveValue(name), moveValue(range))
    , m_retTypeInfo(moveValue(retType))
    , m_parameters(moveValue(params))
    , m_body(moveValue(body))
{
    // Nothing to do
}

/* ************************************************************************* */

FunctionDecl::~FunctionDecl() = default;

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

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
#include "shard/utility.hpp"
#include "shard/Assert.hpp"
#include "shard/ast/Stmt.hpp"
#include "shard/ast/Expr.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

Decl::Decl(DeclKind kind, String name, SourceRange range)
    : Node(moveValue(range))
    , m_kind(kind)
    , m_name(moveValue(name))
{
    // Nothing to do
}

/* ************************************************************************* */

Decl::~Decl() = default;

/* ************************************************************************* */

void Decl::setName(String name)
{
    m_name = moveValue(name);
}

/* ************************************************************************* */

VariableDecl::VariableDecl(Type type, String name, UniquePtr<Expr> initExpr, SourceRange range)
    : Decl(Kind, moveValue(name), moveValue(range))
    , m_type(moveValue(type))
    , m_initExpr(moveValue(initExpr))
{
    // Nothing to do
}

/* ************************************************************************* */

VariableDecl::~VariableDecl() = default;

/* ************************************************************************* */

void VariableDecl::setType(Type type)
{
    m_type = moveValue(type);
}

/* ************************************************************************* */

void VariableDecl::setInitExpr(UniquePtr<Expr> expr)
{
    m_initExpr = moveValue(expr);
}

/* ************************************************************************* */

UniquePtr<VariableDecl> VariableDecl::make(Type type, String name, UniquePtr<Expr> initExpr, SourceRange range)
{
    return makeUnique<VariableDecl>(moveValue(type), moveValue(name), moveValue(initExpr), moveValue(range));
}

/* ************************************************************************* */

FunctionDecl::FunctionDecl(Type retType, String name, UniquePtr<CompoundStmt> bodyStmt,
    PtrDynamicArray<VariableDecl> params, SourceRange range)
    : Decl(Kind, moveValue(name), moveValue(range))
    , m_retType(moveValue(retType))
    , m_parameters(moveValue(params))
    , m_bodyStmt(moveValue(bodyStmt))
{
    SHARD_ASSERT(m_bodyStmt);
}

/* ************************************************************************* */

FunctionDecl::~FunctionDecl() = default;

/* ************************************************************************* */

void FunctionDecl::setRetType(Type info)
{
    m_retType = moveValue(info);
}

/* ************************************************************************* */

void FunctionDecl::setBodyStmt(UniquePtr<CompoundStmt> stmt)
{
    SHARD_ASSERT(stmt);
    m_bodyStmt = moveValue(stmt);
}

/* ************************************************************************* */

void FunctionDecl::setParameters(PtrDynamicArray<VariableDecl> params)
{
    m_parameters = moveValue(params);
}

/* ************************************************************************* */

UniquePtr<FunctionDecl> FunctionDecl::make(Type retType, String name, UniquePtr<CompoundStmt> bodyStmt,
        PtrDynamicArray<VariableDecl> params, SourceRange range)
{
    return makeUnique<FunctionDecl>(moveValue(retType), moveValue(name), moveValue(bodyStmt), moveValue(params), moveValue(range));
}

/* ************************************************************************* */

CompoundDecl::CompoundDecl(DeclKind kind, String name, PtrDynamicArray<Decl> decls, SourceRange range)
    : Decl(kind, moveValue(name), moveValue(range))
    , m_declarations(moveValue(decls))
{
    // Nothing to do
}

/* ************************************************************************* */

CompoundDecl::~CompoundDecl() = default;

/* ************************************************************************* */

void CompoundDecl::setDecls(PtrDynamicArray<Decl> decls)
{
    m_declarations = moveValue(decls);
}

/* ************************************************************************* */

void CompoundDecl::addDecl(UniquePtr<Decl> decl)
{
    m_declarations.push_back(moveValue(decl));
}

/* ************************************************************************* */

ClassDecl::ClassDecl(String name, PtrDynamicArray<Decl> decls, SourceRange range)
    : CompoundDecl(Kind, moveValue(name), moveValue(decls), moveValue(range))
{
    // Nothing to do
}

/* ************************************************************************* */

ClassDecl::~ClassDecl() = default;

/* ************************************************************************* */

UniquePtr<ClassDecl> ClassDecl::make(String name, PtrDynamicArray<Decl> decls, SourceRange range)
{
    return makeUnique<ClassDecl>(moveValue(name), moveValue(decls), moveValue(range));
}

/* ************************************************************************* */

NamespaceDecl::NamespaceDecl(String name, PtrDynamicArray<Decl> decls, SourceRange range)
    : CompoundDecl(Kind, moveValue(name), moveValue(decls), moveValue(range))
{
    // Nothing to do
}

/* ************************************************************************* */

NamespaceDecl::~NamespaceDecl() = default;

/* ************************************************************************* */

UniquePtr<NamespaceDecl> NamespaceDecl::make(String name, PtrDynamicArray<Decl> decls, SourceRange range)
{
    return makeUnique<NamespaceDecl>(moveValue(name), moveValue(decls), moveValue(range));
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

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

#pragma once

/* ************************************************************************* */

// Shard
#include "shard/utility.hpp"
#include "shard/UniquePtr.hpp"
#include "shard/ViewPtr.hpp"
#include "shard/String.hpp"
#include "shard/StringView.hpp"
#include "shard/DynamicArray.hpp"
#include "shard/ast/utility.hpp"
#include "shard/ast/Type.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

class DeclContext;
class CompoundStmt;
class Expr;

/* ************************************************************************* */

/**
 * @brief Kind of Declaration.
 */
enum class DeclKind
{
    Variable = 1,
    Function = 2,
    Class = 3,
    Named_First = Variable,
    Named_Last = Class
};

/* ************************************************************************* */

/**
 * @brief Base declaration class.
 */
class Decl : public LocationInfo
{

// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param type    Declaration type.
     * @param context Declaration context.
     * @param range   Source range.
     */
    Decl(ViewPtr<DeclContext> context, DeclKind type, SourceRange range) noexcept;


    /**
     * @brief Destructor.
     */
    virtual ~Decl() = 0;


// Public Accessors & Mutators
public:


    /**
     * @brief Returns declaration context.
     * @return Declaration context.
     */
    ViewPtr<DeclContext> getContext() const noexcept
    {
        return m_context;
    }


    /**
     * @brief Returns Declaration type.
     * @return Declaration type.
     */
    DeclKind getKind() const noexcept
    {
        return m_kind;
    }


// Private Data Members
private:

    /// Declaration context.
    ViewPtr<DeclContext> m_context;

    /// Declaration type.
    DeclKind m_kind;

};

/* ************************************************************************* */

/**
 * @brief Helper class for declaration kinds.
 * @tparam KIND Tested declaration kind.
 * @tparam T    Class type.
 */
template<DeclKind KIND, typename T>
struct DeclHelper
    : public TypeHelper<DeclKind, KIND, Decl>
    , public CastHelper<Decl, T>
{
    // Nothing to do
};

/* ************************************************************************* */

/**
 * @brief Helper class for declaration kinds.
 * @tparam KIND1 The first tested declaration kind.
 * @tparam KIND2 The last tested declaration kind.
 * @tparam T     Class type.
 */
template<DeclKind KIND1, DeclKind KIND2, typename T>
struct DeclRangeHelper
    : public TypeRangeHelper<DeclKind, KIND1, KIND2, Decl>
    , public CastHelper<Decl, T>
{
    // Nothing to do
};

/* ************************************************************************* */

/**
 * @brief Base class for all declarations which are named.
 */
class NamedDecl
    : public Decl
    , private DeclRangeHelper<DeclKind::Named_First, DeclKind::Named_Last, NamedDecl>
{

// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param context Declaration context.
     * @param kind    Declaration kind.
     * @param name    Declaration name.
     * @param range   Source range.
     */
    NamedDecl(ViewPtr<DeclContext> context, DeclKind kind, String name, SourceRange range = {}) noexcept;


// Public Accessors & Mutators
public:


    /**
     * @brief Returns declaration name.
     * @return
     */
    StringView getName() const noexcept
    {
        return m_name;
    }


// Public Operations
public:


    using DeclRangeHelper<DeclKind::Named_First, DeclKind::Named_Last, NamedDecl>::is;
    using DeclRangeHelper<DeclKind::Named_First, DeclKind::Named_Last, NamedDecl>::cast;


// Private Data Members
private:

    /// Declaration name.
    String m_name;

};

/* ************************************************************************* */

/**
 * @brief Variable declaration.
 */
class VariableDecl final
    : public NamedDecl
    , private DeclHelper<DeclKind::Variable, VariableDecl>
{

// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param context Declaration context.
     * @param name    Variable name.
     * @param type    Type info.
     * @param init    Initializer expression.
     * @param range   Source range.
     */
    explicit VariableDecl(ViewPtr<DeclContext> context, String name, TypeInfo type, UniquePtr<Expr> init = nullptr, SourceRange range = {}) noexcept;


    /**
     * @brief Destructor.
     */
    ~VariableDecl();


// Public Accessors & Mutators
public:


    /**
     * @brief Return type information.
     * @return Variable type information.
     */
    const TypeInfo& getTypeInfo() const noexcept
    {
        return m_typeInfo;
    }


    /**
     * @brief Return type.
     * @return Variable type.
     */
    ViewPtr<const Type> getType() const noexcept
    {
        return m_typeInfo.getType();
    }


    /**
     * @brief Returns initializer expression.
     * @return Expression.
     */
    ViewPtr<Expr> getInitializer() noexcept
    {
        return m_initializer.get();
    }


    /**
     * @brief Returns initializer expression.
     * @return Expression.
     */
    ViewPtr<const Expr> getInitializer() const noexcept
    {
        return m_initializer.get();
    }


// Public Operations
public:


    using DeclHelper<DeclKind::Variable, VariableDecl>::is;
    using DeclHelper<DeclKind::Variable, VariableDecl>::cast;


// Private Data Members
private:

    /// Type information.
    TypeInfo m_typeInfo;

    /// Initializer expression.
    UniquePtr<Expr> m_initializer;

};

/* ************************************************************************* */

/**
 * @brief Function declaration.
 */
class FunctionDecl final
    : public NamedDecl
    , private DeclHelper<DeclKind::Function, FunctionDecl>
{

// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param context Declaration context.
     * @param name    Function name.
     * @param retType Return type information.
     * @param params  Function parameters.
     * @param body    Function body.
     * @param range   Source range.
     */
    explicit FunctionDecl(ViewPtr<DeclContext> context, String name, TypeInfo retType,
        DynamicArray<UniquePtr<VariableDecl>> params, UniquePtr<CompoundStmt> body, SourceRange range = {}) noexcept;


    /**
     * @brief Destructor.
     */
    ~FunctionDecl();


// Public Accessors & Mutators
public:


    /**
     * @brief Return return type information.
     * @return Return type information.
     */
    const TypeInfo& getRetTypeInfo() const noexcept
    {
        return m_retTypeInfo;
    }


    /**
     * @brief Return return type.
     * @return Return type.
     */
    ViewPtr<const Type> getRetType() const noexcept
    {
        return m_retTypeInfo.getType();
    }


    /**
     * @brief Returns function parameters.
     * @return Expression.
     */
    const DynamicArray<UniquePtr<VariableDecl>>& getParameters() const noexcept
    {
        return m_parameters;
    }


    /**
     * @brief Returns pointer to function body.
     * @return
     */
    ViewPtr<CompoundStmt> getBody() noexcept
    {
        return m_body.get();
    }


    /**
     * @brief Returns pointer to function body.
     * @return
     */
    ViewPtr<const CompoundStmt> getBody() const noexcept
    {
        return m_body.get();
    }


// Public Operations
public:


    using DeclHelper<DeclKind::Function, FunctionDecl>::is;
    using DeclHelper<DeclKind::Function, FunctionDecl>::cast;


// Private Data Members
private:

    /// Return type information.
    TypeInfo m_retTypeInfo;

    /// Parameters.
    DynamicArray<UniquePtr<VariableDecl>> m_parameters;

    /// Function body.
    UniquePtr<CompoundStmt> m_body;

};

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

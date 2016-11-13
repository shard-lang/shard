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
#include "shard/PtrDynamicArray.hpp"
#include "shard/ast/utility.hpp"
#include "shard/ast/Type.hpp"
#include "shard/ast/DeclContext.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

class Expr;
class CompoundStmt;

/* ************************************************************************* */

/**
 * @brief Kind of Declaration.
 */
enum class DeclKind
{
    Variable,
    Function,
    Class,
    //Namespace,
    Named_First = Variable,
    Named_Last  = Class
    //Named_Last  = Namespace
};

/* ************************************************************************* */

/**
 * @brief      Base declaration class.
 */
class Decl : public LocationInfo
{

// Public Ctors & Dtors
public:


    /**
     * @brief Destructor.
     */
    virtual ~Decl() = 0;


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns declaration context.
     *
     * @return     Declaration context.
     */
    ViewPtr<DeclContext> getContext() noexcept
    {
        return m_context;
    }


    /**
     * @brief      Returns declaration context.
     *
     * @return     Declaration context.
     */
    ViewPtr<const DeclContext> getContext() const noexcept
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


// Protected Ctors & Dtors
protected:


    /**
     * @brief      Constructor.
     *
     * @param      context  Declaration context.
     * @param      type     Declaration type.
     * @param      range    Source range.
     */
    explicit Decl(ViewPtr<DeclContext> context, DeclKind type,
        SourceRange range) noexcept;


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
    : public KindTester<DeclKind, KIND, Decl>
    , public KindCaster<Decl, T>
    , public KindMaker<T>
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
    : public KindRangeTester<DeclKind, KIND1, KIND2, Decl>
    , public KindCaster<Decl, T>
    , public KindMaker<T>
{
    // Nothing to do
};

/* ************************************************************************* */

/**
 * @brief      Base class for all declarations which are named: function, class, variable.
 */
class NamedDecl
    : public Decl
    , private DeclRangeHelper<DeclKind::Named_First, DeclKind::Named_Last, NamedDecl>
{


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns declaration name.
     *
     * @return     The declaration name.
     */
    const String& getName() const noexcept
    {
        return m_name;
    }


    /**
     * @brief      Change declaration name.
     *
     * @param      name  New declaration name.
     */
    void setName(String name) noexcept
    {
        m_name = moveValue(name);
    }


// Public Operations
public:


    using DeclRangeHelper<DeclKind::Named_First, DeclKind::Named_Last, NamedDecl>::is;
    using DeclRangeHelper<DeclKind::Named_First, DeclKind::Named_Last, NamedDecl>::cast;


// Protected Ctors & Dtors
protected:


    /**
     * @brief      Constructor.
     *
     * @param      context  The declaration context.
     * @param      kind     Declaration kind.
     * @param      name     Declaration name.
     * @param      range    Source range.
     */
    explicit NamedDecl(ViewPtr<DeclContext> context, DeclKind kind, String name,
        SourceRange range = {}) noexcept;


    // Private Data Members
private:

    /// Declaration name.
    String m_name;
};

/* ************************************************************************* */

/**
 * @brief      Variable declaration.
 *
 * @details    In the source it appears as: `<type> <name>` or `<type> <name> =
 *             <initExpr>`.
 */
class VariableDecl final
    : public NamedDecl
    , private DeclHelper<DeclKind::Variable, VariableDecl>
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      context   The declaration context.
     * @param      type      Type info.
     * @param      name      Variable name.
     * @param      initExpr  Initialization expression.
     * @param      range     Source range.
     */
    explicit VariableDecl(ViewPtr<DeclContext> context, TypeInfo type,
        String name, UniquePtr<Expr> initExpr = nullptr,
        SourceRange range = {}) noexcept;


    /**
     * @brief      Constructor.
     *
     * @param      context   The declaration context.
     * @param      type      Variable type.
     * @param      name      Variable name.
     * @param      initExpr  Initialization expression.
     * @param      range     Source range.
     */
    explicit VariableDecl(ViewPtr<DeclContext> context,
        ViewPtr<const Type> type, String name,
        UniquePtr<Expr> initExpr = nullptr, SourceRange range = {}) noexcept;


    /**
     * @brief      Destructor.
     */
    ~VariableDecl();


// Public Accessors & Mutators
public:


    /**
     * @brief      Return type information.
     *
     * @return     Variable type information.
     */
    const TypeInfo& getTypeInfo() const noexcept
    {
        return m_typeInfo;
    }


    /**
     * @brief      Change type information.
     *
     * @param      info  Variable type information.
     */
    void setTypeInfo(TypeInfo info) noexcept
    {
        m_typeInfo = moveValue(info);
    }


    /**
     * @brief      Return type.
     *
     * @return     Variable type.
     */
    ViewPtr<const Type> getType() const noexcept
    {
        return m_typeInfo.getType();
    }


    /**
     * @brief      Change variable type.
     *
     * @param      type  New variable type.
     */
    void setType(ViewPtr<const Type> type) noexcept
    {
        m_typeInfo.setType(type);
    }


    /**
     * @brief      Returns initialization expression.
     *
     * @return     The initialization expression.
     */
    ViewPtr<const Expr> getInitExpr() const noexcept
    {
        return makeView(m_initExpr);
    }


    /**
     * @brief      Returns initialization expression.
     *
     * @return     The initialization expression.
     */
    ViewPtr<Expr> getInitExpr() noexcept
    {
        return makeView(m_initExpr);
    }


    /**
     * @brief      Change initialization expression.
     *
     * @param      expr  New initialization expression.
     */
    void setInitExpr(UniquePtr<Expr> expr) noexcept;


// Public Operations
public:


    using DeclHelper<DeclKind::Variable, VariableDecl>::is;
    using DeclHelper<DeclKind::Variable, VariableDecl>::cast;
    using DeclHelper<DeclKind::Variable, VariableDecl>::make;


// Private Data Members
private:

    /// Type information.
    TypeInfo m_typeInfo;

    /// Initializer expression.
    UniquePtr<Expr> m_initExpr;
};

/* ************************************************************************* */

/**
 * @brief      Function declaration.
 *
 * @details    In the source it appears as: `<retType> <name> (<params>) <bodyStmt>`.
 */
class FunctionDecl final
    : public NamedDecl
    , private DeclHelper<DeclKind::Function, FunctionDecl>
    , public DeclContext
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      context   The declaration context.
     * @param      retType   Return type information.
     * @param      name      Function name.
     * @param      params    Function parameters.
     * @param      bodyStmt  Function body.
     * @param      range     Source range.
     */
    explicit FunctionDecl(ViewPtr<DeclContext> context, TypeInfo retType,
        String name, PtrDynamicArray<VariableDecl> params,
        UniquePtr<CompoundStmt> bodyStmt, SourceRange range = {}) noexcept;


    /**
     * @brief      Destructor.
     */
    ~FunctionDecl();


// Public Accessors & Mutators
public:


    /**
     * @brief      Return return type information.
     *
     * @return     Return type information.
     */
    TypeInfo& getRetTypeInfo() noexcept
    {
        return m_retTypeInfo;
    }


    /**
     * @brief      Return return type information.
     *
     * @return     Return type information.
     */
    const TypeInfo& getRetTypeInfo() const noexcept
    {
        return m_retTypeInfo;
    }


    /**
     * @brief      Change return type information.
     *
     * @param      info  New return type information.
     */
    void setRetTypeInfo(TypeInfo info) noexcept
    {
        m_retTypeInfo = moveValue(info);
    }


    /**
     * @brief      Return return type.
     *
     * @return     Return type.
     */
    ViewPtr<const Type> getRetType() const noexcept
    {
        return m_retTypeInfo.getType();
    }


    /**
     * @brief      Change return type.
     *
     * @param      type  New return type.
     */
    void setRetType(ViewPtr<const Type> type) noexcept
    {
        SHARD_ASSERT(type);
        m_retTypeInfo.setType(type);
    }


    /**
     * @brief      Returns function parameters.
     *
     * @return     A list of function parameters.
     */
    DynamicArray<ViewPtr<VariableDecl>> getParameters() const noexcept
    {
        return getDeclarations<VariableDecl>();
    }


    /**
     * @brief      Change function parameters.
     *
     * @param      params  The function parameters.
     */
    void setParameters(PtrDynamicArray<VariableDecl> params) noexcept;


    /**
     * @brief      Returns pointer to function body.
     *
     * @return     Body statement.
     */
    ViewPtr<const CompoundStmt> getBodyStmt() const noexcept
    {
        return makeView(m_bodyStmt);
    }


    /**
     * @brief      Returns pointer to function body.
     *
     * @return     Body statement.
     */
    ViewPtr<CompoundStmt> getBodyStmt() noexcept
    {
        return makeView(m_bodyStmt);
    }


    /**
     * @brief      Change function body.
     *
     * @param      stmt  Body statement.
     */
    void setBodyStmt(UniquePtr<CompoundStmt> stmt) noexcept;


// Public Operations
public:


    using DeclHelper<DeclKind::Function, FunctionDecl>::is;
    using DeclHelper<DeclKind::Function, FunctionDecl>::cast;
    using DeclHelper<DeclKind::Function, FunctionDecl>::make;


// Private Data Members
private:

    /// Return type information.
    TypeInfo m_retTypeInfo;

    /// Function body.
    UniquePtr<CompoundStmt> m_bodyStmt;
};

/* ************************************************************************* */

/**
 * @brief      Class declaration.
 *
 * @details    In the source it appears as: `class <name> { <decls> }`.
 */
class ClassDecl final
    : public NamedDecl
    , private DeclHelper<DeclKind::Class, ClassDecl>
    , public DeclContext
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      context  The declaration context.
     * @param      name     Class name.
     * @param      decls    Declarations.
     * @param      range    Source range.
     */
    explicit ClassDecl(ViewPtr<DeclContext> context, String name,
        PtrDynamicArray<Decl> decls = {}, SourceRange range = {}) noexcept;


    /**
     * @brief      Destructor.
     */
    ~ClassDecl();


// Public Operations
public:


    using DeclHelper<DeclKind::Class, ClassDecl>::is;
    using DeclHelper<DeclKind::Class, ClassDecl>::cast;
    using DeclHelper<DeclKind::Class, ClassDecl>::make;

};

/* ************************************************************************* */

/**
 * @brief Namespace declaration.
 */
// class NamespaceDecl final
//     : public NamedDecl
//     , private DeclHelper<DeclKind::Namespace, NamespaceDecl>
//     , public DeclContext
// {

// // Public Ctors & Dtors
// public:


//     /**
//      * @brief Constructor.
//      * @param name     Class name.
//      * @param decls    Declarations.
//      * @param range    Source range.
//      */
//     explicit NamespaceDecl(ViewPtr<DeclContext> context, String name, PtrDynamicArray<Decl> decls = {}, SourceRange range = {}) noexcept;


//     /**
//      * @brief Destructor.
//      */
//     ~NamespaceDecl();


// // Public Operations
// public:


//     using DeclHelper<DeclKind::Namespace, NamespaceDecl>::is;
//     using DeclHelper<DeclKind::Namespace, NamespaceDecl>::cast;

// };

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

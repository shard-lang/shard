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
#include "shard/Assert.hpp"
#include "shard/utility.hpp"
#include "shard/UniquePtr.hpp"
#include "shard/ViewPtr.hpp"
#include "shard/String.hpp"
#include "shard/PtrDynamicArray.hpp"
#include "shard/ast/Node.hpp"
#include "shard/ast/Type.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

class Expr;
class CompoundStmt;

/* ************************************************************************* */

/**
 * @brief      Kind of Declaration.
 */
enum class DeclKind
{
    Variable,
    Function,
    Class,
    Namespace,
};

/* ************************************************************************* */

/**
 * @brief      Declaration access specifier.
 */
enum class DeclAccessSpecifier
{
    /// Access is not specified and use rules defined by context. It's also
    /// value for declaration where access specifier cannot be used
    /// (like local variables).
    Default,

    /// Declaration is accessible by anyone.
    Public,

    /// Declaration is accessible only under by some rules.
    Protected,

    /// Declaration is not accessible outside scope within compilation unit.
    /// If some other compilation unit define same scope the declaration is
    /// not accessible from that unit.
    Private
};

/* ************************************************************************* */

/**
 * @brief      Base declaration class.
 *
 * @details    This abstract class serves as base class for all declaration
 *             types as variable, function and class declaration. It's not
 *             possible to create an object of this class directly (pure virtual
 *             destructor, protected constructor), the only way is to create an
 *             object of child class. Type of the declaration can be obtained by
 *             calling `getKind`. All declarations are named so can be
 *             identified later. The name should represents declaration scope
 *             naming scheme not FQN scheme.
 */
class Decl : public Node
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Destructor.
     */
    virtual ~Decl() = 0;


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns the declaration kind.
     *
     * @details    Use for specific declaration type identification.
     *
     * @return     The declaration kind.
     */
    DeclKind getKind() const noexcept
    {
        return m_kind;
    }


    /**
     * @brief      Returns the declaration name in local scope naming scheme.
     *
     * @return     The declaration name.
     */
    const String& getName() const noexcept
    {
        return m_name;
    }


    /**
     * @brief      Change the declaration name.
     *
     * @return     The declaration name in local scope naming scheme.
     */
    void setName(String name);


    /**
     * @brief      Returns the declaration access specifier.
     *
     * @return     The access specifier.
     */
    DeclAccessSpecifier getAccessSpecifier() const noexcept
    {
        return m_accessSpecifier;
    }


    /**
     * @brief      Change the declaration access specifier.
     *
     * @param      spec  The access specifier.
     */
    void setAccessSpecifier(DeclAccessSpecifier spec) noexcept
    {
        m_accessSpecifier = spec;
    }


// Public Operations
public:


    /**
     * @brief      Test if declaration match required kind.
     *
     * @tparam     DeclType  Declaration type.
     *
     * @return     Returns `true` if this is `DeclType`, `false` otherwise.
     */
    template<typename DeclType>
    bool is() const noexcept
    {
        return getKind() == DeclType::Kind;
    }


    /**
     * @brief      Cast this to required declaration type.
     *
     * @tparam     DeclType  Declaration type.
     *
     * @return     Reference to required declaration type.
     */
    template<typename DeclType>
    DeclType& cast() noexcept
    {
        SHARD_ASSERT(is<DeclType>());
        return static_cast<DeclType&>(*this);
    }


    /**
     * @brief      Cast this to required declaration type.
     *
     * @tparam     DeclType  Declaration type.
     *
     * @return     Reference to required declaration type.
     */
    template<typename DeclType>
    const DeclType& cast() const noexcept
    {
        SHARD_ASSERT(is<DeclType>());
        return static_cast<const DeclType&>(*this);
    }


// Protected Ctors & Dtors
protected:


    /**
     * @brief      Constructor.
     *
     * @param      kind   The declaration kind.
     * @param      name   The declaration name in local scope naming scheme.
     * @param      range  The declaration location within the source.
     */
    explicit Decl(DeclKind kind, String name, SourceRange range);


    // Private Data Members
private:

    /// Declaration kind.
    DeclKind m_kind;

    /// Declaration name.
    String m_name;

    /// Declaration access specifier
    DeclAccessSpecifier m_accessSpecifier = DeclAccessSpecifier::Default;
};

/* ************************************************************************* */

/**
 * @brief      Variable declaration.
 *
 * @details    In the source it appears as: `<type> <name>` or `<type> <name> =
 *             <initExpr>`.
 */
class VariableDecl final : public Decl
{

// Public Constants
public:


    /// Declaration kind
    static constexpr DeclKind Kind = DeclKind::Variable;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      type      The variable type.
     * @param      name      The variable name.
     * @param      initExpr  The optional initialization expression.
     * @param      range     The declaration location within the source.
     */
    explicit VariableDecl(Type type, String name, UniquePtr<Expr> initExpr = nullptr, SourceRange range = {});


    /**
     * @brief      Destructor.
     */
    ~VariableDecl();


// Public Accessors & Mutators
public:


    /**
     * @brief      Return the variable type.
     *
     * @return     The variable type.
     */
    const Type& getType() const noexcept
    {
        return m_type;
    }


    /**
     * @brief      Change the variable type.
     *
     * @param      type  The variable type.
     */
    void setType(Type type);


    /**
     * @brief      Returns the initialization expression.
     *
     * @return     The initialization expression.
     */
    ViewPtr<const Expr> getInitExpr() const noexcept
    {
        return makeView(m_initExpr);
    }


    /**
     * @brief      Returns the initialization expression.
     *
     * @return     The initialization expression.
     */
    ViewPtr<Expr> getInitExpr() noexcept
    {
        return makeView(m_initExpr);
    }


    /**
     * @brief      Change the initialization expression.
     *
     * @param      expr  The initialization expression.
     */
    void setInitExpr(UniquePtr<Expr> expr);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      type      The variable type.
     * @param      name      The variable name.
     * @param      initExpr  The optional initialization expression.
     * @param      range     The declaration location within the source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<VariableDecl> make(Type type, String name, UniquePtr<Expr> initExpr = nullptr, SourceRange range = {});


// Private Data Members
private:

    /// Variable type.
    Type m_type;

    /// Initializer expression.
    UniquePtr<Expr> m_initExpr;
};

/* ************************************************************************* */

/**
 * @brief      Function declaration.
 *
 * @details    In the source it appears as: `<retType> <name> (<params>) <bodyStmt>`.
 */
class FunctionDecl final : public Decl
{

// Public Constants
public:


    /// Declaration kind
    static constexpr DeclKind Kind = DeclKind::Function;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      retType   The function return type.
     * @param      name      The function name.
     * @param      params    The function parameters.
     * @param      bodyStmt  The function body.
     * @param      range     The declaration location within the source.
     */
    explicit FunctionDecl(Type retType, String name, UniquePtr<CompoundStmt> bodyStmt,
        PtrDynamicArray<VariableDecl> params = {}, SourceRange range = {});


    /**
     * @brief      Destructor.
     */
    ~FunctionDecl();


// Public Accessors & Mutators
public:


    /**
     * @brief      Return the function return type.
     *
     * @return     The function return type.
     */
    const Type& getRetType() const noexcept
    {
        return m_retType;
    }


    /**
     * @brief      Change the return type.
     *
     * @param      type  The return type.
     */
    void setRetType(Type type);


    /**
     * @brief      Returns the function parameters.
     *
     * @return     A list of function parameters.
     */
    const PtrDynamicArray<VariableDecl>& getParameters() const noexcept
    {
        return m_parameters;
    }


    /**
     * @brief      Change the function parameters.
     *
     * @param      params  The function parameters.
     */
    void setParameters(PtrDynamicArray<VariableDecl> params);


    /**
     * @brief      Returns the function body statement.
     *
     * @return     The function body compound statement.
     */
    ViewPtr<const CompoundStmt> getBodyStmt() const noexcept
    {
        return makeView(m_bodyStmt);
    }


    /**
     * @brief      Returns the function body statement.
     *
     * @return     The function body compound statement.
     */
    ViewPtr<CompoundStmt> getBodyStmt() noexcept
    {
        return makeView(m_bodyStmt);
    }


    /**
     * @brief      Change the function body.
     *
     * @param      stmt  The function body compound statement.
     */
    void setBodyStmt(UniquePtr<CompoundStmt> stmt);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      retType   The function return type.
     * @param      name      The function name.
     * @param      bodyStmt  The function body.
     * @param      params    The function parameters.
     * @param      range     The declaration location within the source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<FunctionDecl> make(Type retType, String name, UniquePtr<CompoundStmt> bodyStmt,
        PtrDynamicArray<VariableDecl> params = {}, SourceRange range = {});


// Private Data Members
private:

    /// Return type.
    Type m_retType;

    /// Function parameters.
    PtrDynamicArray<VariableDecl> m_parameters;

    /// Function body.
    UniquePtr<CompoundStmt> m_bodyStmt;
};

/* ************************************************************************* */

/**
 * @brief      Base class for declaration which are compound of other
 *             declarations (class, namespace, ...).
 */
class CompoundDecl : public Decl
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Destructor.
     */
    ~CompoundDecl();


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns declarations.
     *
     * @return     The declarations.
     */
    const PtrDynamicArray<Decl>& getDecls() const noexcept
    {
        return m_declarations;
    }


    /**
     * @brief      Set declarations.
     *
     * @param      decls  The declarations.
     */
    void setDecls(PtrDynamicArray<Decl> decls);


    /**
     * @brief      Add declaration.
     *
     * @param      decl  The declaration to add.
     */
    void addDecl(UniquePtr<Decl> decl);


// Protected Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      kind   The declaration kind.
     * @param      name   The declaration name in local scope naming scheme.
     * @param      decls  The declarations.
     * @param      range  The declaration location within the source.
     */
    explicit CompoundDecl(DeclKind kind, String name, PtrDynamicArray<Decl> decls, SourceRange range);


// Private Data Members
private:

    /// Declarations
    PtrDynamicArray<Decl> m_declarations;

};

/* ************************************************************************* */

/**
 * @brief      Class declaration.
 *
 * @details    In the source it appears as: `class <name> { <decls> }`.
 */
class ClassDecl final : public CompoundDecl
{

// Public Constants
public:


    /// Declaration kind
    static constexpr DeclKind Kind = DeclKind::Class;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      name   The class name.
     * @param      decls  The list of declarations.
     * @param      range  The declaration location within the source.
     */
    explicit ClassDecl(String name, PtrDynamicArray<Decl> decls = {}, SourceRange range = {});


    /**
     * @brief      Destructor.
     */
    ~ClassDecl();


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      name   The class name.
     * @param      decls  The list of declarations.
     * @param      range  The declaration location within the source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<ClassDecl> make(String name, PtrDynamicArray<Decl> decls = {}, SourceRange range = {});

};

/* ************************************************************************* */

/**
 * @brief      Namespace declaration.
 */
class NamespaceDecl final : public CompoundDecl
{

// Public Constants
public:


    /// Declaration kind
    static constexpr DeclKind Kind = DeclKind::Namespace;


// Public Ctors & Dtors
public:


   /**
     * @brief      Constructor.
     *
     * @param      name   The class name.
     * @param      decls  The list of declarations.
     * @param      range  The declaration location within the source.
     */
   explicit NamespaceDecl(String name, PtrDynamicArray<Decl> decls = {}, SourceRange range = {});


   /**
    * @brief      Destructor.
    */
    ~NamespaceDecl();


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      name   The class name.
     * @param      decls  The list of declarations.
     * @param      range  The declaration location within the source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<NamespaceDecl> make(String name, PtrDynamicArray<Decl> decls = {}, SourceRange range = {});

};

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

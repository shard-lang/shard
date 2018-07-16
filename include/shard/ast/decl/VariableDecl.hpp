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
#include "shard/UniquePtr.hpp"
#include "shard/ViewPtr.hpp"
#include "shard/String.hpp"
#include "shard/ast/Type.hpp"
#include "shard/ast/Decl.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

class Expr;

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
    const Type& getType() const noexcept;


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
    ViewPtr<const Expr> getInitExpr() const noexcept;


    /**
     * @brief      Returns the initialization expression.
     *
     * @return     The initialization expression.
     */
    ViewPtr<Expr> getInitExpr() noexcept;


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
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

inline const Type& VariableDecl::getType() const noexcept
{
    return m_type;
}

/* ************************************************************************* */

inline ViewPtr<const Expr> VariableDecl::getInitExpr() const noexcept
{
    return makeView(m_initExpr);
}

/* ************************************************************************* */

inline ViewPtr<Expr> VariableDecl::getInitExpr() noexcept
{
    return makeView(m_initExpr);
}

/* ************************************************************************* */

}

/* ************************************************************************* */

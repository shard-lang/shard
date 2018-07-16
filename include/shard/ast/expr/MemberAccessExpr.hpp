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
#include "shard/String.hpp"
#include "shard/UniquePtr.hpp"
#include "shard/ViewPtr.hpp"
#include "shard/ast/Expr.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

/**
 * @brief      Member access expression.
 *
 * @details    In the source it represents following expression: `<expr>.<name>`.
 */
class MemberAccessExpr final : public Expr
{

// Public Constants
public:


    /// Expression kind
    static constexpr ExprKind Kind = ExprKind::MemberAccess;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      expr   Evaluation context expression.
     * @param      name   Identifier name.
     * @param      range  Location in source.
     */
    explicit MemberAccessExpr(UniquePtr<Expr> expr, String name, SourceRange range = {});


    /**
     * @brief      Destructor.
     */
    ~MemberAccessExpr();


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns evaluation context expression.
     *
     * @return     The evaluation context expression.
     */
    ViewPtr<const Expr> getExpr() const noexcept;


    /**
     * @brief      Returns evaluation context expression.
     *
     * @return     The evaluation context expression.
     */
    ViewPtr<Expr> getExpr() noexcept;


    /**
     * @brief      Change evaluation context expression.
     *
     * @param      expr  The new expression.
     */
    void setExpr(UniquePtr<Expr> expr);


    /**
     * @brief      Returns identifier name.
     *
     * @return     Identifier name.
     */
    const String& getName() const noexcept;

    /**
     * @brief      Change identifier name.
     *
     * @param      name  The new identifier name.
     */
    void setName(String name);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      expr   Evaluation context expression.
     * @param      name   Identifier name.
     * @param      range  Location in source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<MemberAccessExpr> make(UniquePtr<Expr> expr, String name, SourceRange range = {});


// Private Data Members
private:

    /// Left expression.
    UniquePtr<Expr> m_expr;

    /// Identifier name.
    String m_name;

};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

inline ViewPtr<const Expr> MemberAccessExpr::getExpr() const noexcept
{
    return makeView(m_expr);
}

/* ************************************************************************* */

inline ViewPtr<Expr> MemberAccessExpr::getExpr() noexcept
{
    return makeView(m_expr);
}

/* ************************************************************************* */

inline const String& MemberAccessExpr::getName() const noexcept
{
    return m_name;
}

/* ************************************************************************* */

}

/* ************************************************************************* */

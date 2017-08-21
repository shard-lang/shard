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
#include "shard/ast/Expr.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

/**
 * @brief      Parenthesis expression.
 *
 * @details    Represents a parenthesis aroud another expression: `(<expr>)`.
 */
class ParenExpr final : public Expr
{

// Public Constants
public:


    /// Expression kind
    static constexpr ExprKind Kind = ExprKind::Paren;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      expr   Inner expression.
     * @param      range  Location in source.
     */
    explicit ParenExpr(UniquePtr<Expr> expr, SourceRange range = {});


    /**
     * @brief      Destructor.
     */
    ~ParenExpr();


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns inner expression.
     *
     * @return     Inner expression.
     */
    ViewPtr<const Expr> getExpr() const noexcept;


    /**
     * @brief      Returns inner expression.
     *
     * @return     Inner expression.
     */
    ViewPtr<Expr> getExpr() noexcept;


    /**
     * @brief      Change expression.
     *
     * @param      expr  The new expression.
     */
    void setExpr(UniquePtr<Expr> expr);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      expr   Inner expression.
     * @param      range  Location in source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<ParenExpr> make(UniquePtr<Expr> expr, SourceRange range = {});


// Private Data Members
private:

    /// Inner expression.
    UniquePtr<Expr> m_expr;

};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

inline ViewPtr<const Expr> ParenExpr::getExpr() const noexcept
{
    return makeView(m_expr);
}

/* ************************************************************************* */

inline ViewPtr<Expr> ParenExpr::getExpr() noexcept
{
    return makeView(m_expr);
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

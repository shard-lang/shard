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

namespace shard::ast {

/* ************************************************************************* */

/**
 * @brief      Unary expression.
 *
 * @details    This expression is used for single prefix or postfix expressions
 *             to which an operation is applied like negation, increment or
 *             decrement. In the source it can be identified as: `<op><expr>` or
 *             `<expr><op>`.
 */
class UnaryExpr final : public Expr
{

// Public Constants
public:


    /// Expression kind
    static constexpr ExprKind Kind = ExprKind::Unary;


// Public Enums
public:


    /**
     * @brief      Unary operation kind.
     */
    enum class OpKind
    {
        PostInc,
        PostDec,
        PreInc,
        PreDec,
        Plus,
        Minus,
        Not
    };


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      op     Operation kind.
     * @param      expr   Operand expression.
     * @param      range  Location in source.
     */
    explicit UnaryExpr(OpKind op, UniquePtr<Expr> expr, SourceRange range = {});


    /**
     * @brief      Destructor.
     */
    ~UnaryExpr();


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns operation kind.
     *
     * @return     Operation kind.
     */
    OpKind getOpKind() const noexcept;


    /**
     * @brief      Change operation kind.
     *
     * @param      op    The new operation kind.
     */
    void setOpKind(OpKind op);


    /**
     * @brief      Returns subexpression.
     *
     * @return     Subexpression.
     */
    ViewPtr<const Expr> getExpr() const noexcept;


    /**
     * @brief      Returns subexpression.
     *
     * @return     Subexpression.
     */
    ViewPtr<Expr> getExpr() noexcept;


    /**
     * @brief      Change subexpression.
     *
     * @param      expr  The new subexpression.
     */
    void setExpr(UniquePtr<Expr> expr);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      op     Operation kind.
     * @param      expr   Operand expression.
     * @param      range  Location in source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<UnaryExpr> make(OpKind op, UniquePtr<Expr> expr, SourceRange range = {});


// Private Data Members
private:

    /// OpKind.
    OpKind m_operator;

    /// Operand.
    UniquePtr<Expr> m_expr;
};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

inline UnaryExpr::OpKind UnaryExpr::getOpKind() const noexcept
{
    return m_operator;
}

/* ************************************************************************* */

inline ViewPtr<const Expr> UnaryExpr::getExpr() const noexcept
{
    return makeView(m_expr);
}

/* ************************************************************************* */

inline ViewPtr<Expr> UnaryExpr::getExpr() noexcept
{
    return makeView(m_expr);
}

/* ************************************************************************* */

}

/* ************************************************************************* */

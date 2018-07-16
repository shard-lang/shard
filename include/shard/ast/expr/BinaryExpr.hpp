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
 * @brief      Binary expression.
 *
 * @details    This expression is used for expressions where an operation is
 *             applied to two expressions like addition, subtraction and
 *             relation. In the source it can be identified as:
 *             `<lhs><op><rhs>`.
 */
class BinaryExpr final : public Expr
{

// Public Constants
public:


    /// Expression kind
    static constexpr ExprKind Kind = ExprKind::Binary;


// Public Enums
public:


    /**
     * @brief      Binary expression operation kind.
     */
    enum class OpKind
    {
        //  Equality operators
        EQ,
        NE,

        // Relational operators
        LT,
        LE,
        GT,
        GE,

        // Additive operators
        Add,
        Sub,

        // Multiplicative operators
        Mul,
        Div,
        Rem,

        // Assignment operators
        Assign,
        MulAssign,
        DivAssign,
        RemAssign,
        AddAssign,
        SubAssign
    };


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      op     Operation kind.
     * @param      lhs    Left operand expression.
     * @param      rhs    Right operand expression.
     * @param      range  Location in source.
     */
    explicit BinaryExpr(OpKind op, UniquePtr<Expr> lhs, UniquePtr<Expr> rhs, SourceRange range = {});


    /**
     * @brief      Destructor.
     */
    ~BinaryExpr();


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
     * @brief      Returns LHS expression.
     *
     * @return     LHS expression.
     */
    ViewPtr<const Expr> getLhs() const noexcept;


    /**
     * @brief      Returns LHS expression.
     *
     * @return     LHS expression.
     */
    ViewPtr<Expr> getLhs() noexcept;


    /**
     * @brief      Change LHS expression.
     *
     * @param      lhs   The LHS expression.
     */
    void setLhs(UniquePtr<Expr> lhs);


    /**
     * @brief      Returns RHS expression.
     *
     * @return     RHS expression.
     */
    ViewPtr<const Expr> getRhs() const noexcept;


    /**
     * @brief      Returns RHS expression.
     *
     * @return     RHS expression.
     */
    ViewPtr<Expr> getRhs() noexcept;


    /**
     * @brief      Change RHS expression.
     *
     * @param      rhs   The RHS expression.
     */
    void setRhs(UniquePtr<Expr> rhs);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      op     Operation kind.
     * @param      lhs    Left operand expression.
     * @param      rhs    Right operand expression.
     * @param      range  Location in source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<BinaryExpr> make(OpKind op, UniquePtr<Expr> lhs, UniquePtr<Expr> rhs, SourceRange range = {});


// Private Data Members
private:

    /// Operation kind.
    OpKind m_operator;

    /// LHS expression.
    UniquePtr<Expr> m_lhs;

    /// RHS expression.
    UniquePtr<Expr> m_rhs;
};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

inline BinaryExpr::OpKind BinaryExpr::getOpKind() const noexcept
{
    return m_operator;
}

/* ************************************************************************* */

inline ViewPtr<const Expr> BinaryExpr::getLhs() const noexcept
{
    return makeView(m_lhs);
}

/* ************************************************************************* */

inline ViewPtr<Expr> BinaryExpr::getLhs() noexcept
{
    return makeView(m_lhs);
}

/* ************************************************************************* */

inline ViewPtr<const Expr> BinaryExpr::getRhs() const noexcept
{
    return makeView(m_rhs);
}

/* ************************************************************************* */

inline ViewPtr<Expr> BinaryExpr::getRhs() noexcept
{
    return makeView(m_rhs);
}

/* ************************************************************************* */

}

/* ************************************************************************* */

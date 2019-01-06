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
#include "shard/ast/utility.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

/**
 * @brief      Binary expression operation kind.
 */
enum class BinaryOpKind
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

/* ************************************************************************* */

/**
 * @brief      Binary expression.
 *
 * @details    This expression is used for expressions where an operation is
 *             applied to two expressions like addition, subtraction and
 *             relation. In the source it can be identified as:
 *             `<lhs><op><rhs>`.
 */
class BinaryExpr final
    : public Expr,
      public PtrBuilder<BinaryExpr, BinaryOpKind, ExprPtr, ExprPtr>
{

public:
    // Types

    /// Operation kind.
    using OpKind[[deprecated]] = BinaryOpKind;

public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      op     Operation kind.
     * @param      lhs    Left operand expression.
     * @param      rhs    Right operand expression.
     * @param      range  Location in source.
     */
    explicit BinaryExpr(
        BinaryOpKind op,
        ExprPtr lhs,
        ExprPtr rhs,
        SourceRange range = {})
        : Expr(range)
        , m_operator(op)
        , m_lhs(std::move(lhs))
        , m_rhs(std::move(rhs))
    {
        // Nothing to do
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns the operator.
     *
     * @return     The operator.
     */
    BinaryOpKind op() const noexcept
    {
        return m_operator;
    }

    /**
     * @brief      Change the operator.
     *
     * @param      op    The new operator.
     */
    void setOp(BinaryOpKind op) noexcept
    {
        m_operator = op;
    }

    /**
     * @brief      Returns LHS expression.
     *
     * @return     The LHS expression.
     */
    const ExprPtr& lhs() const noexcept
    {
        return m_lhs;
    }

    /**
     * @brief      Returns LHS expression.
     *
     * @return     The LHS expression.
     */
    ExprPtr& lhs() noexcept
    {
        return m_lhs;
    }

    /**
     * @brief      Returns the inner expression.
     *
     * @tparam     EXPR  The required expression type.
     *
     * @return     The inner expression.
     *
     * @pre        `lhs()->is<EXPR>()`
     */
    template<typename EXPR>
    const EXPR& lhs() const noexcept
    {
        return m_lhs->cast<EXPR>();
    }

    /**
     * @brief      Returns the inner expression.
     *
     * @tparam     EXPR  The required expression type.
     *
     * @return     The inner expression.
     *
     * @pre        `lhs()->is<EXPR>()`
     */
    template<typename EXPR>
    EXPR& lhs() noexcept
    {
        return m_lhs->cast<EXPR>();
    }

    /**
     * @brief      Change LHS expression.
     *
     * @param      lhs   The LHS expression.
     */
    void setLhs(ExprPtr lhs)
    {
        SHARD_ASSERT(lhs);
        m_lhs = std::move(lhs);
    }

    /**
     * @brief      Returns RHS expression.
     *
     * @return     The RHS expression.
     */
    const ExprPtr& rhs() const noexcept
    {
        return m_rhs;
    }

    /**
     * @brief      Returns RHS expression.
     *
     * @return     The RHS expression.
     */
    ExprPtr& rhs() noexcept
    {
        return m_rhs;
    }

    /**
     * @brief      Returns the inner expression.
     *
     * @tparam     EXPR  The required expression type.
     *
     * @return     The inner expression.
     *
     * @pre        `rhs()->is<EXPR>()`
     */
    template<typename EXPR>
    const EXPR& rhs() const noexcept
    {
        return m_rhs->cast<EXPR>();
    }

    /**
     * @brief      Returns the inner expression.
     *
     * @tparam     EXPR  The required expression type.
     *
     * @return     The inner expression.
     *
     * @pre        `rhs()->is<EXPR>()`
     */
    template<typename EXPR>
    EXPR& rhs() noexcept
    {
        return m_rhs->cast<EXPR>();
    }

    /**
     * @brief      Change RHS expression.
     *
     * @param      rhs   The RHS expression.
     */
    void setRhs(ExprPtr rhs)
    {
        SHARD_ASSERT(rhs);
        m_rhs = std::move(rhs);
    }

private:
    // Data Members

    /// The operator.
    BinaryOpKind m_operator;

    /// LHS expression.
    ExprPtr m_lhs;

    /// RHS expression.
    ExprPtr m_rhs;
};

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

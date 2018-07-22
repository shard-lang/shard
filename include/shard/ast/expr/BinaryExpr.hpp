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
    // Enums

    /**
     * @brief      Binary expression operation kind.
     */
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
        : Expr(ExprKind::Binary, range)
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
     * @brief      Returns operation kind.
     *
     * @return     Operation kind.
     */
    [[deprecated]] BinaryOpKind getOpKind() const noexcept
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
     * @brief      Change operation kind.
     *
     * @param      op    The new operation kind.
     */
    [[deprecated]] void setOpKind(BinaryOpKind op) noexcept
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
     * @tparam     ExprType  The required expression type.
     *
     * @return     The inner expression.
     *
     * @pre        `lhs()->is<ExprType>()`
     */
    template<typename ExprType>
    const ExprType& lhs() const noexcept
    {
        return m_lhs->cast<ExprType>();
    }

    /**
     * @brief      Returns the inner expression.
     *
     * @tparam     ExprType  The required expression type.
     *
     * @return     The inner expression.
     *
     * @pre        `lhs()->is<ExprType>()`
     */
    template<typename ExprType>
    ExprType& lhs() noexcept
    {
        return m_lhs->cast<ExprType>();
    }

    /**
     * @brief      Returns LHS expression.
     *
     * @return     LHS expression.
     */
    [[deprecated]] ViewPtr<const Expr> getLhs() const noexcept
    {
        return makeView(m_lhs);
    }

    /**
     * @brief      Returns LHS expression.
     *
     * @return     LHS expression.
     */
    [[deprecated]] ViewPtr<Expr> getLhs() noexcept
    {
        return makeView(m_lhs);
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
     * @return     RHS expression.
     */
    [[deprecated]] ViewPtr<const Expr> getRhs() const noexcept
    {
        return makeView(m_rhs);
    }

    /**
     * @brief      Returns RHS expression.
     *
     * @return     RHS expression.
     */
    [[deprecated]] ViewPtr<Expr> getRhs() noexcept
    {
        return makeView(m_rhs);
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
     * @tparam     ExprType  The required expression type.
     *
     * @return     The inner expression.
     *
     * @pre        `rhs()->is<ExprType>()`
     */
    template<typename ExprType>
    const ExprType& rhs() const noexcept
    {
        return m_rhs->cast<ExprType>();
    }

    /**
     * @brief      Returns the inner expression.
     *
     * @tparam     ExprType  The required expression type.
     *
     * @return     The inner expression.
     *
     * @pre        `rhs()->is<ExprType>()`
     */
    template<typename ExprType>
    ExprType& rhs() noexcept
    {
        return m_rhs->cast<ExprType>();
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

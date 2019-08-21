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
#include "shard/String.hpp"
#include "shard/ViewPtr.hpp"
#include "shard/ast/Expr.hpp"
#include "shard/ast/utility.hpp"

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
class UnaryExpr : public Expr
{

public:
    // Accessors & Mutators

    /**
     * @brief      Returns the operator.
     *
     * @return     The operator.
     */
    const String& op() const noexcept
    {
        return m_operator;
    }

    /**
     * @brief      Change operator.
     *
     * @param      op    The new operator.
     */
    void setOp(String op) noexcept
    {
        m_operator = std::move(op);
    }

    /**
     * @brief      Returns the inner expression.
     *
     * @return     The inner expression.
     */
    const ExprPtr& expr() const noexcept
    {
        return m_expr;
    }

    /**
     * @brief      Returns the inner expression.
     *
     * @return     The inner expression.
     */
    ExprPtr& expr() noexcept
    {
        return m_expr;
    }

    /**
     * @brief      Returns the inner expression.
     *
     * @tparam     EXPR  The required expression type.
     *
     * @return     The inner expression.
     *
     * @pre        `expr()->is<EXPR>()`
     */
    template<typename EXPR>
    const EXPR& expr() const noexcept
    {
        return m_expr->cast<EXPR>();
    }

    /**
     * @brief      Returns the inner expression.
     *
     * @tparam     EXPR  The required expression type.
     *
     * @return     The inner expression.
     *
     * @pre        `expr()->is<EXPR>()`
     */
    template<typename EXPR>
    EXPR& expr() noexcept
    {
        return m_expr->cast<EXPR>();
    }

    /**
     * @brief      Change subexpression.
     *
     * @param      expr  The new subexpression.
     */
    void setExpr(ExprPtr expr)
    {
        SHARD_ASSERT(expr);
        m_expr = std::move(expr);
    }

public:
    // Operations

    /**
     * @brief      Dump declaration to stream.
     *
     * @param      context  The context.
     */
    void dump(const DumpContext& context) const override;

protected:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      op     Operation kind.
     * @param      expr   Operand expression.
     * @param      range  Location in source.
     */
    explicit UnaryExpr(String op, ExprPtr expr, SourceRange range = {})
        : Expr(range)
        , m_operator(std::move(op))
        , m_expr(std::move(expr))
    {
        // Nothing to do
    }

private:
    // Data Members

    /// OpKind.
    String m_operator;

    /// Operand.
    ExprPtr m_expr;
};

/* ************************************************************************* */

/**
 * @brief      Prefix unary expression.
 */
class PrefixUnaryExpr final
    : public UnaryExpr,
      public PtrBuilder<PrefixUnaryExpr, String, ExprPtr>
{

public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      op     Operation kind.
     * @param      expr   Operand expression.
     * @param      range  Location in source.
     */
    explicit PrefixUnaryExpr(String op, ExprPtr expr, SourceRange range = {})
        : UnaryExpr(std::move(op), std::move(expr), range)
    {
        // Nothing to do
    }
};

/* ************************************************************************* */

/**
 * @brief      Postfix unary expression.
 */
class PostfixUnaryExpr final
    : public UnaryExpr,
      public PtrBuilder<PrefixUnaryExpr, ExprPtr, String>
{

public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      expr   Operand expression.
     * @param      op     Operation kind.
     * @param      range  Location in source.
     */
    explicit PostfixUnaryExpr(ExprPtr expr, String op, SourceRange range = {})
        : UnaryExpr(std::move(op), std::move(expr), range)
    {
        // Nothing to do
    }
};

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

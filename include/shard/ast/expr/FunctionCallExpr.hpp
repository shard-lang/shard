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
#include "shard/ast/Expr.hpp"
#include "shard/ast/utility.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

/**
 * @brief      Function call expression.
 *
 * @details    In the source it represents following expression:
 *             `<expr>(<args>)`.
 */
class FunctionCallExpr final
    : public Expr,
      public PtrBuilder<FunctionCallExpr, ExprPtr, ExprPtrVector>
{
public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      expr   Callee expression.
     * @param      args   Call arguments.
     * @param      range  Location in source.
     */
    explicit FunctionCallExpr(
        ExprPtr expr,
        ExprPtrVector args = {},
        SourceRange range  = {})
        : Expr(range)
        , m_expr(std::move(expr))
        , m_arguments(std::move(args))
    {
        SHARD_ASSERT(m_expr);
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns callee expression.
     *
     * @return     The callee expression.
     */
    const ExprPtr& expr() const noexcept
    {
        return m_expr;
    }

    /**
     * @brief      Returns callee expression.
     *
     * @return     The callee expression.
     */
    ExprPtr& expr() noexcept
    {
        return m_expr;
    }

    /**
     * @brief      Returns the callee expression.
     *
     * @tparam     EXPR  The required expression type.
     *
     * @return     The callee expression.
     *
     * @pre        `expr()->is<EXPR>()`
     */
    template<typename EXPR>
    const EXPR& expr() const noexcept
    {
        return m_expr->cast<EXPR>();
    }

    /**
     * @brief      Returns the callee expression.
     *
     * @tparam     EXPR  The required expression type.
     *
     * @return     The callee expression.
     *
     * @pre        `expr()->is<EXPR>()`
     */
    template<typename EXPR>
    EXPR& expr() noexcept
    {
        return m_expr->cast<EXPR>();
    }

    /**
     * @brief      Change expression.
     *
     * @param      expr  The new expression.
     */
    void setExpr(ExprPtr expr) noexcept
    {
        SHARD_ASSERT(expr);
        m_expr = std::move(expr);
    }

    /**
     * @brief      Returns call arguments.
     *
     * @return     The call arguments.
     */
    const ExprPtrVector& args() const noexcept
    {
        return m_arguments;
    }

    /**
     * @brief      Returns number of arguments.
     *
     * @return     The number of arguments.
     */
    size_t argsCount() const noexcept
    {
        return m_arguments.size();
    }

    /**
     * @brief      Returns call argument.
     *
     * @param      pos   The argument position.
     *
     * @return     The call arguments.
     *
     * @pre        `pos < argsCount()`.
     */
    const ExprPtr& arg(size_t pos) const noexcept
    {
        return m_arguments[pos];
    }

    /**
     * @brief      Returns call argument.
     *
     * @param      pos   The argument position.
     *
     * @return     The call arguments.
     *
     * @pre        `pos < args().size()`.
     */
    ExprPtr& arg(size_t pos) noexcept
    {
        return m_arguments[pos];
    }

    /**
     * @brief      Returns call argument.
     *
     * @param      pos   The argument position.
     *
     * @return     The call arguments.
     *
     * @pre        `pos < argsCount()`.
     */
    template<typename EXPR>
    const EXPR& arg(size_t pos) const noexcept
    {
        return arg(pos)->cast<EXPR>();
    }

    /**
     * @brief      Returns call argument.
     *
     * @param      pos   The argument position.
     *
     * @return     The call arguments.
     *
     * @pre        `pos < args().size()`.
     */
    template<typename EXPR>
    EXPR& arg(size_t pos) noexcept
    {
        return arg(pos)->cast<EXPR>();
    }

    /**
     * @brief      Returns call arguments.
     *
     * @return     The call arguments.
     */
    const ExprPtrVector& arguments() const noexcept
    {
        return m_arguments;
    }

    /**
     * @brief      Change call arguments.
     *
     * @param      args  The call arguments.
     */
    void setArguments(ExprPtrVector args) noexcept
    {
        m_arguments = std::move(args);
    }

private:
    // Data Members

    /// Callee expression.
    ExprPtr m_expr;

    /// Call arguments.
    ExprPtrVector m_arguments;
};

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

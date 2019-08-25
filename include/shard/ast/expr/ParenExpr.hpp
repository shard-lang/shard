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
 * @brief      Parenthesis expression.
 *
 * @details    Represents a parenthesis aroud another expression: `(<expr>)`.
 */
class ParenExpr final : public Expr, public PtrBuilder<ParenExpr, ExprPtr>
{
public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      expr   Inner expression.
     * @param      range  Location in source.
     */
    explicit ParenExpr(ExprPtr expr, SourceRange range = {})
        : Expr(range)
        , m_expr(std::move(expr))
    {
        SHARD_ASSERT(m_expr);
    }

public:
    // Accessors & Mutators

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
     * @brief      Change the inner expression.
     *
     * @param      expr  The new inner expression.
     */
    void setExpr(ExprPtr expr)
    {
        SHARD_ASSERT(expr);
        m_expr = std::move(expr);
    }

public:
    // Operations

    /**
     * @brief      Perform semantic analysis.
     *
     * @param      context  The context.
     */
    void analyse(AnalysisContext& context) override;

    /**
     * @brief      Dump declaration to stream.
     *
     * @param      context  The context.
     */
    void dump(const DumpContext& context) const override;

private:
    // Data Members

    /// Inner expression.
    ExprPtr m_expr;
};

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

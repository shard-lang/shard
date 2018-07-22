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
#include "shard/UniquePtr.hpp"
#include "shard/ViewPtr.hpp"
#include "shard/ast/Expr.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

/**
 * @brief      Ternary expression.
 *
 * @details    This expression is used for ternary operator: `<condExpr> ?
 *             <trueExpr> : <falseExpr>`.
 */
[[deprecated]] class TernaryExpr final : public Expr
{
public:
    // Constants

    /// Expression kind
    static constexpr ExprKind Kind = ExprKind::Ternary;

public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      condExpr   Condition expression.
     * @param      trueExpr   Left operand expression.
     * @param      falseExpr  Right operand expression.
     * @param      range      Location in source.
     */
    explicit TernaryExpr(
        ExprPtr condExpr,
        ExprPtr trueExpr,
        ExprPtr falseExpr,
        SourceRange range = {})
        : Expr(Kind, range)
        , m_condExpr(std::move(condExpr))
        , m_trueExpr(std::move(trueExpr))
        , m_falseExpr(std::move(falseExpr))
    {
        // Nothing to do
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns condition expression.
     *
     * @return     Condition expression.
     */
    ViewPtr<const Expr> getCondExpr() const noexcept
    {
        return makeView(m_condExpr);
    }

    /**
     * @brief      Returns condition expression.
     *
     * @return     Condition expression.
     */
    ViewPtr<Expr> getCondExpr() noexcept
    {
        return makeView(m_condExpr);
    }

    /**
     * @brief      Change condition expression.
     *
     * @param      expr  The new expression.
     */
    void setCondExpr(ExprPtr expr)
    {
        SHARD_ASSERT(expr);
        m_condExpr = std::move(expr);
    }

    /**
     * @brief      Returns true expression.
     *
     * @return     True expression.
     */
    ViewPtr<const Expr> getTrueExpr() const noexcept
    {
        return makeView(m_trueExpr);
    }

    /**
     * @brief      Returns true expression.
     *
     * @return     True expression.
     */
    ViewPtr<Expr> getTrueExpr() noexcept
    {
        return makeView(m_trueExpr);
    }

    /**
     * @brief      Change true branch expression.
     *
     * @param      expr  The new expression.
     */
    void setTrueExpr(ExprPtr expr)
    {
        SHARD_ASSERT(expr);
        m_trueExpr = std::move(expr);
    }

    /**
     * @brief      Returns false expression.
     *
     * @return     False expression.
     */
    ViewPtr<const Expr> getFalseExpr() const noexcept
    {
        return makeView(m_falseExpr);
    }

    /**
     * @brief      Returns false expression.
     *
     * @return     False expression.
     */
    ViewPtr<Expr> getFalseExpr() noexcept
    {
        return makeView(m_falseExpr);
    }

    /**
     * @brief      Change false branch expression.
     *
     * @param      expr  The new expression.
     */
    void setFalseExpr(ExprPtr expr)
    {
        SHARD_ASSERT(expr);
        m_falseExpr = std::move(expr);
    }

public:
    // Operations

    /**
     * @brief      Construct object.
     *
     * @param      condExpr   Condition expression.
     * @param      trueExpr   Left operand expression.
     * @param      falseExpr  Right operand expression.
     * @param      range      Location in source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<TernaryExpr> make(
        ExprPtr condExpr,
        ExprPtr trueExpr,
        ExprPtr falseExpr,
        SourceRange range = {})
    {
        return makeUnique<TernaryExpr>(
            std::move(condExpr),
            std::move(trueExpr),
            std::move(falseExpr),
            std::move(range));
    }

private:
    // Data Members

    /// Condition expression.
    ExprPtr m_condExpr;

    /// True expression.
    ExprPtr m_trueExpr;

    /// False expression.
    ExprPtr m_falseExpr;
};

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

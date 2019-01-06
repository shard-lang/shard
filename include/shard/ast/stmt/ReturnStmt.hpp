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
#include "shard/ast/Expr.hpp"
#include "shard/ast/Stmt.hpp"
#include "shard/ast/utility.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

/**
 * @brief Return statement.
 *
 * @details    In the source it appears as: `return <resExpr>;` or `return;`.
 */
class ReturnStmt final : public Stmt
{

public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      resExpr  Result expression.
     * @param      range    Source range.
     */
    explicit ReturnStmt(ExprPtr resExpr = nullptr, SourceRange range = {})
        : Stmt(range)
        , m_resExpr(std::move(resExpr))
    {
        // Nothing to do
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns result expression.
     *
     * @return     Result expression.
     */
    const ExprPtr& resExpr() const noexcept
    {
        return m_resExpr;
    }

    /**
     * @brief      Returns result expression.
     *
     * @tparam     EXPR  Expession type.
     *
     * @return     Result expression.
     *
     * @pre        `resExpr().is<EXPR>()`.
     */
    template<typename EXPR>
    EXPR& resExpr() noexcept
    {
        return resExpr()->cast<EXPR>();
    }

    /**
     * @brief      Returns result expression.
     *
     * @tparam     EXPR  Expession type.
     *
     * @return     Result expression.
     *
     * @pre        `resExpr().is<EXPR>()`.
     */
    template<typename EXPR>
    const EXPR& resExpr() const noexcept
    {
        return resExpr()->cast<EXPR>();
    }

    /**
     * @brief      Change result epxression.
     *
     * @param      expr  The new result expression.
     */
    void setResExpr(UniquePtr<Expr> expr)
    {
        m_resExpr = std::move(expr);
    }

public:
    // Operations

    /**
     * @brief      Construct object.
     *
     * @param      resExpr  Result expression.
     * @param      range    Source range.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<ReturnStmt> make(
        ExprPtr resExpr   = nullptr,
        SourceRange range = {})
    {
        return makeUnique<ReturnStmt>(std::move(resExpr), range);
    }

private:
    // Data Members

    /// Return expression.
    ExprPtr m_resExpr;
};

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

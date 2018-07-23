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
#include "shard/ViewPtr.hpp"
#include "shard/ast/Expr.hpp"
#include "shard/ast/Stmt.hpp"
#include "shard/ast/utility.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

/**
 * @brief      Expression statement.
 *
 * @details    In the source it represents: `;` or `<expr>;`. When the `expr` is
 *             `nullptr` it's an empty statement.
 */
class ExprStmt final : public Stmt, public PtrBuilder<ExprStmt, ExprPtr>
{
public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      expr   Expression.
     * @param      range  Source range.
     */
    explicit ExprStmt(ExprPtr expr = nullptr, SourceRange range = {})
        : Stmt(StmtKind::Expr, range)
        , m_expr(std::move(expr))
    {
        // Nothing to do
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns expression.
     *
     * @return     Expression.
     */
    ExprPtr& expr() noexcept
    {
        return m_expr;
    }

    /**
     * @brief      Returns expression.
     *
     * @return     Expression.
     */
    const ExprPtr& expr() const noexcept
    {
        return m_expr;
    }

    /**
     * @brief      Returns expression.
     *
     * @return     Expression.
     */
    [[deprecated]] ViewPtr<Expr> getExpr() noexcept
    {
        return makeView(m_expr);
    }

    /**
     * @brief      Returns expression.
     *
     * @return     Expression.
     */
    [[deprecated]] ViewPtr<const Expr> getExpr() const noexcept
    {
        return makeView(m_expr);
    }

    /**
     * @brief      Change the expression.
     *
     * @param      expr  The new expression.
     */
    void setExpr(ExprPtr expr)
    {
        m_expr = std::move(expr);
    }

private:
    // Data Members

    /// Expression.
    ExprPtr m_expr;
};

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

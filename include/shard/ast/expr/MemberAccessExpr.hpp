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
 * @brief      Member access expression.
 *
 * @details    In the source it represents following expression:
 * `<expr>.<name>`.
 */
class MemberAccessExpr final
    : public Expr,
      public PtrBuilder<MemberAccessExpr, ExprPtr, String>
{
public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      expr   Evaluation context expression.
     * @param      name   Identifier name.
     * @param      range  Location in source.
     */
    explicit MemberAccessExpr(ExprPtr expr, String name, SourceRange range = {})
        : Expr(range)
        , m_expr(std::move(expr))
        , m_name(std::move(name))
    {
        SHARD_ASSERT(!m_name.empty());
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

    /**
     * @brief      Returns identifier name.
     *
     * @return     Identifier name.
     */
    const String& name() const noexcept
    {
        return m_name;
    }

    /**
     * @brief      Change identifier name.
     *
     * @param      name  The new identifier name.
     */
    void setName(String name)
    {
        m_name = std::move(name);
    }

private:
    // Data Members

    /// Left expression.
    ExprPtr m_expr;

    /// Identifier name.
    String m_name;
};

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

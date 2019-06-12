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
#include "shard/String.hpp"
#include "shard/ast/Decl.hpp"
#include "shard/ast/Expr.hpp"
#include "shard/ast/utility.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

/**
 * @brief      Variable declaration.
 */
class VariableDecl final
    : public Decl,
      public PtrBuilder<VariableDecl, String, String, ExprPtr>
{

public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      type      The variable type.
     * @param      name      The variable name.
     * @param      initExpr  The optional initialization expression.
     * @param      range     The declaration location within the source.
     */
    explicit VariableDecl(
        String type,
        String name,
        ExprPtr initExpr      = nullptr,
        SourceRange range     = {})
        : Decl(std::move(name), std::move(range))
        , m_type(std::move(type))
        , m_initExpr(std::move(initExpr))
    {
        // Nothing to do
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Return the variable type.
     *
     * @return     The variable type.
     */
    const String& type() const noexcept
    {
        return m_type;
    }

    /**
     * @brief      Change the variable type.
     *
     * @param      type  The variable type.
     */
    void setType(String type)
    {
        m_type = type;
    }

    /**
     * @brief      Returns the initialization expression.
     *
     * @return     The initialization expression.
     */
    const ExprPtr& initExpr() const noexcept
    {
        return m_initExpr;
    }

    /**
     * @brief      Returns the initialization expression.
     *
     * @tparam     EXPR  The expression type.
     *
     * @return     The initialization expression.
     *
     * @pre        `initExpr()->is<EXPR>()`.
     */
    template<typename EXPR>
    EXPR& initExpr() noexcept
    {
        return initExpr()->cast<EXPR>();
    }

    /**
     * @brief      Returns the initialization expression.
     *
     * @tparam     EXPR  The expression type.
     *
     * @return     The initialization expression.
     *
     * @pre        `initExpr()->is<EXPR>()`.
     */
    template<typename EXPR>
    const EXPR& initExpr() const noexcept
    {
        return initExpr()->cast<EXPR>();
    }

    /**
     * @brief      Change the initialization expression.
     *
     * @param      expr  The initialization expression.
     */
    void setInitExpr(ExprPtr expr)
    {
        m_initExpr = std::move(expr);
    }

private:
    // Data Members

    /// Variable type.
    String m_type;

    /// Initializer expression.
    ExprPtr m_initExpr;
};

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

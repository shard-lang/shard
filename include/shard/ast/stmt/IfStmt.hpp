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
#include "shard/ast/Expr.hpp"
#include "shard/ast/Stmt.hpp"
#include "shard/ast/utility.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

class IfStmt;

/* ************************************************************************* */

using IfStmtPtr = UniquePtr<IfStmt>;

/* ************************************************************************* */

/**
 * @brief      If branch statement.
 *
 * @details    In the source it appears as: `if (<condExpr>) <thenStmt>` or `if
 *             (<condExpr>) <thenStmt> else <elseStmt>`.
 */
class IfStmt final : public Stmt,
                     public PtrBuilder<IfStmt, ExprPtr, StmtPtr, StmtPtr>
{

public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      condExpr  Condition expression.
     * @param      thenStmt  Then branch statement.
     * @param      elseStmt  Else branch statement.
     * @param      range     Source range.
     */
    explicit IfStmt(
        ExprPtr condExpr,
        StmtPtr thenStmt,
        StmtPtr elseStmt  = nullptr,
        SourceRange range = {})
        : Stmt(range)
        , m_condExpr(std::move(condExpr))
        , m_thenStmt(std::move(thenStmt))
        , m_elseStmt(std::move(elseStmt))
    {
        SHARD_ASSERT(m_condExpr);
        SHARD_ASSERT(m_thenStmt);
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Return condition expression.
     *
     * @return     Condition expression.
     */
    const ExprPtr& condExpr() const noexcept
    {
        return m_condExpr;
    }

    /**
     * @brief      Return condition expression.
     *
     * @tparam     EXPR  Expression type.
     *
     * @return     Condition expression.
     *
     * @pre        `condExpr()->is<EXPR>()`.
     */
    template<typename EXPR>
    EXPR& condExpr() noexcept
    {
        return condExpr()->cast<EXPR>();
    }

    /**
     * @brief      Return condition expression.
     *
     * @tparam     EXPR  Expression type.
     *
     * @return     Condition expression.
     *
     * @pre        `condExpr()->is<EXPR>()`.
     */
    template<typename EXPR>
    const EXPR& condExpr() const noexcept
    {
        return condExpr()->cast<EXPR>();
    }

    /**
     * @brief      Change condition expression.
     *
     * @param      expr  The new condition expression.
     */
    void setCondExpr(ExprPtr expr)
    {
        m_condExpr = std::move(expr);
    }

    /**
     * @brief      Return then branch statement.
     *
     * @return     Then branch statement.
     */
    const StmtPtr& thenStmt() const noexcept
    {
        return m_thenStmt;
    }

    /**
     * @brief      Return then branch statement.
     *
     * @tparam     STMT  Statement type.
     *
     * @return     Then branch statement.
     *
     * @pre        `thenStmt()->is<STMT>()`.
     */
    template<typename STMT>
    STMT& thenStmt() noexcept
    {
        return thenStmt()->cast<STMT>();
    }

    /**
     * @brief      Return then branch statement.
     *
     * @tparam     STMT  Statement type.
     *
     * @return     Then branch statement.
     *
     * @pre        `thenStmt()->is<STMT>()`.
     */
    template<typename STMT>
    const STMT& thenStmt() const noexcept
    {
        return thenStmt()->cast<STMT>();
    }

    /**
     * @brief      Change then branch statement.
     *
     * @param      stmt  The new then branch statement.
     */
    void setThenStmt(StmtPtr stmt)
    {
        m_thenStmt = std::move(stmt);
    }

    /**
     * @brief      Return else branch statement.
     *
     * @return     Else branch statement.
     */
    const StmtPtr& elseStmt() const noexcept
    {
        return m_elseStmt;
    }

    /**
     * @brief      Return else branch statement.
     *
     * @tparam     STMT  Statement type.
     *
     * @return     Then branch statement.
     *
     * @pre        `elseStmt()->is<STMT>()`.
     */
    template<typename STMT>
    STMT& elseStmt() noexcept
    {
        return elseStmt()->cast<STMT>();
    }

    /**
     * @brief      Return else branch statement.
     *
     * @tparam     STMT  Statement type.
     *
     * @return     Then branch statement.
     *
     * @pre        `elseStmt()->is<STMT>()`.
     */
    template<typename STMT>
    const STMT& elseStmt() const noexcept
    {
        return elseStmt()->cast<STMT>();
    }

    /**
     * @brief      Change else branch statement.
     *
     * @param      stmt  The new else branch statement.
     */
    void setElseStmt(StmtPtr stmt)
    {
        m_elseStmt = std::move(stmt);
    }

public:
    // Operations

    /**
     * @brief      Dump declaration to stream.
     *
     * @param      context  The context.
     */
    void dump(const DumpContext& context) const override;

private:
    // Data Members

    /// Condition expression.
    ExprPtr m_condExpr;

    /// Then branch statement.
    StmtPtr m_thenStmt;

    /// Else branch statement.
    StmtPtr m_elseStmt;
};

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

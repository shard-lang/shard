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

class Expr;

/* ************************************************************************* */

class WhileStmt;

/* ************************************************************************* */

using WhileStmtPtr = UniquePtr<WhileStmt>;

/* ************************************************************************* */

/**
 * @brief      While loop statement.
 *
 * @details    In the source it appears as: `while (<condExpr>) <bodyStmt>`.
 */
class WhileStmt final : public Stmt,
                        public PtrBuilder<WhileStmt, ExprPtr, StmtPtr>
{

public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      condExpr  Condition expression.
     * @param      bodyStmt  Body statement.
     * @param      range     Source range.
     */
    WhileStmt(ExprPtr condExpr, StmtPtr bodyStmt, SourceRange range = {})
        : Stmt(range)
        , m_condExpr(std::move(condExpr))
        , m_bodyStmt(std::move(bodyStmt))
    {
        SHARD_ASSERT(m_condExpr);
        SHARD_ASSERT(m_bodyStmt);
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns condition expression.
     *
     * @return     Expression.
     */
    const ExprPtr& condExpr() const noexcept
    {
        return m_condExpr;
    }

    /**
     * @brief      Returns condition expression.
     *
     * @tparam     EXPR  Expession type.
     *
     * @return     Result expression.
     *
     * @pre        `condExpr().is<EXPR>()`.
     */
    template<typename EXPR>
    const EXPR& condExpr() noexcept
    {
        return condExpr()->cast<EXPR>();
    }

    /**
     * @brief      Returns condition expression.
     *
     * @tparam     EXPR  Expession type.
     *
     * @return     Result expression.
     *
     * @pre        `condExpr().is<EXPR>()`.
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
    void setCondExpr(UniquePtr<Expr> expr)
    {
        m_condExpr = std::move(expr);
    }

    /**
     * @brief      Returns body statement.
     *
     * @return     Body statement.
     */
    const StmtPtr& bodyStmt() const noexcept
    {
        return m_bodyStmt;
    }

    /**
     * @brief      Returns body statement.
     *
     * @tparam     STMT  The statement type.
     *
     * @return     Body statement.
     *
     * @pre        `bodyStmt().is<STMT>()`.
     */
    template<typename STMT>
    STMT& bodyStmt() noexcept
    {
        return bodyStmt()->cast<STMT>();
    }

    /**
     * @brief      Returns body statement.
     *
     * @tparam     STMT  The statement type.
     *
     * @return     Body statement.
     *
     * @pre        `bodyStmt().is<STMT>()`.
     */
    template<typename STMT>
    const STMT& bodyStmt() const noexcept
    {
        return bodyStmt()->cast<STMT>();
    }

    /**
     * @brief      Change body statement.
     *
     * @param      stmt  The new body statement.
     */
    void setBodyStmt(StmtPtr stmt)
    {
        m_bodyStmt = std::move(stmt);
    }

private:
    // Data Members

    /// Loop condition.
    ExprPtr m_condExpr;

    /// Body statement.
    StmtPtr m_bodyStmt;
};

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

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
#include "shard/ViewPtr.hpp"
#include "shard/ast/Stmt.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

class Expr;

/* ************************************************************************* */

/**
 * @brief      While loop statement.
 *
 * @details    In the source it appears as: `while (<condExpr>) <bodyStmt>`.
 */
[[deprecated]] class WhileStmt final : public Stmt
{

// Public Constants
public:


    /// Expression kind
    static constexpr StmtKind Kind = StmtKind::While;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      condExpr  Condition expression.
     * @param      bodyStmt  Body statement.
     * @param      range     Source range.
     */
    explicit WhileStmt(UniquePtr<Expr> condExpr, UniquePtr<Stmt> bodyStmt, SourceRange range = {}) ;


    /**
     * @brief      Destructor.
     */
    ~WhileStmt();


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns condition expression.
     *
     * @return     Expression.
     */
    ViewPtr<Expr> getCondExpr() noexcept;


    /**
     * @brief      Returns condition expression.
     *
     * @return     Expression.
     */
    ViewPtr<const Expr> getCondExpr() const noexcept;


    /**
     * @brief      Change condition expression.
     *
     * @param      expr  The new condition expression.
     */
    void setCondExpr(UniquePtr<Expr> expr);


    /**
     * @brief      Returns body statement.
     *
     * @return     Body statement.
     */
    ViewPtr<Stmt> getBodyStmt() noexcept;


    /**
     * @brief      Returns body statement.
     *
     * @return     Body statement.
     */
    ViewPtr<const Stmt> getBodyStmt() const noexcept;


    /**
     * @brief      Change body statement.
     *
     * @param      stmt  The new body statement.
     */
    void setBodyStmt(UniquePtr<Stmt> stmt);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      condExpr  Condition expression.
     * @param      bodyStmt  Body statement.
     * @param      range     Source range.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<WhileStmt> make(UniquePtr<Expr> condExpr, UniquePtr<Stmt> bodyStmt, SourceRange range = {});


// Private Data Members
private:

    /// Loop condition.
    UniquePtr<Expr> m_condExpr;

    /// Body statement.
    UniquePtr<Stmt> m_bodyStmt;

};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

inline ViewPtr<Expr> WhileStmt::getCondExpr() noexcept
{
    return makeView(m_condExpr);
}

/* ************************************************************************* */

inline ViewPtr<const Expr> WhileStmt::getCondExpr() const noexcept
{
    return makeView(m_condExpr);
}

/* ************************************************************************* */

inline ViewPtr<Stmt> WhileStmt::getBodyStmt() noexcept
{
    return makeView(m_bodyStmt);
}

/* ************************************************************************* */

inline ViewPtr<const Stmt> WhileStmt::getBodyStmt() const noexcept
{
    return makeView(m_bodyStmt);
}

/* ************************************************************************* */

}

/* ************************************************************************* */

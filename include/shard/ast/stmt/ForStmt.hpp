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
#include "shard/utility.hpp"
#include "shard/UniquePtr.hpp"
#include "shard/ViewPtr.hpp"
#include "shard/ast/Stmt.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

/**
 * @brief      For loop statement.
 *
 * @details    In the source it appears as: `for (<initStmt> <condExpr> ;
 *             <incExpr>) <bodyStmt>`.
 */
class ForStmt final : public Stmt
{

// Public Constants
public:


    /// Expression kind
    static constexpr StmtKind Kind = StmtKind::For;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      initStmt  Initialization statement.
     * @param      condExpr  Test expression.
     * @param      incExpr   Increment statement.
     * @param      bodyStmt  Body statement.
     * @param      range     Source range.
     */
    explicit ForStmt(UniquePtr<Stmt> initStmt, UniquePtr<Expr> condExpr, UniquePtr<Expr> incExpr, UniquePtr<Stmt> bodyStmt, SourceRange range = {});


    /**
     * @brief      Destructor.
     */
    ~ForStmt();


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns initialization statement.
     *
     * @return     Initialization statement.
     */
    ViewPtr<Stmt> getInitStmt() noexcept;


    /**
     * @brief      Returns initialization statement.
     *
     * @return     Initialization statement.
     */
    ViewPtr<const Stmt> getInitStmt() const noexcept;


    /**
     * @brief      Change initialization statement.
     *
     * @param      stmt  THe new initialization statement.
     */
    void setInitStmt(UniquePtr<Stmt> stmt);


    /**
     * @brief      Returns condition epxression.
     *
     * @return     Condition epxression.
     */
    ViewPtr<Expr> getCondExpr() noexcept;


    /**
     * @brief      Returns condition epxression.
     *
     * @return     Condition epxression.
     */
    ViewPtr<const Expr> getCondExpr() const noexcept;


    /**
     * @brief      Change condition epxression.
     *
     * @param      expr  The new condition epxression.
     */
    void setCondExpr(UniquePtr<Expr> expr);


    /**
     * @brief      Returns increment expression.
     *
     * @return     Increment expression.
     */
    ViewPtr<Expr> getIncExpr() noexcept;


    /**
     * @brief      Returns increment expression.
     *
     * @return     Increment expression.
     */
    ViewPtr<const Expr> getIncExpr() const noexcept;


    /**
     * @brief      Change increment expression.
     *
     * @param      expr  The new increment expression.
     */
    void setIncExpr(UniquePtr<Expr> expr);


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
     * @param      initStmt  Initialization statement.
     * @param      condExpr  Test expression.
     * @param      incExpr   Increment statement.
     * @param      bodyStmt  Body statement.
     * @param      range     Source range.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<ForStmt> make(UniquePtr<Stmt> initStmt, UniquePtr<Expr> condExpr, UniquePtr<Expr> incExpr, UniquePtr<Stmt> bodyStmt, SourceRange range = {});


// Private Data Members
private:

    /// Initialization statement.
    UniquePtr<Stmt> m_initStmt;

    /// Loop condition.
    UniquePtr<Expr> m_condExpr;

    /// Increment expression.
    UniquePtr<Expr> m_incExpr;

    /// Body statement.
    UniquePtr<Stmt> m_bodyStmt;

};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

inline ViewPtr<Stmt> ForStmt::getInitStmt() noexcept
{
    return makeView(m_initStmt);
}

/* ************************************************************************* */

inline ViewPtr<const Stmt> ForStmt::getInitStmt() const noexcept
{
    return makeView(m_initStmt);
}

/* ************************************************************************* */

inline ViewPtr<Expr> ForStmt::getCondExpr() noexcept
{
    return makeView(m_condExpr);
}

/* ************************************************************************* */

inline ViewPtr<const Expr> ForStmt::getCondExpr() const noexcept
{
    return makeView(m_condExpr);
}

/* ************************************************************************* */

inline ViewPtr<Expr> ForStmt::getIncExpr() noexcept
{
    return makeView(m_incExpr);
}

/* ************************************************************************* */

inline ViewPtr<const Expr> ForStmt::getIncExpr() const noexcept
{
    return makeView(m_incExpr);
}

/* ************************************************************************* */

inline ViewPtr<Stmt> ForStmt::getBodyStmt() noexcept
{
    return makeView(m_bodyStmt);
}

/* ************************************************************************* */

inline ViewPtr<const Stmt> ForStmt::getBodyStmt() const noexcept
{
    return makeView(m_bodyStmt);
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

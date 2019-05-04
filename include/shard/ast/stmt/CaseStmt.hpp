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
#include "shard/UniquePtr.hpp"
#include "shard/PtrVector.hpp"
#include "shard/ast/Stmt.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

class Expr;

/* ************************************************************************* */

/**
 * @brief      Case statement.
 *
 * @details    In the source it appears as: `case <expr>: <bodyStmt>`.
 */
class [[deprecated]] CaseStmt final : public Stmt
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      expr   The case expression.
     * @param      stmts  The statement list.
     * @param      range  Source range.
     */
    explicit CaseStmt(UniquePtr<Expr> expr, PtrVector<Stmt> stmts = {}, SourceRange range = {});


    /**
     * @brief      Destructor.
     */
    ~CaseStmt();


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns condition expression.
     *
     * @return     Condition expression.
     */
    ViewPtr<Expr> getExpr() noexcept;


    /**
     * @brief      Returns condition expression.
     *
     * @return     Condition expression.
     */
    ViewPtr<const Expr> getExpr() const noexcept;


    /**
     * @brief      Change expression.
     *
     * @param      expr  The new expression.
     */
    void setExpr(UniquePtr<Expr> expr);


    /**
     * @brief      Returns the statements.
     *
     * @return     The statements.
     */
    const PtrVector<Stmt>& getStmts() const noexcept;


    /**
     * @brief      Change the statements.
     *
     * @param      stmt  The new statements.
     */
    void setStmts(PtrVector<Stmt> stmts);


    /**
     * @brief      Add statement to body statement list.
     *
     * @param      stmt  Statement to be added.
     */
    void addStmt(UniquePtr<Stmt> stmt);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      expr   The case expression.
     * @param      stmts  The statement list.
     * @param      range  Source range.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<CaseStmt> make(UniquePtr<Expr> expr, PtrVector<Stmt> stmts = {}, SourceRange range = {});


// Private Data Members
private:

    /// Case test expression.
    UniquePtr<Expr> m_expr;

    /// The statements.
    PtrVector<Stmt> m_statements;

};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

inline ViewPtr<Expr> CaseStmt::getExpr() noexcept
{
    return makeView(m_expr);
}

/* ************************************************************************* */

inline ViewPtr<const Expr> CaseStmt::getExpr() const noexcept
{
    return makeView(m_expr);
}

/* ************************************************************************* */

inline const PtrVector<Stmt>& CaseStmt::getStmts() const noexcept
{
    return m_statements;
}

/* ************************************************************************* */

}

/* ************************************************************************* */

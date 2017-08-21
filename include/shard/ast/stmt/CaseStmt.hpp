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
#include "shard/PtrDynamicArray.hpp"
#include "shard/ast/Stmt.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

/**
 * @brief      Case statement.
 *
 * @details    In the source it appears as: `case <expr>: <bodyStmt>`.
 */
class CaseStmt final : public Stmt
{

// Public Constants
public:


    /// Expression kind
    static constexpr StmtKind Kind = StmtKind::Case;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      expr   The case expression.
     * @param      stmts  The statement list.
     * @param      range  Source range.
     */
    explicit CaseStmt(UniquePtr<Expr> expr, PtrDynamicArray<Stmt> stmts = {}, SourceRange range = {});


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
    const PtrDynamicArray<Stmt>& getStmts() const noexcept;


    /**
     * @brief      Change the statements.
     *
     * @param      stmt  The new statements.
     */
    void setStmts(PtrDynamicArray<Stmt> stmts);


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
    static UniquePtr<CaseStmt> make(UniquePtr<Expr> expr, PtrDynamicArray<Stmt> stmts = {}, SourceRange range = {});


// Private Data Members
private:

    /// Case test expression.
    UniquePtr<Expr> m_expr;

    /// The statements.
    PtrDynamicArray<Stmt> m_statements;

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

inline const PtrDynamicArray<Stmt>& CaseStmt::getStmts() const noexcept
{
    return m_statements;
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

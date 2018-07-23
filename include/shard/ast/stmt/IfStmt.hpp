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

namespace shard::ast {

/* ************************************************************************* */

class Expr;

/* ************************************************************************* */

/**
 * @brief      If branch statement.
 *
 * @details    In the source it appears as: `if (<condExpr>) <thenStmt>` or `if
 *             (<condExpr>) <thenStmt> else <elseStmt>`.
 */
[[deprecated]] class IfStmt final : public Stmt
{

// Public Constants
public:


    /// Expression kind
    static constexpr StmtKind Kind = StmtKind::If;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      condExpr  Condition expression.
     * @param      thenStmt  Then branch statement.
     * @param      elseStmt  Else branch statement.
     * @param      range     Source range.
     */
    explicit IfStmt(UniquePtr<Expr> condExpr, UniquePtr<Stmt> thenStmt, UniquePtr<Stmt> elseStmt = nullptr, SourceRange range = {});


    /**
     * @brief      Destructor.
     */
    ~IfStmt();


// Public Accessors & Mutators
public:


    /**
     * @brief      Return condition expression.
     *
     * @return     Condition expression.
     */
    ViewPtr<Expr> getCondExpr() noexcept;


    /**
     * @brief      Return condition expression.
     *
     * @return     Condition expression.
     */
    ViewPtr<const Expr> getCondExpr() const noexcept;


    /**
     * @brief      Change condition expression.
     *
     * @param      expr  The new condition expression.
     */
    void setCondExpr(UniquePtr<Expr> expr);


    /**
     * @brief      Return then branch statement.
     *
     * @return     Then branch statement.
     */
    ViewPtr<Stmt> getThenStmt() noexcept;


    /**
     * @brief      Return then branch statement.
     *
     * @return     Then branch statement.
     */
    ViewPtr<const Stmt> getThenStmt() const noexcept;


    /**
     * @brief      Change then branch statement.
     *
     * @param      stmt  The new then branch statement.
     */
    void setThenStmt(UniquePtr<Stmt> stmt);


    /**
     * @brief      Return else branch statement.
     *
     * @return     Else branch statement.
     */
    ViewPtr<Stmt> getElseStmt() noexcept;


    /**
     * @brief      Return else branch statement.
     *
     * @return     Else branch statement.
     */
    ViewPtr<const Stmt> getElseStmt() const noexcept;


    /**
     * @brief      Change else branch statement.
     *
     * @param      stmt  The new else branch statement.
     */
    void setElseStmt(UniquePtr<Stmt> stmt);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      condExpr  Condition expression.
     * @param      thenStmt  Then branch statement.
     * @param      elseStmt  Else branch statement.
     * @param      range     Source range.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<IfStmt> make(UniquePtr<Expr> condExpr, UniquePtr<Stmt> thenStmt, UniquePtr<Stmt> elseStmt = nullptr, SourceRange range = {});


// Private Data Members
private:

    /// Condition expression.
    UniquePtr<Expr> m_condExpr;

    /// Then branch statement.
    UniquePtr<Stmt> m_thenStmt;

    /// Else branch statement.
    UniquePtr<Stmt> m_elseStmt;

};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

inline ViewPtr<Expr> IfStmt::getCondExpr() noexcept
{
    return makeView(m_condExpr);
}

/* ************************************************************************* */

inline ViewPtr<const Expr> IfStmt::getCondExpr() const noexcept
{
    return makeView(m_condExpr);
}

/* ************************************************************************* */

inline ViewPtr<Stmt> IfStmt::getThenStmt() noexcept
{
    return makeView(m_thenStmt);
}

/* ************************************************************************* */

inline ViewPtr<const Stmt> IfStmt::getThenStmt() const noexcept
{
    return makeView(m_thenStmt);
}

/* ************************************************************************* */

inline ViewPtr<Stmt> IfStmt::getElseStmt() noexcept
{
    return makeView(m_elseStmt);
}

/* ************************************************************************* */

inline ViewPtr<const Stmt> IfStmt::getElseStmt() const noexcept
{
    return makeView(m_elseStmt);
}

/* ************************************************************************* */

}

/* ************************************************************************* */

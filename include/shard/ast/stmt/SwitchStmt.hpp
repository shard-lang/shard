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
#include "shard/PtrDynamicArray.hpp"
#include "shard/ast/Stmt.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

class Expr;
class CompoundStmt;

/* ************************************************************************* */

/**
 * @brief      Switch branch statement.
 *
 * @details    In the source it appears as: `switch (<condExpr>) <bodyStmt>`.
 */
[[deprecated]] class SwitchStmt final : public Stmt
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      condExpr  Condition expression.
     * @param      bodyStmt  Body statement.
     * @param      range     Source range.
     */
    explicit SwitchStmt(UniquePtr<Expr> condExpr, UniquePtr<CompoundStmt> bodyStmt, SourceRange range = {});


    /**
     * @brief      Destructor.
     */
    ~SwitchStmt();


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns condition expression.
     *
     * @return     Condition expression.
     */
    ViewPtr<Expr> getCondExpr() noexcept;


    /**
     * @brief      Returns condition expression.
     *
     * @return     Condition expression.
     */
    ViewPtr<const Expr> getCondExpr() const noexcept;


    /**
     * @brief      Change condition epxression.
     *
     * @param      expr  The new condition epxression.
     */
    void setCondExpr(UniquePtr<Expr> expr);


    /**
     * @brief      Returns body statement.
     *
     * @return     Body statement.
     */
    ViewPtr<CompoundStmt> getBodyStmt() noexcept;


    /**
     * @brief      Returns body statement.
     *
     * @return     Body statement.
     */
    ViewPtr<const CompoundStmt> getBodyStmt() const noexcept;


    /**
     * @brief      Change body statement.
     *
     * @param      stmt  The new body statement.
     */
    void setBodyStmt(UniquePtr<CompoundStmt> stmt);


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
    static UniquePtr<SwitchStmt> make(UniquePtr<Expr> condExpr, UniquePtr<CompoundStmt> bodyStmt, SourceRange range = {});


// Private Data Members
private:

    /// Switch expression.
    UniquePtr<Expr> m_condExpr;

    /// Body statement.
    UniquePtr<CompoundStmt> m_bodyStmt;

};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

inline ViewPtr<Expr> SwitchStmt::getCondExpr() noexcept
{
    return makeView(m_condExpr);
}

/* ************************************************************************* */

inline ViewPtr<const Expr> SwitchStmt::getCondExpr() const noexcept
{
    return makeView(m_condExpr);
}

/* ************************************************************************* */

inline ViewPtr<CompoundStmt> SwitchStmt::getBodyStmt() noexcept
{
    return makeView(m_bodyStmt);
}

/* ************************************************************************* */

inline ViewPtr<const CompoundStmt> SwitchStmt::getBodyStmt() const noexcept
{
    return makeView(m_bodyStmt);
}

/* ************************************************************************* */

}

/* ************************************************************************* */

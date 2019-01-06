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
#include "shard/PtrVector.hpp"
#include "shard/ast/Stmt.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

/**
 * @brief      Default statement.
 *
 * @details    In the source it appears as: `default: <bodyStmt>`.
 */
[[deprecated]] class DefaultStmt final : public Stmt
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      body      Body statements.
     * @param      range     Source range.
     */
    explicit DefaultStmt(PtrVector<Stmt> body = {}, SourceRange range = {});


    /**
     * @brief      Destructor.
     */
    ~DefaultStmt();


// Public Accessors & Mutators
public:


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
     * @param      body      Body statements.
     * @param      range     Source range.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<DefaultStmt> make(PtrVector<Stmt> body = {}, SourceRange range = {});


// Private Data Members
private:

    /// The statements.
    PtrVector<Stmt> m_statements;

};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

inline const PtrVector<Stmt>& DefaultStmt::getStmts() const noexcept
{
    return m_statements;
}

/* ************************************************************************* */

}

/* ************************************************************************* */

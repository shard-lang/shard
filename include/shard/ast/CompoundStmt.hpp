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
#include "shard/PtrDynamicArray.hpp"
#include "shard/ast/Stmt.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

/**
 * @brief      Compound statement.
 *
 * @details    It's a container for other statements. In the source is looks
 *             like this: `{ <stmts> }`.
 */
class CompoundStmt final : public Stmt
{

// Public Constants
public:


    /// Expression kind
    static constexpr StmtKind Kind = StmtKind::Compound;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      stmts  A list of statements.
     * @param      range  Source range.
     */
    explicit CompoundStmt(PtrDynamicArray<Stmt> stmts = {}, SourceRange range = {});


    /**
     * @brief      Destructor.
     */
    ~CompoundStmt();


// Public Accessors & Mutators
public:


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
     * @param      stmts  A list of statements.
     * @param      range  Source range.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<CompoundStmt> make(PtrDynamicArray<Stmt> stmts = {}, SourceRange range = {});


// Private Data Members
private:

    /// Case statements.
    PtrDynamicArray<Stmt> m_statements;

};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

inline const PtrDynamicArray<Stmt>& CompoundStmt::getStmts() const noexcept
{
    return m_statements;
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

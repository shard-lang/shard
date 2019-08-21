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
#include "shard/ast/Stmt.hpp"
#include "shard/ast/utility.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

class CompoundStmt;

/* ************************************************************************* */

using CompoundStmtPtr = UniquePtr<CompoundStmt>;

/* ************************************************************************* */

/**
 * @brief      Compound statement.
 *
 * @details    It's a container for other statements. In the source is looks
 *             like this: `{ <stmts> }`.
 */
class CompoundStmt final : public Stmt,
                           public PtrBuilder<CompoundStmt, StmtPtrVector>
{
public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      stmts  A list of statements.
     * @param      range  Source range.
     */
    explicit CompoundStmt(StmtPtrVector stmts = {}, SourceRange range = {})
        : Stmt(range)
        , m_statements(std::move(stmts))
    {
        // Nothing to do
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns the statements.
     *
     * @return     The statements.
     */
    const StmtPtrVector& stmts() const noexcept
    {
        return m_statements;
    }

    /**
     * @brief      Change the statements.
     *
     * @param      stmts  The new statements.
     */
    void setStmts(StmtPtrVector stmts)
    {
        m_statements = std::move(stmts);
    }

    /**
     * @brief      Add statement to body statement list.
     *
     * @param      stmt  Statement to be added.
     */
    void addStmt(StmtPtr stmt)
    {
        m_statements.push_back(std::move(stmt));
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

    /// The statements.
    StmtPtrVector m_statements;
};

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

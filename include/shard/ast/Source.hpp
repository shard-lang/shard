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

// C++
#include <iosfwd>

// Shard
#include "shard/ast/Stmt.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

/**
 * @brief      The top level AST container.
 */
class Source
{
public:
    // Ctors & Dtors

    /**
     * @brief      Default constructor.
     */
    Source() = default;

    /**
     * @brief      Constructor.
     *
     * @param      stmts  The statements.
     */
    explicit Source(StmtPtrVector stmts)
        : m_statements(std::move(stmts))
    {
        // Nothing to do
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns statements.
     *
     * @return     The statements.
     */
    StmtPtrVector& stmts() noexcept
    {
        return m_statements;
    }

    /**
     * @brief      Returns statements.
     *
     * @return     The statements.
     */
    const StmtPtrVector& stmts() const noexcept
    {
        return m_statements;
    }

    /**
     * @brief      Set statements.
     *
     * @param      stmts  The statements.
     */
    void setStmts(StmtPtrVector stmts)
    {
        m_statements = std::move(stmts);
    }

    /**
     * @brief      Add statement.
     *
     * @param      stmt  The statement to add.
     */
    void addStmt(StmtPtr stmt)
    {
        m_statements.push_back(std::move(stmt));
    }

public:
    // Operations

    /**
     * @brief      Perform semantic analysis.
     *
     * @return     If AST is semantically valid.
     */
    bool analyse();

    /**
     * @brief      Dump source to stream.
     *
     * @param      os    Output stream.
     */
    void dump(std::ostream& os) const;

private:
    // Data Members

    /// Statements
    StmtPtrVector m_statements;
};

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

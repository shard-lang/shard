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
#include "shard/PtrVector.hpp"
#include "shard/UniquePtr.hpp"
#include "shard/ast/Node.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

class DumpContext;
class AnalysisContext;

/* ************************************************************************* */

/**
 * @brief      Base statement class.
 */
class Stmt : public Node
{

public:
    // Ctors & Dtors

    /**
     * @brief Destructor.
     */
    virtual ~Stmt() = default;

public:
    // Operations

    /**
     * @brief      Perform semantic analysis.
     *
     * @param      context  The context.
     */
    virtual void analyse([[maybe_unused]] AnalysisContext& context)
    {
        // Nothing to do
    }

    /**
     * @brief      Dump declaration to stream.
     *
     * @param      context  The context.
     */
    virtual void dump(const DumpContext& context) const;

protected:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      kind   Statement kind.
     * @param      range  Source range.
     */
    explicit Stmt(SourceRange range)
        : Node(range)
    {
        // Nothing to do
    }
};

/* ************************************************************************* */

/**
 * @brief A pointer to statement.
 */
using StmtPtr = UniquePtr<Stmt>;

/* ************************************************************************* */

/**
 * @brief A vector of statements.
 */
using StmtPtrVector = Vector<StmtPtr>;

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

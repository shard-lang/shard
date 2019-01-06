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

class ContinueStmt;

/* ************************************************************************* */

using ContinueStmtPtr = UniquePtr<ContinueStmt>;

/* ************************************************************************* */

/**
 * @brief      Continue statement.
 *
 * @details    In the source it appears as: `continue;`.
 */
class ContinueStmt final : public Stmt, public PtrBuilder<ContinueStmt>
{

public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      range  Source range.
     */
    explicit ContinueStmt(SourceRange range = {})
        : Stmt(range)
    {
        // Nothing to do
    }
};

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

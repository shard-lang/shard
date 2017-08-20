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
#include "shard/ast/Stmt.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

/**
 * @brief      Break statement.
 *
 * @details    In the source it appears as: `break;`.
 */
class BreakStmt final : public Stmt
{

// Public Constants
public:


    /// Expression kind
    static constexpr StmtKind Kind = StmtKind::Break;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      range  Source range.
     */
    explicit BreakStmt(SourceRange range = {});


    /**
     * @brief      Destructor.
     */
    ~BreakStmt();


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      range  Source range.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<BreakStmt> make(SourceRange range = {});

};

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

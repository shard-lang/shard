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
#include "shard/UniquePtr.hpp"
#include "shard/ViewPtr.hpp"
#include "shard/ast/Node.hpp"
#include "shard/ast/utility.hpp"
#include "shard/utility.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

class Expr;
class Decl;

/* ************************************************************************* */

/**
 * @brief      Statement kind.
 */
[[deprecated]] enum class StmtKind {
    Expr,
    Decl,
    Compound,
    If,
    While,
    DoWhile,
    For,
    Switch,
    Case,
    Default,
    Continue,
    Break,
    Return
};

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
    virtual ~Stmt() = 0;

public:
    // Accessors & Mutators

    /**
     * @brief      Returns statement kind.
     *
     * @return     Statement kind.
     */
    [[deprecated]] StmtKind getKind() const noexcept
    {
        return m_kind;
    }

protected:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      kind   Statement kind.
     * @param      range  Source range.
     */
    [[deprecated]] explicit Stmt(StmtKind kind, SourceRange range);

private:
    // Data Members

    /// Statement kind.
    StmtKind m_kind;
};

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

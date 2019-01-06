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
#include "shard/Assert.hpp"
#include "shard/SourceLocation.hpp"
#include "shard/SourceRange.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

/**
 * @brief      Base class for all AST nodes.
 *
 * @details    Base class for all AST nodes which cannot be used directly. It
 *             just store information needed by all AST nodes.
 */
class Node
{
public:
    // Accessors & Mutators

    /**
     * @brief      Returns source range.
     *
     * @return     The source range.
     */
    constexpr const SourceRange& sourceRange() const noexcept
    {
        return m_sourceRange;
    }

public:
    // Operations

    /**
     * @brief      Test if current node match required node type.
     *
     * @tparam     NODE  Node type.
     *
     * @return     Returns `true` if this is `NODE`, `false` otherwise.
     */
    template<typename NODE>
    bool is() const noexcept
    {
        return dynamic_cast<const NODE*>(this) != nullptr;
    }

    /**
     * @brief      Cast this to required node type.
     *
     * @tparam     NODE  Node type.
     *
     * @return     Reference to required node type.
     *
     * @pre        `is<NODE>()`
     */
    template<typename NODE>
    NODE& cast() noexcept
    {
        SHARD_ASSERT(is<NODE>());
        return static_cast<NODE&>(*this);
    }

    /**
     * @brief      Cast this to required node type.
     *
     * @tparam     NODE  Node type.
     *
     * @return     Reference to required node type.
     *
     * @pre        `is<NODE>()`
     */
    template<typename NODE>
    const NODE& cast() const noexcept
    {
        SHARD_ASSERT(is<NODE>());
        return static_cast<const NODE&>(*this);
    }

protected:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      range  Source range.
     */
    constexpr Node(SourceRange range) noexcept
        : m_sourceRange(range)
    {
        // Nothing to do
    }

    /**
     * @brief      Destructor.
     */
    virtual ~Node() = default;

private:
    // Data Members

    /// Source range.
    SourceRange m_sourceRange;
};

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

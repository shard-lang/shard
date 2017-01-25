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
#include "shard/ViewPtr.hpp"
#include "shard/UniquePtr.hpp"
#include "shard/utility.hpp"
#include "shard/SourceLocation.hpp"
#include "shard/SourceRange.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {


/* ************************************************************************* */

/**
 * @brief Helper class for storing location in source code.
 */
class NodeBase
{

// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param range Source range.
     */
    NodeBase(SourceRange range) noexcept
        : m_range(moveValue(range))
    {
        // Nothing to do
    }


// Public Accessors & Mutators
public:


    /**
     * @brief Returns source range.
     * @return
     */
    const SourceRange& getSourceRange() const noexcept
    {
        return m_range;
    }


    /**
     * @brief Returns source range start.
     * @return
     */
    const SourceLocation& getSourceStart() const noexcept
    {
        return getSourceRange().getStart();
    }


    /**
     * @brief Returns source range end.
     * @return
     */
    const SourceLocation& getSourceEnd() const noexcept
    {
        return getSourceRange().getEnd();
    }


// Private Data Members
private:

    /// Source range.
    SourceRange m_range;

};

/* ************************************************************************* */

template<typename Kind>
class KindRange
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      first  The first value.
     * @param      last   The last value.
     */
    constexpr KindRange(Kind first, Kind last) noexcept
        : m_first(first)
        , m_last(last)
    {
        // Nothing to do
    }


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns the first value.
     *
     * @return     The first value.
     */
    Kind getFirst() const noexcept
    {
        return m_first;
    }


    /**
     * @brief      Returns the last value.
     *
     * @return     The last value.
     */
    Kind getLast() const noexcept
    {
        return m_last;
    }


// Public Operations
public:


    /**
     * @brief      Compare operator.
     *
     * @param      rng   The kind range.
     * @param      kind  The kind.
     *
     * @return     Comparision result.
     */
    friend constexpr bool operator==(KindRange rng, Kind kind)
    {
        return kind >= rng.getFirst() && kind <= rng.getLast();
    }


    /**
     * @brief      Compare operator.
     *
     * @param      kind  The kind.
     * @param      rng   The kind range.
     *
     * @return     Comparision result.
     */
    friend constexpr bool operator==(Kind kind, KindRange rng)
    {
        return operator==(rng, kind);
    }


// Private Data Members
private:

    /// The first value.
    Kind m_first;

    /// The last value.
    Kind m_last;

};

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

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
 * @brief      Helper class for storing location in source code.
 */
class NodeBase
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      range  Source range.
     */
    NodeBase(SourceRange range) noexcept;


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns source range.
     *
     * @return     The source range.
     */
    const SourceRange& getSourceRange() const noexcept;


    /**
     * @brief      Returns source range start.
     *
     * @return     The source start.
     */
    const SourceLocation& getSourceStart() const noexcept;


    /**
     * @brief      Returns source range end.
     *
     * @return     The source end.
     */
    const SourceLocation& getSourceEnd() const noexcept;


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
    constexpr KindRange(Kind first, Kind last) noexcept;


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns the first value.
     *
     * @return     The first value.
     */
    Kind getFirst() const noexcept;


    /**
     * @brief      Returns the last value.
     *
     * @return     The last value.
     */
    Kind getLast() const noexcept;


// Private Data Members
private:

    /// The first value.
    Kind m_first;

    /// The last value.
    Kind m_last;

};

/* ************************************************************************* */

/**
 * @brief      Compare operator.
 *
 * @param      rng   The kind range.
 * @param      kind  The kind.
 *
 * @tparam     Kind  Kind type.
 *
 * @return     Comparision result.
 */
template<typename Kind>
constexpr bool operator==(KindRange<Kind> rng, Kind kind);

/* ************************************************************************* */

/**
 * @brief      Compare operator.
 *
 * @param      kind  The kind.
 * @param      rng   The kind range.
 *
 * @tparam     Kind  Kind type.
 *
 * @return     Comparision result.
 */
template<typename Kind>
constexpr bool operator==(Kind kind, KindRange<Kind> rng);

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

inline NodeBase::NodeBase(SourceRange range) noexcept
    : m_range(moveValue(range))
{
    // Nothing to do
}

/* ************************************************************************* */

inline const SourceRange& NodeBase::getSourceRange() const noexcept
{
    return m_range;
}

/* ************************************************************************* */

inline const SourceLocation& NodeBase::getSourceStart() const noexcept
{
    return getSourceRange().getStart();
}

/* ************************************************************************* */

inline const SourceLocation& NodeBase::getSourceEnd() const noexcept
{
    return getSourceRange().getEnd();
}

/* ************************************************************************* */

template<typename Kind>
inline constexpr KindRange<Kind>::KindRange(Kind first, Kind last) noexcept
    : m_first(first)
    , m_last(last)
{
    // Nothing to do
}

/* ************************************************************************* */

template<typename Kind>
inline Kind KindRange<Kind>::getFirst() const noexcept
{
    return m_first;
}

/* ************************************************************************* */

template<typename Kind>
inline Kind KindRange<Kind>::getLast() const noexcept
{
    return m_last;
}

/* ************************************************************************* */

template<typename Kind>
inline constexpr bool operator==(KindRange<Kind> rng, Kind kind)
{
    return kind >= rng.getFirst() && kind <= rng.getLast();
}

/* ************************************************************************* */

template<typename Kind>
inline constexpr bool operator==(Kind kind, KindRange<Kind> rng)
{
    return operator==(rng, kind);
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

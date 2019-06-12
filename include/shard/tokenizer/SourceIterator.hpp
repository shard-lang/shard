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
#include <cstddef>
#include <iterator>

// Shard
#include "shard/SourceLocation.hpp"
#include "shard/ViewPtr.hpp"

/* ************************************************************************* */

namespace shard::tokenizer {

/* ************************************************************************* */

class Source; // FWD declaration

/* ************************************************************************* */

/**
 * @brief Input iterator from Source.
 */
class SourceIterator
{
public:
    // Types

    /// A signed integer type that can be used to identify distance between
    /// iterators.
    using difference_type = std::ptrdiff_t;

    /// The type of the values that can be obtained by dereferencing the
    /// iterator. This type is void for output iterators.
    using value_type = char;

    /// Defines a pointer to the type iterated over (value_type).
    using pointer = char*;

    /// Defines a reference to the type iterated over (value_type).
    using reference = char&;

    /// The category of the iterator.
    using iterator_category = std::forward_iterator_tag;

public:
    // Ctors & Dtors

    /**
     * @brief      Default constructor.
     */
    SourceIterator() = default;

    /**
     * @brief      Constructs the iterator.
     *
     * @param      source    The source iterate on.
     * @param      position  The position in the source.
     */
    explicit SourceIterator(const Source& source, std::size_t position) noexcept
        : m_source(&source)
        , m_position(position)
    {
        // Nothing to do
    }

public:
    // Operators

    /**
     * @brief      Compares two iterators.
     *
     * @param      rhs   Second iterator.
     *
     * @return     Are iterators equal?
     */
    bool operator==(const SourceIterator& rhs) const noexcept
    {
        return m_source == rhs.m_source && m_position == rhs.m_position;
    }

    /**
     * @brief      Compares two iterators.
     *
     * @param      rhs   Second iterator.
     *
     * @return     Aren't iterators equal?
     */
    bool operator!=(const SourceIterator& rhs) const noexcept
    {
        return !operator==(rhs);
    }

    /**
     * @brief      Dereference operator.
     *
     * @return     Current character.
     *
     * @pre        `hasSource()`.
     */
    char operator*() const noexcept;

    /**
     * @brief      Pre-increment operator.
     *
     * @return     Reference to this.
     *
     * @pre        `hasSource()`.
     */
    SourceIterator& operator++() noexcept
    {
        m_position++;
        return *this;
    }

    /**
     * @brief      Pre-increment operator.
     *
     * @return     Reference to this.
     *
     * @pre        `hasSource()`.
     */
    SourceIterator operator++(int) noexcept
    {
        SourceIterator tmp(*this);
        m_position++;
        return tmp;
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns if interator have source (not default constructed).
     *
     * @return     If has source.
     */
    bool hasSource() noexcept
    {
        return m_source != nullptr;
    }

    /**
     * @brief      Returns source the iterator use.
     *
     * @return     The source.
     *
     * @pre        `hasSource()`.
     */
    const Source& source() const noexcept
    {
        return *m_source;
    }

    /**
     * @brief      Return current source location.
     *
     * @return     The location.
     */
    SourceLocation location() const noexcept;

private:
    // Data Members

    /// Source
    ViewPtr<const Source> m_source;

    /// Position in the source.
    std::size_t m_position = 0;
};

/* ************************************************************************* */

} // namespace shard::tokenizer

/* ************************************************************************* */

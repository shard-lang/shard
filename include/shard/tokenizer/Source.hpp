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
#include "shard/FilePath.hpp"
#include "shard/SourceLocation.hpp"
#include "shard/String.hpp"
#include "shard/Vector.hpp"
#include "shard/tokenizer/SourceIterator.hpp"

/* ************************************************************************* */

namespace shard::tokenizer {

/* ************************************************************************* */

/**
 * @brief Streams data from various types of input.
 */
class Source
{
public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      source    The source code.
     * @param      filename  The source filename.
     */
    explicit Source(const String& source, FilePath filename = "<input>")
        : m_filename(std::move(filename))
    {
        // Process source code
        process(source);
    }

public:
    // Operators

    /**
     * @brief      Returns character at given position.
     *
     * @return     The character.
     */
    char operator[](std::size_t position) const noexcept
    {
        return m_source[position];
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns the source.
     *
     * @return     The source.
     */
    const String& source() const noexcept
    {
        return m_source;
    }

    /**
     * @brief      Returns the source filename.
     *
     * @return     The source filename.
     */
    const FilePath& filename() const noexcept
    {
        return m_filename;
    }

    /**
     * @brief      Returns source size.
     *
     * @return     The size.
     */
    std::size_t size() const noexcept
    {
        return m_source.size();
    }

    /**
     * @brief      Returns character at given position.
     *
     * @return     The character.
     */
    char at(std::size_t position) const
    {
        return m_source.at(position);
    }

    /**
     * @brief      Returns the begin iterator.
     *
     * @return     The begin iterator.
     */
    SourceIterator begin() const noexcept
    {
        return SourceIterator(*this, 0);
    }

    /**
     * @brief      Returns the end iterator.
     *
     * @return     The end iterator.
     */
    SourceIterator end() const noexcept
    {
        return SourceIterator(*this, m_source.size());
    }

    /**
     * @brief      Returns source location for given position.
     *
     * @param      position  The position.
     *
     * @return     The source location.
     */
    SourceLocation location(std::size_t position) const noexcept;

private:
    // Operations

    /**
     * @brief      Process input source.
     *
     * @param      source  The source.
     */
    void process(const String& source);

private:
    // Data Members

    /// Source code.
    String m_source;

    /// Source file name.
    FilePath m_filename;

    /// Map for position to line number.
    Vector<std::size_t> m_lines;
};

/* ************************************************************************* */

} // namespace shard::tokenizer

/* ************************************************************************* */

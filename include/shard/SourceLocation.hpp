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

namespace shard {
inline namespace v1 {

/* ************************************************************************* */

/**
 * @brief Stores source file location.
 *
 * Values should be in range:
 *   Line: [1, N]
 *   Column: [1, M]
 */
class SourceLocation
{

// Public Ctors & Dtors
public:


    /**
     * @brief Default constructor.
     */
    SourceLocation() = default;


    /**
     * @brief Constructor.
     * @param line   Line number.
     * @param column Column number.
     */
    SourceLocation(unsigned int line, unsigned int column) noexcept
        : m_line(line)
        , m_column(column)
    {
        // Nothing to do
    }


// Public Operators
public:


    /**
     * @brief Bool operator.
     * @return If location is valid.
     */
    explicit operator bool() const noexcept
    {
        return m_line != 0 && m_column != 0;
    }


// Public Accessors & Mutators
public:


    /**
     * @brief Returns line number.
     * @return Line number.
     */
    unsigned int getLine() const noexcept
    {
        return m_line;
    }


    /**
     * @brief Returns column number.
     * @return Column number.
     */
    unsigned int getColumn() const noexcept
    {
        return m_column;
    }


// Private Data Members
private:

    /// Line number.
    unsigned int m_line = 0;

    /// Column number.
    unsigned int m_column = 0;

};

/* ************************************************************************* */

/**
 * @brief Source location equals operator.
 * @param lhs The first source location.
 * @param rhs The second source location.
 * @return If source locations are equals.
 */
inline bool operator==(const SourceLocation& lhs, const SourceLocation& rhs) noexcept
{
    return lhs.getLine() == rhs.getLine() && lhs.getColumn() == rhs.getColumn();
}

/* ************************************************************************* */

/**
 * @brief Source location not equals operator.
 * @param lhs The first source location.
 * @param rhs The second source location.
 * @return If source locations not are equals.
 */
inline bool operator!=(const SourceLocation& lhs, const SourceLocation& rhs) noexcept
{
    return !operator==(lhs, rhs);
}

/* ************************************************************************* */

}
}

/* ************************************************************************* */

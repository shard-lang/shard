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

}
}

/* ************************************************************************* */

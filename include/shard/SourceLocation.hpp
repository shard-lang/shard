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

/* ************************************************************************* */

/**
 * @brief      Stores source file location.
 *
 * @details    Values should be in range: Line: [1, N] Column: [1, M]
 */
class SourceLocation
{

public:
    // Ctors & Dtors

    /**
     * @brief      Default constructor.
     */
    SourceLocation() = default;

    /**
     * @brief      Constructor.
     *
     * @param      line    Line number.
     * @param      column  Column number.
     */
    SourceLocation(int line, int column) noexcept
        : m_line(line)
        , m_column(column)
    {
        // Nothing to do
    }

public:
    // Operators

    /**
     * @brief      Bool operator.
     *
     * @return     If location is valid.
     */
    explicit operator bool() const noexcept
    {
        return m_line != 0 && m_column != 0;
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns line number.
     *
     * @return     Line number.
     */
    int line() const noexcept
    {
        return m_line;
    }

    /**
     * @brief      Returns column number.
     *
     * @return     Column number.
     */
    int column() const noexcept
    {
        return m_column;
    }

    /**
     * @brief      Increments line number and sets column number to 1.
     */
    void incLine() noexcept
    {
        ++m_line;
        m_column = 1;
    }

    /**
     * @brief      Increments column number.
     */
    void incColumn() noexcept
    {
        ++m_column;
    }

    /**
     * @brief      Returns line number.
     *
     * @return     Line number.
     */
    [[deprecated]] int getLine() const noexcept
    {
        return m_line;
    }

    /**
     * @brief      Returns column number.
     *
     * @return     Column number.
     */
    [[deprecated]] int getColumn() const noexcept
    {
        return m_column;
    }

    /**
     * @brief      Increments line number and sets column number to 1.
     */
    [[deprecated]] void addLine() noexcept
    {
        ++m_line;
        m_column = 1;
    }

    /**
     * @brief      Increments column number.
     */
    [[deprecated]] void addColumn() noexcept
    {
        ++m_column;
    }

    // Private Data Members
private:
    /// Line number.
    int m_line = 0;

    /// Column number.
    int m_column = 0;
};

/* ************************************************************************* */

/**
 * @brief      Source location equals operator.
 *
 * @param      lhs   The first source location.
 * @param      rhs   The second source location.
 *
 * @return     If source locations are equals.
 */
inline bool operator==(
    const SourceLocation& lhs,
    const SourceLocation& rhs) noexcept
{
    return lhs.line() == rhs.line() && lhs.column() == rhs.column();
}

/* ************************************************************************* */

/**
 * @brief      Source location not equals operator.
 *
 * @param      lhs   The first source location.
 * @param      rhs   The second source location.
 *
 * @return     If source locations not are equals.
 */
inline bool operator!=(
    const SourceLocation& lhs,
    const SourceLocation& rhs) noexcept
{
    return !operator==(lhs, rhs);
}

/* ************************************************************************* */

/**
 * @brief      Source location less operator.
 *
 * @param      lhs   The first source location.
 * @param      rhs   The second source location.
 *
 * @return     Comparision result.
 */
inline bool operator<(
    const SourceLocation& lhs,
    const SourceLocation& rhs) noexcept
{
    if (lhs.line() < rhs.line())
        return true;

    if (lhs.line() > rhs.line())
        return false;

    // lhs.line() == rhs.line()
    return lhs.column() < rhs.column();
}

/* ************************************************************************* */

/**
 * @brief      Source location less operator.
 *
 * @param      lhs   The first source location.
 * @param      rhs   The second source location.
 *
 * @return     Comparision result.
 */
inline bool operator>(
    const SourceLocation& lhs,
    const SourceLocation& rhs) noexcept
{
    return operator<(rhs, lhs);
}

/* ************************************************************************* */

/**
 * @brief      Source location less equal operator.
 *
 * @param      lhs   The first source location.
 * @param      rhs   The second source location.
 *
 * @return     Comparision result.
 */
inline bool operator<=(
    const SourceLocation& lhs,
    const SourceLocation& rhs) noexcept
{
    return !operator>(lhs, rhs);
}

/* ************************************************************************* */

/**
 * @brief      Source location greater equal operator.
 *
 * @param      lhs   The first source location.
 * @param      rhs   The second source location.
 *
 * @return     Comparision result.
 */
inline bool operator>=(
    const SourceLocation& lhs,
    const SourceLocation& rhs) noexcept
{
    return !operator<(lhs, rhs);
}

/* ************************************************************************* */

} // namespace shard

/* ************************************************************************* */

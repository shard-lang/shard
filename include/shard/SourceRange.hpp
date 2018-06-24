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
#include "shard/SourceLocation.hpp"

/* ************************************************************************* */

namespace shard {

/* ************************************************************************* */

/**
 * @brief      Range of source code locations.
 */
class SourceRange
{

public:
    // Ctors & Dtors

    /**
     * @brief      Default constructor.
     */
    SourceRange() = default;

    /**
     * @brief      Constructor.
     *
     * @param      start  Start location.
     * @param      end    End location.
     */
    SourceRange(SourceLocation start, SourceLocation end) noexcept
        : m_start(start)
        , m_end(end)
    {
        // Nothing to do
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns start location.
     *
     * @return     Start location.
     */
    [[deprecated]] const SourceLocation& getStart() const noexcept
    {
        return m_start;
    }

    /**
     * @brief      Returns start location.
     *
     * @return     Start location.
     */
    const SourceLocation& start() const noexcept
    {
        return m_start;
    }

    /**
     * @brief      Returns end location
     *
     * @return     End location.
     */
    [[deprecated]] const SourceLocation& getEnd() const noexcept
    {
        return m_end;
    }

    /**
     * @brief      Returns end location
     *
     * @return     End location.
     */
    const SourceLocation& end() const noexcept
    {
        return m_end;
    }

private:
    // Data Members

    /// Start location.
    SourceLocation m_start;

    /// End location.
    SourceLocation m_end;
};

/* ************************************************************************* */

} // namespace shard

/* ************************************************************************* */

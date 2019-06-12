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
#include <exception>

// Shard
#include "shard/SourceLocation.hpp"
#include "shard/String.hpp"

/* ************************************************************************* */

namespace shard::parser {

/* ************************************************************************* */

/**
 * @brief      Parse error.
 */
class ParseError : public std::exception
{
public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      message   The message.
     * @param      location  The source code location.
     */
    explicit ParseError(String message, SourceLocation location)
        : m_message(std::move(message))
        , m_location(location)
        , m_what(formatMessage(m_message, location))
    {
        // Nothing to do
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns error source location.
     *
     * @return     The location.
     */
    const SourceLocation& location() const noexcept
    {
        return m_location;
    }

    /**
     * @brief      Returns error message.
     *
     * @return     The message.
     */
    const char* what() const noexcept
    {
        return m_what.c_str();
    }

public:
    // Operations

    /**
     * @brief      Format result error message.
     *
     * @param      msg   The message.
     * @param      loc   The location.
     *
     * @return     The error message.
     */
    static String formatMessage(const String& msg, const SourceLocation& loc)
    {
        return toString(loc.line()) + ":" + toString(loc.column()) + ": " + msg;
    }

private:
    // Data Members

    /// Error message.
    String m_message;

    /// Location where the error comes from.
    SourceLocation m_location;

    /// The result message.
    String m_what;
};

/* ************************************************************************* */

} // namespace shard::parser

/* ************************************************************************* */

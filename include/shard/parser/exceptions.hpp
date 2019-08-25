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
#include "shard/exceptions.hpp"

/* ************************************************************************* */

namespace shard::parser {

/* ************************************************************************* */

/**
 * @brief      Parse error.
 */
class ParseError : public LocationError
{
public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      message   The message.
     * @param      location  The source code location.
     */
    ParseError(String message, SourceLocation location)
        : LocationError(std::move(message), std::move(location))
    {
        // Nothing to do
    }
};

/* ************************************************************************* */

} // namespace shard::parser

/* ************************************************************************* */

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
#include <utility>

// Shard
#include "shard/Exception.hpp"
#include "shard/String.hpp"

/* ************************************************************************* */

namespace shard::interpreter {

/* ************************************************************************* */

/**
 * @brief      Interpreter exception.
 */
class Exception : public shard::Exception
{

public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      msg   The message
     */
    explicit Exception(String msg)
        : m_message(std::move(msg))
    {
        // Nothing to do
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns error message.
     *
     * @return     The message.
     */
    const char* what() const noexcept override
    {
        return m_message.c_str();
    }

private:
    // Data Members

    /// Exception message.
    String m_message;
};

/* ************************************************************************* */

} // namespace shard::interpreter

/* ************************************************************************* */

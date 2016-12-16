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
#include "shard/utility.hpp"
#include "shard/String.hpp"
#include "shard/Exception.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace interpreter {

/* ************************************************************************* */

class Exception : public shard::Exception
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      msg   The message
     */
    explicit Exception(String msg)
        : m_message(moveValue(msg))
    {
        // Nothing to do
    }


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns error message.
     *
     * @return     The message.
     */
    const char* what() const noexcept override
    {
        return m_message.c_str();
    }


// Private Data Members
private:

    /// Exception message.
    String m_message;

};

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */
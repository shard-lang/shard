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
#include "shard/ViewPtr.hpp"
#include "shard/ast/Type.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace interpreter {

/* ************************************************************************* */

/**
 * @brief      Shard interpreter runtime variable.
 */
class Value
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     */
    Value() noexcept
        : m_type(nullptr)
        , m_value(0)
    {
        // Nothing to do
    }


    /**
     * @brief      Constructor.
     *
     * @param      value  The value.
     */
    explicit Value(int value) noexcept
        : m_type(&ast::TYPE_BUILTIN_INT)
        , m_value(value)
    {
        // Nothing to do
    }


// Public Accessors & Mutators
public:


    /**
     * @brief      Determines if value is null.
     *
     * @return     True if null, False otherwise.
     */
    bool isNull() const noexcept
    {
        return m_type == nullptr;
    }


    /**
     * @brief      Returns the declaration type.
     *
     * @return     The type.
     */
    ViewPtr<const ast::Type> getType() const noexcept
    {
        return m_type;
    }


    /**
     * @brief      Returns as integer.
     *
     * @return     The value.
     */
    int asInt() const noexcept
    {
        return m_value;
    }


// Public Operations
public:



// Private Data Members
private:

    /// Declaration type.
    ViewPtr<const ast::Type> m_type;

    /// Variable value.
    int m_value;

};

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

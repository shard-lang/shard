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
#include "shard/ViewPtr.hpp"
#include "shard/ast/Type.hpp"
#include "shard/interpreter/Value.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace interpreter {

/* ************************************************************************* */

/**
 * @brief      Shard interpreter runtime variable.
 */
class Variable
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      type  The variable declaration type.
     */
    explicit Variable(ViewPtr<const ast::Type> type);


// Public Accessors & Mutators
public:


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
     * @brief      Returns the current value.
     *
     * @return     The value.
     */
    Value& getValue() noexcept
    {
        return m_value;
    }


    /**
     * @brief      Returns the current value.
     *
     * @return     The value.
     */
    const Value& getValue() const noexcept
    {
        return m_value;
    }


    /**
     * @brief      Returns the current value.
     *
     * @return     The value.
     */
    void setValue(Value value) noexcept
    {
        m_value = moveValue(value);
    }


// Public Operations
public:



// Private Data Members
private:

    /// Declaration type.
    ViewPtr<const ast::Type> m_type;

    /// Variable value.
    Value m_value;

};

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

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
#include "shard/ir/Type.hpp"

/* ************************************************************************* */

namespace shard::ir {

/* ************************************************************************* */

/**
 * @brief      IR value repesentation.
 *
 * @return     Values are used for representing runtime values and in most cases
 *             doesn't represent specific value.
 */
class Value
{
public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      type  The value type.
     */
    explicit Value(ViewPtr<Type> type) noexcept
        : m_type(type)
    {
        // Nothing to do
    }

    /**
     * @brief      Destructor.
     */
    virtual ~Value() = default;

public:
    // Accessors & Mutators

    /**
     * @brief      Returns if value is constant.
     *
     * @return     True if constant, False otherwise.
     */
    virtual bool isConst() const noexcept
    {
        return false;
    }

    /**
     * @brief      Returns value type.
     *
     * @return     The type.
     */
    ViewPtr<Type> type() const noexcept
    {
        return m_type;
    }

    /**
     * @brief      Returns value type.
     *
     * @tparam     T     The required type of the type.
     *
     * @return     The type.
     */
    template<typename T>
    T& type() const noexcept
    {
        return m_type->as<T>();
    }

private:
    // Data Members

    /// Value type.
    ViewPtr<Type> m_type;
};

/* ************************************************************************* */

} // namespace shard::ir

/* ************************************************************************* */

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
#include <variant>

// Shard
#include "shard/interpreter/Exception.hpp"

/* ************************************************************************* */

namespace shard::interpreter {

/* ************************************************************************* */

/**
 * @brief      Shard interpreter runtime variable.
 */
class Value
{

public:
    // Types

    /// Alias for data.
    using Data = std::variant<
        std::monostate,
        bool,
        int8_t,
        int16_t,
        int32_t,
        int64_t,
        float,
        double>;


public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     */
    Value() = default;

    /**
     * @brief      Constructor.
     *
     * @param      value  The value.
     */
    template<typename T>
    Value(T value) noexcept
        : m_data{value}
    {
        // Nothing
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Return underlying data.
     *
     * @return     The data.
     */
    const Data& data() const noexcept
    {
        return m_data;
    }

    /**
     * @brief      If value is nothing.
     *
     * @return     True if nothing, False otherwise.
     */
    bool isNothing() const noexcept
    {
        return std::holds_alternative<std::monostate>(m_data);
    }

    /**
     * @brief      Check if value has given type.
     *
     * @tparam     T     The type.
     *
     * @return     If value have given type.
     */
    template<typename T>
    bool is() const noexcept
    {
        return std::holds_alternative<T>(m_data);
    }

    /**
     * @brief      Returns value of given type.
     *
     * @tparam     T     The type.
     *
     * @return     The value.
     *
     * @pre        `is<T>()`
     */
    template<typename T>
    const T& get() const
    {
        try
        {
            std::get<T>(m_data);
        }
        catch (std::bad_variant_access&)
        {
            throw Exception("Invalid variable type");
        }
    }

    /**
     * @brief      Store value.
     *
     * @param      value  The value.
     *
     * @tparam     T      The type.
     */
    template<typename T>
    void set(T value) noexcept
    {
        m_data = value;
    }

private:
    // Data Members

    /// The current value.
    Data m_data;
};

/* ************************************************************************* */

} // namespace shard::interpreter

/* ************************************************************************* */

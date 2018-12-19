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
#include <cstdint>

// Shard
#include "shard/ir/Type.hpp"
#include "shard/ir/Value.hpp"

/* ************************************************************************* */

namespace shard::ir {

/* ************************************************************************* */

/**
 * @brief      Fundamental value constant helper.
 *
 * @tparam     T     The type for primitive type.
 * @tparam     V     Fundamental type for this value.
 */
template<typename T, typename V>
class FundamentalConst : public Value
{
public:
    // Types

    /// Stored value type.
    using ValueType = V;

public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      value  The value.
     */
    explicit FundamentalConst(V value) noexcept
        : Value(T::instance())
        , m_value(value)
    {
        // Nothing to do
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns if value is constant.
     *
     * @return     True if constant, False otherwise.
     */
    bool isConst() const noexcept override
    {
        return true;
    }

    /**
     * @brief      Returns value.
     *
     * @return     The value.
     */
    ValueType value() const noexcept
    {
        return m_value;
    }

private:
    // Data Members

    /// The stored value.
    ValueType m_value;
};

/* ************************************************************************* */

/**
 * @brief      Int1 constant.
 */
using ConstInt1 = FundamentalConst<TypeInt1, bool>;

/* ************************************************************************* */

/**
 * @brief      Int8 constant.
 */
using ConstInt8 = FundamentalConst<TypeInt8, std::int8_t>;

/* ************************************************************************* */

/**
 * @brief      Int16 constant.
 */
using ConstInt16 = FundamentalConst<TypeInt16, std::int16_t>;

/* ************************************************************************* */

/**
 * @brief      Int32 constant.
 */
using ConstInt32 = FundamentalConst<TypeInt32, std::int32_t>;

/* ************************************************************************* */

/**
 * @brief      Int64 constant.
 */
using ConstInt64 = FundamentalConst<TypeInt64, std::int64_t>;

/* ************************************************************************* */

/**
 * @brief      Float32 constant.
 */
using ConstFloat32 = FundamentalConst<TypeFloat32, float>;

/* ************************************************************************* */

/**
 * @brief      Float64 constant.
 */
using ConstFloat64 = FundamentalConst<TypeFloat64, double>;

/* ************************************************************************* */

} // namespace shard::ir

/* ************************************************************************* */

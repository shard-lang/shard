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
#include "shard/ViewPtr.hpp"
#include "shard/Any.hpp"
#include "shard/String.hpp"
#include "shard/interpreter/Function.hpp"

/* ************************************************************************* */

namespace shard::interpreter {

/* ************************************************************************* */

/**
 * @brief      Stored value kind.
 */
enum class ValueKind
{
    Null,
    Bool,
    Int,
    Float,
    Char,
    String,
    Function
};

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
    Value() noexcept;


    /**
     * @brief      Constructor.
     *
     * @param      value  The value.
     */
    Value(bool value) noexcept;


    /**
     * @brief      Constructor.
     *
     * @param      value  The value.
     */
    Value(int value) noexcept;


    /**
     * @brief      Constructor.
     *
     * @param      value  The value.
     */
    Value(float value) noexcept;


    /**
     * @brief      Constructor.
     *
     * @param      value  The value.
     */
    Value(char32_t value) noexcept;


    /**
     * @brief      Constructor.
     *
     * @param      value  The value.
     */
    Value(String value) noexcept;


    /**
     * @brief      Constructor.
     *
     * @param      value  The value.
     */
    Value(Function value) noexcept;


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns stored value kind.
     *
     * @return     The kind.
     */
    ValueKind getKind() const noexcept;


    /**
     * @brief      Determines if value is null.
     *
     * @return     True if null, False otherwise.
     */
    bool isNull() const noexcept;


    /**
     * @brief      Returns as bool.
     *
     * @return     The value.
     */
    bool asBool() const noexcept;


    /**
     * @brief      Returns as integer.
     *
     * @return     The value.
     */
    int asInt() const noexcept;


    /**
     * @brief      Returns as float.
     *
     * @return     The value.
     */
    float asFloat() const noexcept;


    /**
     * @brief      Returns as character.
     *
     * @return     The value.
     */
    char32_t asChar() const noexcept;


    /**
     * @brief      Returns as string.
     *
     * @return     The value.
     */
    String asString() const noexcept;


    /**
     * @brief      Returns as function.
     *
     * @return     The value.
     */
    Function asFunction() const noexcept;


// Private Data Members
private:

    /// Stored value kind.
    ValueKind m_kind = ValueKind::Null;

    /// Variable value.
    Any m_value;

};

/* ************************************************************************* */

/**
 * @brief      Compare values.
 *
 * @param      lhs   The left hand side
 * @param      rhs   The right hand side
 *
 * @return     Comparision result.
 */
bool operator==(const Value& lhs, const Value& rhs);

/* ************************************************************************* */

/**
 * @brief      Compare values.
 *
 * @param      lhs   The left hand side
 * @param      rhs   The right hand side
 *
 * @return     Comparision result.
 */
bool operator!=(const Value& lhs, const Value& rhs);

/* ************************************************************************* */

/**
 * @brief      Compare values.
 *
 * @param      lhs   The left hand side
 * @param      rhs   The right hand side
 *
 * @return     Comparision result.
 */
bool operator<(const Value& lhs, const Value& rhs);

/* ************************************************************************* */

/**
 * @brief      Compare values.
 *
 * @param      lhs   The left hand side
 * @param      rhs   The right hand side
 *
 * @return     Comparision result.
 */
bool operator>(const Value& lhs, const Value& rhs);

/* ************************************************************************* */

/**
 * @brief      Compare values.
 *
 * @param      lhs   The left hand side
 * @param      rhs   The right hand side
 *
 * @return     Comparision result.
 */
bool operator<=(const Value& lhs, const Value& rhs);

/* ************************************************************************* */

/**
 * @brief      Compare values.
 *
 * @param      lhs   The left hand side
 * @param      rhs   The right hand side
 *
 * @return     Comparision result.
 */
bool operator>=(const Value& lhs, const Value& rhs);

/* ************************************************************************* */

/**
 * @brief      Add values.
 *
 * @param      lhs   The left hand side
 * @param      rhs   The right hand side
 *
 * @return     Operation result.
 */
Value operator+(const Value& lhs, const Value& rhs);

/* ************************************************************************* */

/**
 * @brief      Subtract values.
 *
 * @param      lhs   The left hand side
 * @param      rhs   The right hand side
 *
 * @return     Operation result.
 */
Value operator-(const Value& lhs, const Value& rhs);

/* ************************************************************************* */

/**
 * @brief      Multiply values.
 *
 * @param      lhs   The left hand side
 * @param      rhs   The right hand side
 *
 * @return     Operation result.
 */
Value operator*(const Value& lhs, const Value& rhs);

/* ************************************************************************* */

/**
 * @brief      Divide values.
 *
 * @param      lhs   The left hand side
 * @param      rhs   The right hand side
 *
 * @return     Operation result.
 */
Value operator/(const Value& lhs, const Value& rhs);

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

inline Value::Value() noexcept
{
    // Nothing to do
}

/* ************************************************************************* */

inline Value::Value(bool value) noexcept
    : m_kind(ValueKind::Bool)
    , m_value(value)
{
    // Nothing to do
}

/* ************************************************************************* */

inline Value::Value(int value) noexcept
    : m_kind(ValueKind::Int)
    , m_value(value)
{
    // Nothing to do
}

/* ************************************************************************* */

inline Value::Value(float value) noexcept
    : m_kind(ValueKind::Float)
    , m_value(value)
{
    // Nothing to do
}

/* ************************************************************************* */

inline Value::Value(char32_t value) noexcept
    : m_kind(ValueKind::Char)
    , m_value(value)
{
    // Nothing to do
}

/* ************************************************************************* */

inline Value::Value(String value) noexcept
    : m_kind(ValueKind::String)
    , m_value(std::move(value))
{
    // Nothing to do
}

/* ************************************************************************* */

inline Value::Value(Function value) noexcept
    : m_kind(ValueKind::Function)
    , m_value(value)
{
    // Nothing to do
}

/* ************************************************************************* */

inline ValueKind Value::getKind() const noexcept
{
    return m_kind;
}

/* ************************************************************************* */

inline bool Value::isNull() const noexcept
{
    return getKind() == ValueKind::Null;
}

/* ************************************************************************* */

inline bool Value::asBool() const noexcept
{
    SHARD_ASSERT(getKind() == ValueKind::Bool);
    return m_value.get<bool>();
}

/* ************************************************************************* */

inline int Value::asInt() const noexcept
{
    SHARD_ASSERT(getKind() == ValueKind::Int);
    return m_value.get<int>();
}

/* ************************************************************************* */

inline float Value::asFloat() const noexcept
{
    SHARD_ASSERT(getKind() == ValueKind::Float);
    return m_value.get<float>();
}

/* ************************************************************************* */

inline char32_t Value::asChar() const noexcept
{
    SHARD_ASSERT(getKind() == ValueKind::Char);
    return m_value.get<char32_t>();
}

/* ************************************************************************* */

inline String Value::asString() const noexcept
{
    SHARD_ASSERT(getKind() == ValueKind::String);
    return m_value.get<String>();
}

/* ************************************************************************* */

inline Function Value::asFunction() const noexcept
{
    SHARD_ASSERT(getKind() == ValueKind::Function);
    return m_value.get<Function>();
}

/* ************************************************************************* */

inline bool operator!=(const Value& lhs, const Value& rhs)
{
    return !operator==(lhs, rhs);
}

/* ************************************************************************* */

inline bool operator>(const Value& lhs, const Value& rhs)
{
    return operator<(rhs, lhs);
}

/* ************************************************************************* */

inline bool operator<=(const Value& lhs, const Value& rhs)
{
    return !operator>(lhs, rhs);
}

/* ************************************************************************* */

inline bool operator>=(const Value& lhs, const Value& rhs)
{
    return !operator<(lhs, rhs);
}

/* ************************************************************************* */

}

/* ************************************************************************* */

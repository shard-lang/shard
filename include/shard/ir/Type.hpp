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
#include "shard/Assert.hpp"
#include "shard/Exception.hpp"
#include "shard/String.hpp"
#include "shard/Vector.hpp"
#include "shard/ViewPtr.hpp"

/* ************************************************************************* */

namespace shard::ir {

/* ************************************************************************* */

/**
 * @brief      Exception for bad type casting.
 */
struct BadTypeCast : public Exception
{
    /**
     * @brief      Return exception message.
     *
     * @return     The message.
     */
    const char* what() const noexcept
    {
        return "bad type cast";
    }
};

/* ************************************************************************* */

/**
 * @brief      Type kind for basic types.
 */
enum class TypeKind
{
    Int1,
    Int8,
    Int16,
    Int32,
    Int64,
    Float32,
    Float64,
    Pointer,
    Struct
};

/* ************************************************************************* */

/**
 * @brief      Base class for types.
 */
class Type
{
public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      kind  The type kind.
     */
    explicit Type(TypeKind kind) noexcept
        : m_kind(kind)
    {
        // Nothing to do
    }

    /**
     * @brief      Destructor.
     */
    virtual ~Type() = default;

public:
    // Accessors & Mutators

    /**
     * @brief      Returns type kind.
     *
     * @return     The type kind.
     */
    TypeKind kind() const noexcept
    {
        return m_kind;
    }

    /**
     * @brief      Check if this type is required type.
     *
     * @tparam     T     The required type.
     *
     * @return     If this is the required type.
     */
    template<typename T>
    bool is() const noexcept
    {
        return T::typeKind == kind();
    }

    /**
     * @brief      Convert this pointer to required type.
     *
     * @tparam     T     The required type.
     *
     * @return     A reference to required type.
     */
    template<typename T>
    T& as()
    {
        SHARD_ASSERT(is<T>());
        return static_cast<T&>(*this);
    }

    /**
     * @brief      Convert this pointer to required type.
     *
     * @tparam     T     The required type.
     *
     * @return     A reference to required type.
     */
    template<typename T>
    const T& as() const
    {
        SHARD_ASSERT(is<T>());
        return static_cast<const T&>(*this);
    }

private:
    // Data Members

    /// The type kind.
    TypeKind m_kind;
};

/* ************************************************************************* */

/**
 * @brief      Type helper.
 */
template<TypeKind KIND>
class TypeHelper : public Type
{
public:
    // Constants

    /// Type kind.
    static constexpr const TypeKind typeKind = KIND;

public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     */
    TypeHelper() noexcept
        : Type(KIND)
    {
        // Nothing to do
    }
};

/* ************************************************************************* */

/**
 * @brief      Type helper for fundamental types.
 *
 * @tparam     KIND  The type kind.
 *
 * @details    Fundamental types are types which are defined only once and
 *             multiple instances of type object is not necessary.
 */
template<TypeKind KIND>
class TypeFundamental : public TypeHelper<KIND>
{
public:
    // Accessors & Mutators

    /**
     * @brief      Returns the global instance of primitive type.
     *
     * @return     The global instance.
     */
    static ViewPtr<TypeFundamental> instance()
    {
        static TypeFundamental s_instance;
        return &s_instance;
    }
};

/* ************************************************************************* */

/**
 * @brief      Int1 type.
 */
using TypeInt1 = TypeFundamental<TypeKind::Int1>;

/* ************************************************************************* */

/**
 * @brief      Int8 type.
 */
using TypeInt8 = TypeFundamental<TypeKind::Int8>;

/* ************************************************************************* */

/**
 * @brief      Int16 type.
 */
using TypeInt16 = TypeFundamental<TypeKind::Int16>;

/* ************************************************************************* */

/**
 * @brief      Int32 type.
 */
using TypeInt32 = TypeFundamental<TypeKind::Int32>;

/* ************************************************************************* */

/**
 * @brief      Int64 type.
 */
using TypeInt64 = TypeFundamental<TypeKind::Int64>;

/* ************************************************************************* */

/**
 * @brief      Float32 type.
 */
using TypeFloat32 = TypeFundamental<TypeKind::Float32>;

/* ************************************************************************* */

/**
 * @brief      Float64 type.
 */
using TypeFloat64 = TypeFundamental<TypeKind::Float64>;

/* ************************************************************************* */

/**
 * @brief      Type for pointers to other types.
 */
class TypePointer : public TypeHelper<TypeKind::Pointer>
{
public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      type  The type the pointer points to.
     */
    explicit TypePointer(ViewPtr<Type> type) noexcept
        : m_type(type)
    {
        // Nothing to do
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns the type the pointer points to.
     *
     * @return     The type.
     */
    ViewPtr<Type> type() const noexcept
    {
        return m_type;
    }

private:
    // Data Members

    /// The type the pointer points to.
    ViewPtr<Type> m_type;
};

/* ************************************************************************* */

/**
 * @brief      Type for structure of types.
 */
class TypeStruct : public TypeHelper<TypeKind::Struct>
{
public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      fields  The structure fields.
     */
    explicit TypeStruct(Vector<ViewPtr<Type>> fields) noexcept
        : m_fields(std::move(fields))
    {
        // Nothing to do
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns structure fields.
     *
     * @return     The fields.
     */
    const Vector<ViewPtr<Type>>& fields() const noexcept
    {
        return m_fields;
    }

    /**
     * @brief      Returns structure field.
     *
     * @param      pos   The field position.
     *
     * @return     The field.
     *
     * @pre        `pos >= 0 && pos < count()`.
     */
    ViewPtr<Type>& field(size_t pos) noexcept
    {
        return m_fields[pos];
    }

    /**
     * @brief      Returns structure field.
     *
     * @param      pos   The field position.
     *
     * @return     The field.
     *
     * @pre        `pos >= 0 && pos < count()`.
     */
    const ViewPtr<Type>& field(size_t pos) const noexcept
    {
        return m_fields[pos];
    }

    /**
     * @brief      Returns the number of struct fields.
     *
     * @return     The number of fields.
     */
    size_t size() const noexcept
    {
        return m_fields.size();
    }

private:
    // Data Members

    /// The struct fields.
    Vector<ViewPtr<Type>> m_fields;
};

/* ************************************************************************* */

} // namespace shard::ir

/* ************************************************************************* */

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
#include "shard/String.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

/**
 * @brief      Type of the type.
 */
enum class TypeKind
{
    /// Special type which allows to store any type at runtime. It's universal
    /// variable type.
    Var,

    /// Automatic variable type which is deduced by initializer expression. The
    /// type cannot be changed later and only values with same type can be
    /// stored withing the variable.
    Auto,

    /// No type. Usable only as functions return type.
    Void,

    /// Integer type.
    Int,

    /// Floating point type.
    Float,

    /// Character type (UNICODE).
    Char,

    /// String type.
    String,

    /// Boolean type.
    Bool,

    /// User defined type. Must be used with name of the type.
    Typename
};

/* ************************************************************************* */

/**
 * @brief      Variable type.
 *
 * @details    This class is used for store information about variable (and
 *             function return type and parameters) type. Variable type can be
 *             one of the builtin types or user defined type.
 */
class Type
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      kind  Type kind. The `TypeKind::Typename` cannot be used.
     */
    Type(TypeKind kind) noexcept;


    /**
     * @brief      Constructor.
     *
     * @param      name  The typename.
     *
     * @note       The result kind is `TypeKind::Typename`.
     */
    Type(String name);


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns type kind
     *
     * @return     The kind.
     */
    TypeKind getKind() const noexcept
    {
        return m_kind;
    }


    /**
     * @brief      Determines if type is builtin.
     *
     * @return     True if builtin, False otherwise.
     */
    bool isBuiltin() const noexcept
    {
        return getKind() != TypeKind::Typename;
    }


    /**
     * @brief      Returns the typename.
     *
     * @return     The name.
     */
    const String& getName() const noexcept
    {
        return m_name;
    }


// Private Data Members
private:

    /// Type kind.
    TypeKind m_kind;

    /// Type name.
    String m_name;
};

/* ************************************************************************* */

/**
 * @brief      Compare two types.
 *
 * @param      lhs   The left hand side
 * @param      rhs   The right hand side
 *
 * @return     Comparision result.
 */
bool operator==(const Type& lhs, const Type& rhs) noexcept;

/* ************************************************************************* */

/**
 * @brief      Compare two types.
 *
 * @param      lhs   The left hand side
 * @param      rhs   The right hand side
 *
 * @return     Comparision result.
 */
inline bool operator!=(const Type& lhs, const Type& rhs) noexcept
{
    return !operator==(lhs, rhs);
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

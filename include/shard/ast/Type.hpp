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

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

/**
 * @brief Type of the type.
 */
enum class TypeKind
{
    Void,
    Int,
    Float,
    Char,
    String,
    Var,
    Bool
};

/* ************************************************************************* */

/**
 * @brief Base type.
 */
class Type
{

// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param kind Type kind.
     */
    explicit Type(TypeKind kind) noexcept
        : m_kind(kind)
    {
        // Nothing to do
    }


    /**
     * @brief Destructor.
     */
    virtual ~Type();


// Public Accessors & Mutators
public:


    /**
     * @brief Returns type kind
     * @return
     */
    TypeKind getKind() const noexcept
    {
        return m_kind;
    }


// Private Data Members
private:

    /// Type kind.
    TypeKind m_kind;

};

/* ************************************************************************* */

/**
 * @brief Type information.
 *
 * Class is lightweight to copy and it's designed be a part of classes which
 * need some type information. Variables, parameters can have specificators
 * (like `const`) and having every used combination in some global type list
 * will be unmanagable. So this class contains enum which define if it is
 * a basic type or a user defined type and pointer to user defined type
 * declaration.
 */
class TypeInfo
{

// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param type Pointer to base type.
     */
    TypeInfo(ViewPtr<const Type> type) noexcept
        : m_type(type)
    {
        // Nothing to do
    }


// Public Accessors & Mutators
public:


    /**
     * @brief Returns base type.
     * @return
     */
    ViewPtr<const Type> getType() const noexcept
    {
        return m_type;
    }


    /**
     * @brief Change base type.
     * @param type
     */
    void setType(ViewPtr<const Type> type) noexcept
    {
        m_type = type;
    }


// Private Data Members
private:

    /// Pointer to base type.
    ViewPtr<const Type> m_type;

};

/* ************************************************************************* */

// Builtin types
extern const Type TYPE_BUILTIN_VOID;
extern const Type TYPE_BUILTIN_INT;
extern const Type TYPE_BUILTIN_FLOAT;
extern const Type TYPE_BUILTIN_CHAR;
extern const Type TYPE_BUILTIN_STRING;
extern const Type TYPE_BUILTIN_VAR;
extern const Type TYPE_BUILTIN_BOOL;

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

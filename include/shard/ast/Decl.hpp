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
#include "shard/utility.hpp"
#include "shard/UniquePtr.hpp"
#include "shard/ViewPtr.hpp"
#include "shard/String.hpp"
#include "shard/ast/Node.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

/**
 * @brief      Kind of Declaration.
 */
enum class DeclKind
{
    Variable,
    Function,
    Class,
    Namespace,
};

/* ************************************************************************* */

/**
 * @brief      Declaration access specifier.
 */
enum class DeclAccessSpecifier
{
    /// Access is not specified and use rules defined by context. It's also
    /// value for declaration where access specifier cannot be used
    /// (like local variables).
    Default,

    /// Declaration is accessible by anyone.
    Public,

    /// Declaration is accessible only under by some rules.
    Protected,

    /// Declaration is not accessible outside scope within compilation unit.
    /// If some other compilation unit define same scope the declaration is
    /// not accessible from that unit.
    Private
};

/* ************************************************************************* */

/**
 * @brief      Base declaration class.
 *
 * @details    This abstract class serves as base class for all declaration
 *             types as variable, function and class declaration. It's not
 *             possible to create an object of this class directly (pure virtual
 *             destructor, protected constructor), the only way is to create an
 *             object of child class. Type of the declaration can be obtained by
 *             calling `getKind`. All declarations are named so can be
 *             identified later. The name should represents declaration scope
 *             naming scheme not FQN scheme.
 */
class Decl : public Node
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Destructor.
     */
    virtual ~Decl() = 0;


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns the declaration kind.
     *
     * @details    Use for specific declaration type identification.
     *
     * @return     The declaration kind.
     */
    DeclKind getKind() const noexcept;


    /**
     * @brief      Returns the declaration name in local scope naming scheme.
     *
     * @return     The declaration name.
     */
    const String& getName() const noexcept;


    /**
     * @brief      Change the declaration name.
     *
     * @return     The declaration name in local scope naming scheme.
     */
    void setName(String name);


    /**
     * @brief      Returns the declaration access specifier.
     *
     * @return     The access specifier.
     */
    DeclAccessSpecifier getAccessSpecifier() const noexcept;


    /**
     * @brief      Change the declaration access specifier.
     *
     * @param      spec  The access specifier.
     */
    void setAccessSpecifier(DeclAccessSpecifier spec) noexcept;


// Public Operations
public:


    /**
     * @brief      Test if declaration match required kind.
     *
     * @tparam     DeclType  Declaration type.
     *
     * @return     Returns `true` if this is `DeclType`, `false` otherwise.
     */
    template<typename DeclType>
    bool is() const noexcept;


    /**
     * @brief      Cast this to required declaration type.
     *
     * @tparam     DeclType  Declaration type.
     *
     * @return     Reference to required declaration type.
     */
    template<typename DeclType>
    DeclType& cast() noexcept;


    /**
     * @brief      Cast this to required declaration type.
     *
     * @tparam     DeclType  Declaration type.
     *
     * @return     Reference to required declaration type.
     */
    template<typename DeclType>
    const DeclType& cast() const noexcept;


// Protected Ctors & Dtors
protected:


    /**
     * @brief      Constructor.
     *
     * @param      kind   The declaration kind.
     * @param      name   The declaration name in local scope naming scheme.
     * @param      range  The declaration location within the source.
     */
    explicit Decl(DeclKind kind, String name, SourceRange range);


// Private Data Members
private:

    /// Declaration kind.
    DeclKind m_kind;

    /// Declaration name.
    String m_name;

    /// Declaration access specifier
    DeclAccessSpecifier m_accessSpecifier = DeclAccessSpecifier::Default;
};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

inline DeclKind Decl::getKind() const noexcept
{
    return m_kind;
}

/* ************************************************************************* */

inline const String& Decl::getName() const noexcept
{
    return m_name;
}

/* ************************************************************************* */

inline DeclAccessSpecifier Decl::getAccessSpecifier() const noexcept
{
    return m_accessSpecifier;
}

/* ************************************************************************* */

inline void Decl::setAccessSpecifier(DeclAccessSpecifier spec) noexcept
{
    m_accessSpecifier = spec;
}

/* ************************************************************************* */

template<typename DeclType>
inline bool Decl::is() const noexcept
{
    return getKind() == DeclType::Kind;
}

/* ************************************************************************* */

template<typename DeclType>
inline DeclType& Decl::cast() noexcept
{
    SHARD_ASSERT(is<DeclType>());
    return static_cast<DeclType&>(*this);
}

/* ************************************************************************* */

template<typename DeclType>
inline const DeclType& Decl::cast() const noexcept
{
    SHARD_ASSERT(is<DeclType>());
    return static_cast<const DeclType&>(*this);
}

/* ************************************************************************* */

}

/* ************************************************************************* */

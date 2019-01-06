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
#include "shard/UniquePtr.hpp"
#include "shard/Vector.hpp"
#include "shard/ast/Node.hpp"

/* ************************************************************************* */

namespace shard::ast {

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
 *             object of child class. All declarations are named so can be
 *             identified later. The name should represents declaration scope
 *             naming scheme not FQN scheme.
 */
class Decl : public Node
{
public:
    // Ctors & Dtors

    /**
     * @brief      Destructor.
     */
    virtual ~Decl() = default;

public:
    // Accessors & Mutators

    /**
     * @brief      Returns the declaration name in local scope naming scheme.
     *
     * @return     The declaration name.
     */
    const String& name() const noexcept
    {
        return m_name;
    }

    /**
     * @brief      Change the declaration name.
     *
     * @return     The declaration name in local scope naming scheme.
     */
    void setName(String name)
    {
        m_name = std::move(name);
    }

    /**
     * @brief      Returns the declaration access specifier.
     *
     * @return     The access specifier.
     */
    DeclAccessSpecifier accessSpecifier() const noexcept
    {
        return m_accessSpecifier;
    }

    /**
     * @brief      Change the declaration access specifier.
     *
     * @param      spec  The access specifier.
     */
    void setAccessSpecifier(DeclAccessSpecifier spec) noexcept
    {
        m_accessSpecifier = spec;
    }

protected:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      kind   The declaration kind.
     * @param      name   The declaration name in local scope naming scheme.
     * @param      range  The declaration location within the source.
     */
    explicit Decl(String name, SourceRange range)
        : Node(range)
        , m_name(std::move(name))
    {
        // Nothing to do
    }

private:
    // Data Members

    /// Declaration name.
    String m_name;

    /// Declaration access specifier
    DeclAccessSpecifier m_accessSpecifier = DeclAccessSpecifier::Default;
};

/* ************************************************************************* */

/**
 * @brief A pointer to declaration.
 */
using DeclPtr = UniquePtr<Decl>;

/* ************************************************************************* */

/**
 * @brief A vector of declarations.
 */
using DeclPtrVector = Vector<DeclPtr>;

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

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
#include "shard/StringView.hpp"
#include "shard/DynamicArray.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

class Decl;
class NamedDecl;
class Type;

/* ************************************************************************* */

/**
 * @brief Declaration context.
 *
 * It represents declaration context/scope which can be global scope,
 * function scope, class scope or compound statement.
 */
class DeclContext
{

// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param parent Optional parent context.
     */
    explicit DeclContext(ViewPtr<DeclContext> parent = nullptr) noexcept
        : m_parent(parent)
    {
        // Nothing to do
    }


// Public Accessors & Mutators
public:


    /**
     * @brief Returns parent context.
     * @return Parent context or nullptr.
     */
    ViewPtr<DeclContext> getParent() const noexcept
    {
        return m_parent;
    }


    /**
     * @brief Returns registered declarations.
     * @return Declarations.
     */
    const DynamicArray<ViewPtr<Decl>>& getDeclarations() const noexcept
    {
        return m_declarations;
    }


    /**
     * @brief Add declaration.
     * @param decl Declaration to add.
     */
    void addDeclaration(ViewPtr<Decl> decl)
    {
        m_declarations.push_back(moveValue(decl));
    }


    /**
     * @brief Add declaration.
     * @param decl Declaration to remove.
     */
    void removeDeclaration(ViewPtr<Decl> decl);


    /**
     * @brief Find named declaration by name.
     * @param name Required declaration name.
     * @return Pointer to named declaration or nullptr.
     */
    ViewPtr<NamedDecl> findDeclaration(StringView name) const noexcept;


    /**
     * @brief Find type by name.
     * @param type Type name.
     * @return Pointer to type definition.
     */
    ViewPtr<const Type> findType(StringView type) const noexcept;


// Private Data Members
private:

    /// Parent context.
    ViewPtr<DeclContext> m_parent;

    /// Declarations
    DynamicArray<ViewPtr<Decl>> m_declarations;

};

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

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
#include "shard/UniquePtr.hpp"
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
     * @param decl   Declarations.
     * @param parent Optional parent context.
     */
    explicit DeclContext(ViewPtr<DeclContext> parent = nullptr) noexcept;


    /**
     * @brief Destructor.
     */
    ~DeclContext();


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
    const DynamicArray<UniquePtr<Decl>>& getDeclarations() const noexcept
    {
        return m_declarations;
    }


    /**
     * @brief Returns registered declarations with given type.
     * @tparam DeclType Required declaration type.
     * @return Declarations.
     */
    template<typename DeclType>
    DynamicArray<ViewPtr<DeclType>> getDeclarations() const noexcept
    {
        DynamicArray<ViewPtr<DeclType>> result;

        for (const auto& decl : getDeclarations())
        {
            if (DeclType::is(makeView(decl)))
                result.push_back(DeclType::cast(makeView(decl)));
        }

        return result;
    }


    /**
     * @brief Add declaration.
     * @param decl Declaration to add.
     * @return Added declaration
     */
    Decl& addDeclaration(UniquePtr<Decl> decl);


    /**
     * @brief Add a list of declarations.
     * @param decls Declarations to add.
     */
    template<typename DeclType>
    void addDeclarations(DynamicArray<UniquePtr<DeclType>> decls)
    {
        for (auto&& decl : decls)
            addDeclaration(moveValue(decl));
    }


    /**
     * @brief Add declaration.
     * @param args Construction arguments.
     * @return Created declaration.
     */
    template<typename DeclType, typename... Args>
    DeclType& createDeclaration(Args&&... args)
    {
        return static_cast<DeclType&>(
            addDeclaration(makeUnique<DeclType>(makeView(this), forwardValue<Args>(args)...))
        );
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
    DynamicArray<UniquePtr<Decl>> m_declarations;

};

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

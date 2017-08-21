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
#include "shard/String.hpp"
#include "shard/StringView.hpp"
#include "shard/Map.hpp"
#include "shard/interpreter/Symbol.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace interpreter {

/* ************************************************************************* */

/**
 * @brief      Shard interpreter scope.
 */
class Scope
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      parent  The optional parent scope.
     */
    Scope(ViewPtr<Scope> parent = nullptr);


// Public Accessors & Mutators
public:


    /**
     * @brief      Gets the parent scope.
     *
     * @return     The parent scope.
     */
    ViewPtr<Scope> getParent() noexcept;


    /**
     * @brief      Gets the parent scope.
     *
     * @return     The parent scope.
     */
    ViewPtr<const Scope> getParent() const noexcept;


// Public Operations
public:


    /**
     * @brief      Find a symbol in current scope.
     *
     * @param      name  The symbol name.
     *
     * @return     Pointer to symbol or nullptr.
     */
    ViewPtr<Symbol> findSymbol(StringView name) noexcept;


    /**
     * @brief      Creates a symbol.
     *
     * @param      name  The symbol name.
     * @param      kind  The symbol kind.
     *
     * @return     Pointer to symbol.
     *
     * @throws     Exception  If symbol already exists.
     */
    ViewPtr<Symbol> addSymbol(String name, SymbolKind kind);


// Private Data Members
private:

    /// Parent scope.
    ViewPtr<Scope> m_parent;

    /// Symbols table.
    Map<String, Symbol> m_symbols;

};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

inline ViewPtr<Scope> Scope::getParent() noexcept
{
    return m_parent;
}

/* ************************************************************************* */

inline ViewPtr<const Scope> Scope::getParent() const noexcept
{
    return m_parent;
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

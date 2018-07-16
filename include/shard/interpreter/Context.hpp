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
#include "shard/DynamicArray.hpp"
#include "shard/Map.hpp"
#include "shard/ast/Type.hpp"
#include "shard/interpreter/Symbol.hpp"

/* ************************************************************************* */

namespace shard::interpreter {

/* ************************************************************************* */

/**
 * @brief      Shard interpreter context.
 */
class Context
{

// Public Ctors & Dtors
public:


    Context();


// Public Operations
public:


    /**
     * @brief      Push new scope.
     */
    void push();


    /**
     * @brief      Pop current scope.
     */
    void pop();


    /**
     * @brief      Find a variable.
     *
     * @param      name  The variable name.
     *
     * @return     Pointer to variable or nullptr.
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
    ViewPtr<Symbol> addSymbol(StringView name, SymbolKind kind);


// Private Data Members
private:

    /// Scope based symbol table.
    DynamicArray<Map<String, Symbol>> m_scopes;

};

/* ************************************************************************* */

}

/* ************************************************************************* */

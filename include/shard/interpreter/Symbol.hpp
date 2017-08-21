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
#include "shard/interpreter/Value.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace interpreter {

/* ************************************************************************* */

class Scope;

/* ************************************************************************* */

/**
 * @brief      Kind of symbol.
 */
enum class SymbolKind
{
    Variable,
    Constant,
    Function
};

/* ************************************************************************* */

/**
 * @brief      Shard interpreter symbol.
 */
class Symbol
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      scope  The declaration scope.
     * @param      kind   The symbol kind.
     */
    Symbol(ViewPtr<Scope> scope, SymbolKind kind) noexcept;


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns the declaration scope.
     *
     * @return     The declaration scope.
     */
    ViewPtr<Scope> getScope() noexcept;


    /**
     * @brief      Returns the declaration scope.
     *
     * @return     The declaration scope.
     */
    ViewPtr<const Scope> getScope() const noexcept;


    /**
     * @brief      Returns the symbol kind.
     *
     * @return     The kind.
     */
    SymbolKind getKind() const noexcept;


    /**
     * @brief      Returns the current value.
     *
     * @return     The value.
     */
    Value& getValue() noexcept;


    /**
     * @brief      Returns the current value.
     *
     * @return     The value.
     */
    const Value& getValue() const noexcept;


    /**
     * @brief      Returns the current value.
     *
     * @return     The value.
     */
    void setValue(Value value) noexcept;


// Private Data Members
private:

    /// Declaration scope.
    ViewPtr<Scope> m_scope;

    /// Symbol kind.
    SymbolKind m_kind;

    /// Variable value.
    Value m_value;

};

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace interpreter {

/* ************************************************************************* */

inline ViewPtr<Scope> Symbol::getScope() noexcept
{
    return m_scope;
}

/* ************************************************************************* */

inline ViewPtr<const Scope> Symbol::getScope() const noexcept
{
    return m_scope;
}

/* ************************************************************************* */

inline SymbolKind Symbol::getKind() const noexcept
{
    return m_kind;
}

/* ************************************************************************* */

inline Value& Symbol::getValue() noexcept
{
    return m_value;
}

/* ************************************************************************* */

inline const Value& Symbol::getValue() const noexcept
{
    return m_value;
}

/* ************************************************************************* */

inline void Symbol::setValue(Value value) noexcept
{
    m_value = moveValue(value);
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

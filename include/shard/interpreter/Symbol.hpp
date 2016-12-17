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
#include "shard/interpreter/Value.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace interpreter {

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
     * @param      kind  The symbol kind.
     */
    explicit Symbol(SymbolKind kind);


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns the symbol kind.
     *
     * @return     The kind.
     */
    SymbolKind getKind() const noexcept
    {
        return m_kind;
    }


    /**
     * @brief      Returns the current value.
     *
     * @return     The value.
     */
    Value& getValue() noexcept
    {
        return m_value;
    }


    /**
     * @brief      Returns the current value.
     *
     * @return     The value.
     */
    const Value& getValue() const noexcept
    {
        return m_value;
    }


    /**
     * @brief      Returns the current value.
     *
     * @return     The value.
     */
    void setValue(Value value) noexcept
    {
        m_value = moveValue(value);
    }


// Private Data Members
private:

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

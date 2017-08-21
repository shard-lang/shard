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

// Declaration
#include "shard/interpreter/Scope.hpp"

// Shard
#include "shard/interpreter/Exception.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace interpreter {

/* ************************************************************************* */

Scope::Scope(ViewPtr<Scope> parent)
    : m_parent(parent)
{
    // Nothing to do
}

/* ************************************************************************* */

ViewPtr<Symbol> Scope::findSymbol(StringView name) noexcept
{
    auto it = m_symbols.find(String(name));

    if (it != m_symbols.end())
        return makeView(&(it->second));

    // Search in parent
    if (m_parent != nullptr)
        return m_parent->findSymbol(name);

    return nullptr;
}

/* ************************************************************************* */

ViewPtr<Symbol> Scope::addSymbol(String name, SymbolKind kind)
{
    auto it = m_symbols.find(name);

    if (it != m_symbols.end())
        throw Exception("Symbol already defined within this scope");

    auto res = m_symbols.emplace(moveValue(name), Symbol{this, kind});

    return makeView(&(res.first->second));
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

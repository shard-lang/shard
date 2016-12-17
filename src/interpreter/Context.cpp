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
#include "shard/interpreter/Context.hpp"

// Shard
#include "shard/Assert.hpp"
#include "shard/ast/Stmt.hpp"
#include "shard/ast/Expr.hpp"
#include "shard/interpreter/Exception.hpp"
#include "shard/interpreter/Function.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace interpreter {

/* ************************************************************************* */

Context::Context()
{
    push();

    auto print = addSymbol("print", SymbolKind::Function);
    SHARD_ASSERT(print);
    print->setValue(Function("print"));
}

/* ************************************************************************* */

void Context::push()
{
    m_scopes.emplace_back();
}

/* ************************************************************************* */

void Context::pop()
{
    m_scopes.pop_back();
}

/* ************************************************************************* */

ViewPtr<Symbol> Context::findSymbol(StringView name) noexcept
{
    for (auto it = m_scopes.rbegin(); it != m_scopes.rend(); ++it)
    {
        auto it2 = it->find(String(name));

        if (it2 != it->end())
            return makeView(&(it2->second));
    }

    return nullptr;
}

/* ************************************************************************* */

ViewPtr<Symbol> Context::addSymbol(StringView name, SymbolKind kind)
{
    auto it = m_scopes.back().find(String(name));

    if (it != m_scopes.back().end())
        throw Exception("Symbol already defined within this scope");

    auto res = m_scopes.back().emplace(String(name), Symbol{kind});

    return makeView(&(res.first->second));
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

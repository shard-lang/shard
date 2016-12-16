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
#include "shard/interpreter/Exception.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace interpreter {

/* ************************************************************************* */

Context::Context()
{
    push();
}

/* ************************************************************************* */

void Context::push()
{
    m_stack.emplace_back();
}

/* ************************************************************************* */

void Context::pop()
{
    m_stack.pop_back();
}

/* ************************************************************************* */

ViewPtr<Variable> Context::findVariable(StringView name) noexcept
{
    for (auto it = m_stack.rbegin(); it != m_stack.rend(); ++it)
    {
        auto it2 = it->find(String(name));

        if (it2 != it->end())
            return makeView(&(it2->second));
    }

    return nullptr;
}

/* ************************************************************************* */

ViewPtr<Variable> Context::createVariable(StringView name, ViewPtr<const ast::Type> type)
{
    auto it = m_stack.back().find(String(name));

    if (it != m_stack.back().end())
        throw Exception("Variable already defined within this scope");

    auto res = m_stack.back().emplace(String(name), Variable{type});

    return makeView(&(res.first->second));
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

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
#include "shard/ast/DeclContext.hpp"

// C++
#include <algorithm>

// Shard
#include "shard/ast/Decl.hpp"
#include "shard/ast/Expr.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

void DeclContext::removeDeclaration(ViewPtr<Decl> decl)
{
    m_declarations.erase(
        std::remove(m_declarations.begin(), m_declarations.end(), decl),
        m_declarations.end()
    );
}

/* ************************************************************************* */

ViewPtr<NamedDecl> DeclContext::findDeclaration(StringView name) const noexcept
{
    auto it = std::find_if(m_declarations.begin(), m_declarations.end(), [&name] (const auto& ptr) {
        if (NamedDecl::is(ptr))
            return NamedDecl::cast(ptr)->getName() == name;
        else
            return false;
    });

    // Found
    if (it != m_declarations.end())
        return NamedDecl::cast(*it);

    // Try parent
    if (m_parent)
        return m_parent->findDeclaration(name);

    // Not found
    return nullptr;
}

/* ************************************************************************* */

ViewPtr<const Type> DeclContext::findType(StringView type) const noexcept
{
    // TODO: implement
    return nullptr;
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

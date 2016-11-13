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

DeclContext::DeclContext(ViewPtr<DeclContext> parent) noexcept
    : m_parent(parent)
{
    // Nothing to do
}

/* ************************************************************************* */

DeclContext::~DeclContext() = default;

/* ************************************************************************* */

Decl& DeclContext::addDeclaration(UniquePtr<Decl> decl)
{
    m_declarations.push_back(moveValue(decl));
    return *m_declarations.back();
}

/* ************************************************************************* */

void DeclContext::removeDeclarations()
{
    m_declarations.clear();
}

/* ************************************************************************* */

void DeclContext::removeDeclaration(ViewPtr<Decl> decl)
{
    m_declarations.erase(
        std::remove_if(m_declarations.begin(), m_declarations.end(), [decl] (const auto& ptr) {
            return makeView(ptr) == decl;
        }),
        m_declarations.end()
    );
}

/* ************************************************************************* */

ViewPtr<NamedDecl> DeclContext::findDeclaration(StringView name) const noexcept
{
    auto it = std::find_if(m_declarations.begin(), m_declarations.end(), [&name] (const auto& ptr) {
        if (NamedDecl::is(makeView(ptr)))
            return NamedDecl::cast(makeView(ptr))->getName() == name;
        else
            return false;
    });

    // Found
    if (it != m_declarations.end())
        return NamedDecl::cast(makeView(*it));

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

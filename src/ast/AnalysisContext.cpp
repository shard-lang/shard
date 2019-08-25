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
#include "shard/ast/AnalysisContext.hpp"

// Shard
#include "shard/ast/Decl.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

void AnalysisContext::addDecl(ViewPtr<Decl> decl)
{
    m_declarations.emplace(decl->name(), decl);
}

/* ************************************************************************* */

ViewPtr<Decl> AnalysisContext::findDecl(const String& name) const
{
    auto it = m_declarations.find(name);

    if (it != m_declarations.end())
        return it->second;

    if (m_parent)
        return m_parent->findDecl(name);

    return nullptr;
}

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

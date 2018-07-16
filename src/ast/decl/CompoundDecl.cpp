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
#include "shard/ast/decl/CompoundDecl.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

CompoundDecl::CompoundDecl(DeclKind kind, String name, PtrDynamicArray<Decl> decls, SourceRange range)
    : Decl(kind, std::move(name), std::move(range))
    , m_declarations(std::move(decls))
{
    // Nothing to do
}

/* ************************************************************************* */

CompoundDecl::~CompoundDecl() = default;

/* ************************************************************************* */

void CompoundDecl::setDecls(PtrDynamicArray<Decl> decls)
{
    m_declarations = std::move(decls);
}

/* ************************************************************************* */

void CompoundDecl::addDecl(UniquePtr<Decl> decl)
{
    m_declarations.push_back(std::move(decl));
}

/* ************************************************************************* */

}

/* ************************************************************************* */

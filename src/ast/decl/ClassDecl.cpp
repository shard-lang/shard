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
#include "shard/ast/decl/ClassDecl.hpp"

// Shard
#include "shard/utility.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

ClassDecl::ClassDecl(String name, PtrVector<Decl> decls, SourceRange range)
    : CompoundDecl(Kind, std::move(name), std::move(decls), std::move(range))
{
    // Nothing to do
}

/* ************************************************************************* */

ClassDecl::~ClassDecl() = default;

/* ************************************************************************* */

UniquePtr<ClassDecl> ClassDecl::make(String name, PtrVector<Decl> decls, SourceRange range)
{
    return makeUnique<ClassDecl>(std::move(name), std::move(decls), std::move(range));
}

/* ************************************************************************* */

}

/* ************************************************************************* */

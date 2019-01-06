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
#include "shard/String.hpp"
#include "shard/ast/decl/CompoundDecl.hpp"
#include "shard/ast/utility.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

class NamespaceDecl;

/* ************************************************************************* */

using NamespaceDeclPtr = UniquePtr<NamespaceDecl>;

/* ************************************************************************* */

/**
 * @brief      Namespace declaration.
 */
class NamespaceDecl final
    : public CompoundDecl,
      public PtrBuilder<NamespaceDecl, String, DeclPtrVector>
{

    // Public Ctors & Dtors
public:
    /**
     * @brief      Constructor.
     *
     * @param      name   The class name.
     * @param      decls  The list of declarations.
     * @param      range  The declaration location within the source.
     */
    explicit NamespaceDecl(
        String name,
        DeclPtrVector decls = {},
        SourceRange range   = {})
        : CompoundDecl(std::move(name), std::move(decls), std::move(range))
    {
        // Nothing to do
    }
};

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

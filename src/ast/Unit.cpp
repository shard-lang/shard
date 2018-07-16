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
#include "shard/ast/Unit.hpp"

// Shard
#include "shard/ast/Expr.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

Unit::Unit(PtrVector<Decl> decls)
    : m_declarations(std::move(decls))
{
    // Nothing to do
}

/* ************************************************************************* */

Unit::~Unit() = default;

/* ************************************************************************* */

void Unit::setDeclarations(PtrVector<Decl> decls)
{
    m_declarations = std::move(decls);
}

/* ************************************************************************* */

void Unit::addDeclaration(UniquePtr<Decl> decl)
{
    m_declarations.push_back(std::move(decl));
}

/* ************************************************************************* */

}

/* ************************************************************************* */

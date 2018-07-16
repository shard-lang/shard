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
#include "shard/ast/stmt/DeclStmt.hpp"

// Shard
#include "shard/Assert.hpp"
#include "shard/ast/Decl.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

DeclStmt::DeclStmt(UniquePtr<Decl> decl, SourceRange range)
    : Stmt(Kind, range)
    , m_decl(std::move(decl))
{
    SHARD_ASSERT(m_decl);
}

/* ************************************************************************* */

DeclStmt::~DeclStmt() = default;

/* ************************************************************************* */

void DeclStmt::setDecl(UniquePtr<Decl> decl)
{
    SHARD_ASSERT(decl);
    m_decl = std::move(decl);
}

/* ************************************************************************* */

UniquePtr<DeclStmt> DeclStmt::make(UniquePtr<Decl> decl, SourceRange range)
{
    return makeUnique<DeclStmt>(std::move(decl), range);
}

/* ************************************************************************* */

}

/* ************************************************************************* */

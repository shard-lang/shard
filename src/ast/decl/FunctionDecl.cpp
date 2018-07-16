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
#include "shard/ast/decl/FunctionDecl.hpp"

// Shard
#include "shard/utility.hpp"
#include "shard/Assert.hpp"
#include "shard/ast/stmt/CompoundStmt.hpp"
#include "shard/ast/decl/VariableDecl.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

FunctionDecl::FunctionDecl(Type retType, String name, UniquePtr<CompoundStmt> bodyStmt,
    PtrVector<VariableDecl> params, SourceRange range)
    : Decl(Kind, std::move(name), std::move(range))
    , m_retType(std::move(retType))
    , m_parameters(std::move(params))
    , m_bodyStmt(std::move(bodyStmt))
{
    SHARD_ASSERT(m_bodyStmt);
}

/* ************************************************************************* */

FunctionDecl::~FunctionDecl() = default;

/* ************************************************************************* */

void FunctionDecl::setRetType(Type info)
{
    m_retType = std::move(info);
}

/* ************************************************************************* */

void FunctionDecl::setBodyStmt(UniquePtr<CompoundStmt> stmt)
{
    SHARD_ASSERT(stmt);
    m_bodyStmt = std::move(stmt);
}

/* ************************************************************************* */

void FunctionDecl::setParameters(PtrVector<VariableDecl> params)
{
    m_parameters = std::move(params);
}

/* ************************************************************************* */

UniquePtr<FunctionDecl> FunctionDecl::make(Type retType, String name, UniquePtr<CompoundStmt> bodyStmt,
        PtrVector<VariableDecl> params, SourceRange range)
{
    return makeUnique<FunctionDecl>(std::move(retType), std::move(name), std::move(bodyStmt), std::move(params), std::move(range));
}

/* ************************************************************************* */

}

/* ************************************************************************* */

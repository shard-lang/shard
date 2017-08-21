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

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

FunctionDecl::FunctionDecl(Type retType, String name, UniquePtr<CompoundStmt> bodyStmt,
    PtrDynamicArray<VariableDecl> params, SourceRange range)
    : Decl(Kind, moveValue(name), moveValue(range))
    , m_retType(moveValue(retType))
    , m_parameters(moveValue(params))
    , m_bodyStmt(moveValue(bodyStmt))
{
    SHARD_ASSERT(m_bodyStmt);
}

/* ************************************************************************* */

FunctionDecl::~FunctionDecl() = default;

/* ************************************************************************* */

void FunctionDecl::setRetType(Type info)
{
    m_retType = moveValue(info);
}

/* ************************************************************************* */

void FunctionDecl::setBodyStmt(UniquePtr<CompoundStmt> stmt)
{
    SHARD_ASSERT(stmt);
    m_bodyStmt = moveValue(stmt);
}

/* ************************************************************************* */

void FunctionDecl::setParameters(PtrDynamicArray<VariableDecl> params)
{
    m_parameters = moveValue(params);
}

/* ************************************************************************* */

UniquePtr<FunctionDecl> FunctionDecl::make(Type retType, String name, UniquePtr<CompoundStmt> bodyStmt,
        PtrDynamicArray<VariableDecl> params, SourceRange range)
{
    return makeUnique<FunctionDecl>(moveValue(retType), moveValue(name), moveValue(bodyStmt), moveValue(params), moveValue(range));
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

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
#include "shard/ast/stmt/CompoundStmt.hpp"

// Shard
#include "shard/ast/Stmt.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

CompoundStmt::CompoundStmt(PtrDynamicArray<Stmt> stmts, SourceRange range)
    : Stmt(Kind, range)
    , m_statements(std::move(stmts))
{
    // Nothing to do
}

/* ************************************************************************* */

CompoundStmt::~CompoundStmt() = default;

/* ************************************************************************* */

void CompoundStmt::setStmts(PtrDynamicArray<Stmt> stmts)
{
    m_statements = std::move(stmts);
}

/* ************************************************************************* */

void CompoundStmt::addStmt(UniquePtr<Stmt> stmt)
{
    m_statements.push_back(std::move(stmt));
}

/* ************************************************************************* */

UniquePtr<CompoundStmt> CompoundStmt::make(PtrDynamicArray<Stmt> stmts, SourceRange range)
{
    return makeUnique<CompoundStmt>(std::move(stmts), range);
}

/* ************************************************************************* */

}

/* ************************************************************************* */

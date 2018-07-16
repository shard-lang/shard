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
#include "shard/ast/stmt/DefaultStmt.hpp"

// Shard
#include "shard/Assert.hpp"
#include "shard/ast/Stmt.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

DefaultStmt::DefaultStmt(PtrDynamicArray<Stmt> stmts, SourceRange range)
    : Stmt(Kind, range)
    , m_statements(std::move(stmts))
{
    // Nothing to do
}

/* ************************************************************************* */

DefaultStmt::~DefaultStmt() = default;

/* ************************************************************************* */

void DefaultStmt::setStmts(PtrDynamicArray<Stmt> stmts)
{
    m_statements = std::move(stmts);
}

/* ************************************************************************* */

void DefaultStmt::addStmt(UniquePtr<Stmt> stmt)
{
    m_statements.push_back(std::move(stmt));
}

/* ************************************************************************* */

UniquePtr<DefaultStmt> DefaultStmt::make(PtrDynamicArray<Stmt> body, SourceRange range)
{
    return makeUnique<DefaultStmt>(std::move(body), range);
}

/* ************************************************************************* */

}

/* ************************************************************************* */

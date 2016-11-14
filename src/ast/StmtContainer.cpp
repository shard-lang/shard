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
#include "shard/ast/StmtContainer.hpp"

// Shard
#include "shard/utility.hpp"
#include "shard/ast/Stmt.hpp"
#include "shard/ast/Expr.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

StmtContainer::StmtContainer() noexcept = default;

/* ************************************************************************* */

StmtContainer::~StmtContainer() = default;

/* ************************************************************************* */

StmtContainer::StmtContainer(PtrDynamicArray<Stmt> stmts) noexcept
    : m_statements(moveValue(stmts))
{
    // Nothing to do
}

/* ************************************************************************* */

void StmtContainer::addStatement(UniquePtr<Stmt> stmt) noexcept
{
    m_statements.push_back(moveValue(stmt));
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

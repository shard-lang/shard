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
#include "shard/ast/expr/IdentifierExpr.hpp"

// Shard
#include "shard/utility.hpp"
#include "shard/Assert.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

IdentifierExpr::IdentifierExpr(String name, SourceRange range)
    : Expr(Kind, range)
    , m_name(moveValue(name))
{
    SHARD_ASSERT(!m_name.empty());
}

/* ************************************************************************* */

IdentifierExpr::~IdentifierExpr() = default;

/* ************************************************************************* */

void IdentifierExpr::setName(String name)
{
    SHARD_ASSERT(!name.empty());
    m_name = moveValue(name);
}

/* ************************************************************************* */

UniquePtr<IdentifierExpr> IdentifierExpr::make(String name, SourceRange range)
{
    return makeUnique<IdentifierExpr>(moveValue(name), moveValue(range));
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

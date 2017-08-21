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
#include "shard/ast/expr/MemberAccessExpr.hpp"

// Shard
#include "shard/utility.hpp"
#include "shard/Assert.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

MemberAccessExpr::MemberAccessExpr(UniquePtr<Expr> expr, String name, SourceRange range)
    : Expr(Kind, range)
    , m_expr(moveValue(expr))
    , m_name(moveValue(name))
{
    SHARD_ASSERT(!m_name.empty());
}

/* ************************************************************************* */

MemberAccessExpr::~MemberAccessExpr() = default;

/* ************************************************************************* */

void MemberAccessExpr::setExpr(UniquePtr<Expr> expr)
{
    SHARD_ASSERT(expr);
    m_expr = moveValue(expr);
}

/* ************************************************************************* */

void MemberAccessExpr::setName(String name)
{
    SHARD_ASSERT(!name.empty());
    m_name = moveValue(name);
}

/* ************************************************************************* */

UniquePtr<MemberAccessExpr> MemberAccessExpr::make(UniquePtr<Expr> expr, String name, SourceRange range)
{
    return makeUnique<MemberAccessExpr>(moveValue(expr), moveValue(name), moveValue(range));
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

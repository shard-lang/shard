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
#include "shard/ast/expr/SubscriptExpr.hpp"

// Shard
#include "shard/Assert.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

SubscriptExpr::SubscriptExpr(UniquePtr<Expr> expr, PtrDynamicArray<Expr> args, SourceRange range)
    : Expr(Kind, range)
    , m_expr(std::move(expr))
    , m_arguments(std::move(args))
{
    SHARD_ASSERT(m_expr);
}

/* ************************************************************************* */

SubscriptExpr::~SubscriptExpr() = default;

/* ************************************************************************* */

void SubscriptExpr::setExpr(UniquePtr<Expr> expr)
{
    SHARD_ASSERT(expr);
    m_expr = std::move(expr);
}

/* ************************************************************************* */

void SubscriptExpr::setArguments(PtrDynamicArray<Expr> args)
{
    m_arguments = std::move(args);
}

/* ************************************************************************* */

UniquePtr<SubscriptExpr> SubscriptExpr::make(UniquePtr<Expr> expr, PtrDynamicArray<Expr> args, SourceRange range)
{
    return makeUnique<SubscriptExpr>(std::move(expr), std::move(args), std::move(range));
}

/* ************************************************************************* */

}

/* ************************************************************************* */

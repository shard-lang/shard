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
#include "shard/ast/expr/TernaryExpr.hpp"

// Shard
#include "shard/utility.hpp"
#include "shard/Assert.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

TernaryExpr::TernaryExpr(UniquePtr<Expr> condExpr, UniquePtr<Expr> trueExpr, UniquePtr<Expr> falseExpr, SourceRange range)
    : Expr(Kind, range)
    , m_condExpr(moveValue(condExpr))
    , m_trueExpr(moveValue(trueExpr))
    , m_falseExpr(moveValue(falseExpr))
{
    // Nothing to do
}

/* ************************************************************************* */

TernaryExpr::~TernaryExpr() = default;

/* ************************************************************************* */

void TernaryExpr::setCondExpr(UniquePtr<Expr> expr)
{
    SHARD_ASSERT(expr);
    m_condExpr = moveValue(expr);
}

/* ************************************************************************* */

void TernaryExpr::setTrueExpr(UniquePtr<Expr> expr)
{
    SHARD_ASSERT(expr);
    m_trueExpr = moveValue(expr);
}

/* ************************************************************************* */

void TernaryExpr::setFalseExpr(UniquePtr<Expr> expr)
{
    SHARD_ASSERT(expr);
    m_falseExpr = moveValue(expr);
}

/* ************************************************************************* */

UniquePtr<TernaryExpr> TernaryExpr::make(UniquePtr<Expr> condExpr, UniquePtr<Expr> trueExpr, UniquePtr<Expr> falseExpr, SourceRange range)
{
    return makeUnique<TernaryExpr>(moveValue(condExpr), moveValue(trueExpr), moveValue(falseExpr), moveValue(range));
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

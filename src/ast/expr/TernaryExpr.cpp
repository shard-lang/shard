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
#include "shard/Assert.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

TernaryExpr::TernaryExpr(UniquePtr<Expr> condExpr, UniquePtr<Expr> trueExpr, UniquePtr<Expr> falseExpr, SourceRange range)
    : Expr(Kind, range)
    , m_condExpr(std::move(condExpr))
    , m_trueExpr(std::move(trueExpr))
    , m_falseExpr(std::move(falseExpr))
{
    // Nothing to do
}

/* ************************************************************************* */

TernaryExpr::~TernaryExpr() = default;

/* ************************************************************************* */

void TernaryExpr::setCondExpr(UniquePtr<Expr> expr)
{
    SHARD_ASSERT(expr);
    m_condExpr = std::move(expr);
}

/* ************************************************************************* */

void TernaryExpr::setTrueExpr(UniquePtr<Expr> expr)
{
    SHARD_ASSERT(expr);
    m_trueExpr = std::move(expr);
}

/* ************************************************************************* */

void TernaryExpr::setFalseExpr(UniquePtr<Expr> expr)
{
    SHARD_ASSERT(expr);
    m_falseExpr = std::move(expr);
}

/* ************************************************************************* */

UniquePtr<TernaryExpr> TernaryExpr::make(UniquePtr<Expr> condExpr, UniquePtr<Expr> trueExpr, UniquePtr<Expr> falseExpr, SourceRange range)
{
    return makeUnique<TernaryExpr>(std::move(condExpr), std::move(trueExpr), std::move(falseExpr), std::move(range));
}

/* ************************************************************************* */

}

/* ************************************************************************* */

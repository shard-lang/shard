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
#include "shard/ast/expr/IntLiteralExpr.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

IntLiteralExpr::IntLiteralExpr(ValueType value, SourceRange range) noexcept
    : LiteralExpr(Kind, value, range)
{
    // Nothing to do
}

/* ************************************************************************* */

IntLiteralExpr::~IntLiteralExpr() = default;

/* ************************************************************************* */

UniquePtr<IntLiteralExpr> IntLiteralExpr::make(ValueType value, SourceRange range)
{
    return makeUnique<IntLiteralExpr>(std::move(value), std::move(range));
}

/* ************************************************************************* */

}

/* ************************************************************************* */

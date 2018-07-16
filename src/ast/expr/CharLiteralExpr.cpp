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
#include "shard/ast/expr/CharLiteralExpr.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

CharLiteralExpr::CharLiteralExpr(ValueType value, SourceRange range) noexcept
    : LiteralExpr(Kind, value, range)
{
    // Nothing to do
}

/* ************************************************************************* */

CharLiteralExpr::~CharLiteralExpr() = default;

/* ************************************************************************* */

UniquePtr<CharLiteralExpr> CharLiteralExpr::make(ValueType value, SourceRange range)
{
    return makeUnique<CharLiteralExpr>(std::move(value), std::move(range));
}

/* ************************************************************************* */

}

/* ************************************************************************* */

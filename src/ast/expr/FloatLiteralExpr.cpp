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
#include "shard/ast/expr/FloatLiteralExpr.hpp"

// Shard
#include "shard/utility.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

FloatLiteralExpr::FloatLiteralExpr(ValueType value, SourceRange range) noexcept
    : NumberLiteralExpr(Kind, range)
    , m_value(value)
{
    // Nothing to do
}

/* ************************************************************************* */

FloatLiteralExpr::~FloatLiteralExpr() = default;

/* ************************************************************************* */

void FloatLiteralExpr::setValue(ValueType value)
{
    m_value = value;
}

/* ************************************************************************* */

UniquePtr<FloatLiteralExpr> FloatLiteralExpr::make(ValueType value, SourceRange range)
{
    return makeUnique<FloatLiteralExpr>(moveValue(value), moveValue(range));
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

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

#pragma once

/* ************************************************************************* */

// Shard
#include "shard/ast/Expr.hpp"
#include "shard/ast/utility.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

/**
 * @brief      The integer literal.
 */
class IntLiteralExpr final : public LiteralExpr<int>,
                             public PtrBuilder<IntLiteralExpr, int>
{
public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      value  Integer value.
     * @param      range  Location in source.
     */
    explicit IntLiteralExpr(int value, SourceRange range = {}) noexcept
        : LiteralExpr<int>(ExprKind::IntLiteral, value, range)
    {
        // Nothing to do
    }
};

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

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
 * @brief      The float literal.
 *
 * @details    In the language it represents a float literal like 0, 1.346,
 *             15e456. The value can be accessed by calling `getValue` and
 *             changed by `setValue`.
 */
class FloatLiteralExpr final : public LiteralExpr<float>,
                               public PtrBuilder<FloatLiteralExpr, float>
{
public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      value  The float value.
     * @param      range  Location in source.
     */
    explicit FloatLiteralExpr(float value, SourceRange range = {}) noexcept
        : LiteralExpr<float>(value, range)
    {
        // Nothing to do
    }
};

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

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
 * @brief      The character literal.
 *
 * @details    In the language it represents a character literal like '0', 'x',
 *             'á'. The value can be accessed by calling `value` and changed
 *             by `setValue`. Value is stored as a UNICODE code point.
 */
class CharLiteralExpr final : public LiteralExpr<char32_t>,
                              public PtrBuilder<CharLiteralExpr, char32_t>
{
public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      value  The character UNICODE code point.
     * @param      range  Location in source.
     */
    explicit CharLiteralExpr(char32_t value, SourceRange range = {}) noexcept
        : LiteralExpr<char32_t>(value, range)
    {
        // Nothing to do
    }

public:
    // Operations

    /**
     * @brief      Dump declaration to stream.
     *
     * @param      context  The context.
     */
    void dump(const DumpContext& context) const override;
};

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

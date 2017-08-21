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
#include "shard/UniquePtr.hpp"
#include "shard/ast/Expr.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

/**
 * @brief      The character literal.
 *
 * @details    In the language it represents a character literal like '0', 'x',
 *             'á'. The value can be accessed by calling `getValue` and changed
 *             by `setValue`. Value is stored as a UNICODE code point.
 */
class CharLiteralExpr final : public LiteralExpr<char32_t>
{

// Public Constants
public:


    /// Expression kind
    static constexpr ExprKind Kind = ExprKind::CharLiteral;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      value  The character UNICODE code point.
     * @param      range  Location in source.
     */
    explicit CharLiteralExpr(ValueType value, SourceRange range = {}) noexcept;


    /**
     * @brief      Destructor.
     */
    ~CharLiteralExpr();


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      value  The character UNICODE code point.
     * @param      range  Location in source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<CharLiteralExpr> make(ValueType value, SourceRange range = {});

};

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

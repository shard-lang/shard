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
 * @brief      The integer literal.
 *
 * @details    In the language it represents an integer literal like 0, 5624,
 *             0x12345. The value can be accessed by calling `getValue` and
 *             changed by `setValue`.
 */
class IntLiteralExpr final : public LiteralExpr<int>
{

// Public Constants
public:


    /// Expression kind
    static constexpr ExprKind Kind = ExprKind::IntLiteral;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      value  Integer value.
     * @param      range  Location in source.
     */
    explicit IntLiteralExpr(ValueType value, SourceRange range = {}) noexcept;


    /**
     * @brief      Destructor.
     */
    ~IntLiteralExpr();


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      value  Integer value.
     * @param      range  Location in source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<IntLiteralExpr> make(ValueType value, SourceRange range = {});

};

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

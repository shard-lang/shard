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

namespace shard::ast {

/* ************************************************************************* */

/**
 * @brief      The float literal.
 *
 * @details    In the language it represents a float literal like 0, 1.346,
 *             15e456. The value can be accessed by calling `getValue` and
 *             changed by `setValue`.
 */
class FloatLiteralExpr final : public LiteralExpr<float>
{

// Public Constants
public:


    /// Expression kind
    static constexpr ExprKind Kind = ExprKind::FloatLiteral;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      value  The float value.
     * @param      range  Location in source.
     */
    explicit FloatLiteralExpr(ValueType value, SourceRange range = {}) noexcept;


    /**
     * @brief      Destructor.
     */
    ~FloatLiteralExpr();


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      value  The float value.
     * @param      range  Location in source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<FloatLiteralExpr> make(ValueType value, SourceRange range = {});

};

/* ************************************************************************* */

}

/* ************************************************************************* */

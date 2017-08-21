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
 * @brief      Boolean literal.
 *
 * @details    In the language it represents `true` or `false` keyword. The
 *             value can be accessed by calling `getValue` and changed by
 *             `setValue`.
 */
class BoolLiteralExpr final : public LiteralExpr
{

// Public Constants
public:


    /// Expression kind
    static constexpr ExprKind Kind = ExprKind::BoolLiteral;


// Public Types
public:


    /// Boolean type.
    using ValueType = bool;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      value  The literal value, can be `true` or `false`.
     * @param      range  Location in source.
     */
    explicit BoolLiteralExpr(ValueType value, SourceRange range = {}) noexcept;


    /**
     * @brief      Destructor.
     */
    ~BoolLiteralExpr();


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns literal value.
     *
     * @return     Literal value.
     */
    ValueType getValue() const noexcept;


    /**
     * @brief      Change literal value.
     *
     * @param      value  The new literal value.
     */
    void setValue(ValueType value);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      value  The literal value, can be `true` or `false`.
     * @param      range  Location in source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<BoolLiteralExpr> make(ValueType value, SourceRange range = {});


// Private Data Members
private:

    /// Literal value.
    ValueType m_value;

};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

inline BoolLiteralExpr::ValueType BoolLiteralExpr::getValue() const noexcept
{
    return m_value;
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

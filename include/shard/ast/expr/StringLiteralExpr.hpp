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
#include "shard/String.hpp"
#include "shard/UniquePtr.hpp"
#include "shard/ast/Expr.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

/**
 * @brief      String literal.
 *
 * @details    In the language it represents a string literal like
 *             "hello world". The value can be accessed by calling `getValue`
 *             and changed by `setValue`.
 */
class StringLiteralExpr final : public LiteralExpr
{

// Public Constants
public:


    /// Expression kind
    static constexpr ExprKind Kind = ExprKind::StringLiteral;


// Public Types
public:


    /// String type.
    using ValueType = String;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      value  The string literal value.
     * @param      range  Location in source.
     */
    explicit StringLiteralExpr(ValueType value, SourceRange range = {});


    /**
     * @brief      Destructor.
     */
    ~StringLiteralExpr();


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns literal value.
     *
     * @return     Literal value.
     */
    const ValueType& getValue() const noexcept;


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
     * @param      value  The string literal value.
     * @param      range  Location in source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<StringLiteralExpr> make(ValueType value, SourceRange range = {});


// Private Data Members
private:

    /// Literal value.
    ValueType m_value;

};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

inline const StringLiteralExpr::ValueType& StringLiteralExpr::getValue() const noexcept
{
    return m_value;
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

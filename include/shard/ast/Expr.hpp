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

// C++
#include <utility>

// Shard
#include "shard/Assert.hpp"
#include "shard/UniquePtr.hpp"
#include "shard/ViewPtr.hpp"
#include "shard/ast/utility.hpp"
#include "shard/ast/Node.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

/**
 * @brief      Type of expression.
 */
enum class ExprKind
{
    NullLiteral,
    BoolLiteral,
    IntLiteral,
    FloatLiteral,
    CharLiteral,
    StringLiteral,
    Binary,
    Unary,
    Ternary,
    Paren,
    Identifier,
    FunctionCall,
    MemberAccess,
    Subscript,
};

/* ************************************************************************* */

/**
 * @brief      Base expression class.
 *
 * @details    An instance of this class cannot be created directly a child
 *             class must be created. Type of child class can be determined from
 *             ExprKind value obtained by calling `getKind`. Kind cannot be
 *             changed because it's bind to the child class.
 */
class Expr : public Node
{

// Public Ctors & Dtors
public:


    /**
     * @brief Destructor.
     */
    virtual ~Expr() = 0;


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns expression kind.
     *
     * @return     Expression kind.
     */
    ExprKind getKind() const noexcept;


// Public Operations
public:


    /**
     * @brief      Test if expression match required kind.
     *
     * @tparam     ExprType  Expression type.
     *
     * @return     Returns `true` if this is `ExprType`, `false` otherwise.
     */
    template<typename ExprType>
    bool is() const noexcept;


    /**
     * @brief      Cast this to required expression type.
     *
     * @tparam     ExprType  Expression type.
     *
     * @return     Reference to required expression type.
     */
    template<typename ExprType>
    ExprType& cast() noexcept;


    /**
     * @brief      Cast this to required expression type.
     *
     * @tparam     ExprType  Expression type.
     *
     * @return     Reference to required expression type.
     */
    template<typename ExprType>
    const ExprType& cast() const noexcept;


// Protected Ctors & Dtors
protected:


    /**
     * @brief      Constructor.
     *
     * @param      kind   Expression kind.
     * @param      range  Source range.
     */
    explicit Expr(ExprKind kind, SourceRange range) noexcept;


// Private Data Members
private:

    /// Expression kind.
    ExprKind m_kind;

};

/* ************************************************************************* */

/**
 * @brief      Base class for all literal kinds.
 */
template<typename ValueT>
class LiteralExpr : public Expr
{


// Public Types
public:


    /// Value type.
    using ValueType = ValueT;


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


// Protected Ctors & Dtors
protected:


    /**
     * @brief      Constructor.
     *
     * @param      kind   Expression kind.
     * @param      value  The literal value.
     * @param      range  Location in source.
     */
    explicit LiteralExpr(ExprKind kind, ValueType value, SourceRange range = {}) noexcept;


// Private Data Members
private:

    /// Literal value.
    ValueType m_value;

};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

inline ExprKind Expr::getKind() const noexcept
{
    return m_kind;
}

/* ************************************************************************* */

template<typename ExprType>
inline bool Expr::is() const noexcept
{
    return getKind() == ExprType::Kind;
}

/* ************************************************************************* */

template<typename ExprType>
inline ExprType& Expr::cast() noexcept
{
    SHARD_ASSERT(is<ExprType>());
    return static_cast<ExprType&>(*this);
}

/* ************************************************************************* */

template<typename ExprType>
inline const ExprType& Expr::cast() const noexcept
{
    SHARD_ASSERT(is<ExprType>());
    return static_cast<const ExprType&>(*this);
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

template<typename ValueT>
inline LiteralExpr<ValueT>::LiteralExpr(ExprKind kind, ValueType value, SourceRange range) noexcept
    : Expr(kind, range)
    , m_value(value)
{
    // Nothing to do
}

/* ************************************************************************* */

template<typename ValueT>
inline const typename LiteralExpr<ValueT>::ValueType& LiteralExpr<ValueT>::getValue() const noexcept
{
    return m_value;
}

/* ************************************************************************* */

template<typename ValueT>
inline void LiteralExpr<ValueT>::setValue(ValueType value)
{
    m_value = std::move(value);
}

/* ************************************************************************* */

}

/* ************************************************************************* */

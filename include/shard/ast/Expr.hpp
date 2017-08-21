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
#include "shard/Assert.hpp"
#include "shard/UniquePtr.hpp"
#include "shard/ViewPtr.hpp"
#include "shard/ast/utility.hpp"
#include "shard/ast/Node.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

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
    Literal_First       = NullLiteral,
    Literal_Last        = StringLiteral,
    NumberLiteral_First = IntLiteral,
    NumberLiteral_Last  = FloatLiteral,
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
 *
 * @details    It expression is a literal `expr.is<LiteralExpr>()` returns true.
 */
class LiteralExpr : public Expr
{

// Public Constants
public:


    /// Expression kind
    static constexpr KindRange<ExprKind> Kind{ExprKind::Literal_First, ExprKind::Literal_Last};


// Protected Ctors & Dtors
protected:


    using Expr::Expr;

};

/* ************************************************************************* */

/**
 * @brief      Base class for all number literals.
 */
class NumberLiteralExpr : public LiteralExpr
{

// Public Constants
public:


    /// Expression kind
    static constexpr KindRange<ExprKind> Kind{ExprKind::NumberLiteral_First, ExprKind::NumberLiteral_Last};


// Protected Ctors & Dtors
protected:


    using LiteralExpr::LiteralExpr;

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

}
}
}

/* ************************************************************************* */

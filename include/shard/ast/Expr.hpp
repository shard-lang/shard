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
#include "shard/PtrVector.hpp"
#include "shard/ast/Node.hpp"
#include "shard/ast/utility.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

/**
 * @brief      Type of expression.
 */
[[deprecated]] enum class ExprKind {
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

public:
    // Ctors & Dtors

    /**
     * @brief Destructor.
     */
    virtual ~Expr() = default;

public:
    // Accessors & Mutators

    /**
     * @brief      Returns expression kind.
     *
     * @return     Expression kind.
     */
    [[deprecated]] ExprKind getKind() const noexcept
    {
        return m_kind;
    }

protected:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      kind   Expression kind.
     * @param      range  Source range.
     */
    explicit Expr(ExprKind kind, SourceRange range) noexcept
        : Node(range)
        , m_kind(kind)
    {
        // Nothing to do
    }

private:
    // Data Members

    /// Expression kind.
    ExprKind m_kind;
};

/* ************************************************************************* */

/**
 * @brief      Base class for all literal kinds.
 *
 * @tparam     T     Literal value type.
 */
template<typename T>
class LiteralExpr : public Expr
{
public:
    // Types

    /// Value type.
    using Value = T;

    /// Value type.
    using ValueType [[deprecated]] = T;

public:
    // Accessors & Mutators

    /**
     * @brief      Returns the literal value.
     *
     * @return     The literal value.
     */
    const Value& value() const noexcept
    {
        return m_value;
    }

    /**
     * @brief      Returns the literal value.
     *
     * @return     The literal value.
     */
    [[deprecated]] const Value& getValue() const noexcept
    {
        return m_value;
    }

    /**
     * @brief      Change the literal value.
     *
     * @param      value  The new literal value.
     */
    void setValue(Value value)
    {
        m_value = std::move(value);
    }

protected:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      kind   Expression kind.
     * @param      value  The literal value.
     * @param      range  Location in source.
     */
    explicit LiteralExpr(
        ExprKind kind,
        Value value,
        SourceRange range = {}) noexcept
        : Expr(kind, range)
        , m_value(value)
    {
        // Nothing to do
    }

private:
    // Data Members

    /// Literal value.
    Value m_value;
};

/* ************************************************************************* */

/**
 * @brief A pointer to expression.
 */
using ExprPtr = UniquePtr<Expr>;

/* ************************************************************************* */

/**
 * @brief A vector of expressions.
 */
using ExprPtrVector = Vector<ExprPtr>;

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

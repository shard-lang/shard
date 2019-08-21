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
#include "shard/UniquePtr.hpp"
#include "shard/Vector.hpp"
#include "shard/ast/Node.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

class DumpContext;

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
    // Operations

    /**
     * @brief      Perform semantic analysis.
     *
     * @return     If AST is semantically valid.
     */
    virtual bool analyse()
    {
        return true;
    }

    /**
     * @brief      Dump declaration to stream.
     *
     * @param      context  The context.
     */
    virtual void dump(const DumpContext& context) const;

protected:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      kind   Expression kind.
     * @param      range  Source range.
     */
    explicit Expr(SourceRange range) noexcept
        : Node(range)
    {
        // Nothing to do
    }
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
    explicit LiteralExpr(Value value, SourceRange range = {}) noexcept
        : Expr(range)
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

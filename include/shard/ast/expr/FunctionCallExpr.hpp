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
#include "shard/ViewPtr.hpp"
#include "shard/PtrVector.hpp"
#include "shard/ast/Expr.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

/**
 * @brief      Function call expression.
 *
 * @details    In the source it represents following expression:
 *             `<expr>(<args>)`.
 */
class FunctionCallExpr final : public Expr
{

// Public Constants
public:


    /// Expression kind
    static constexpr ExprKind Kind = ExprKind::FunctionCall;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      expr   Callee expression.
     * @param      args   Call arguments.
     * @param      range  Location in source.
     */
    explicit FunctionCallExpr(UniquePtr<Expr> expr, PtrVector<Expr> args = {}, SourceRange range = {});


    /**
     * @brief      Destructor.
     */
    ~FunctionCallExpr();


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns callee expression.
     *
     * @return     The callee expression.
     */
    ViewPtr<const Expr> getExpr() const noexcept;


    /**
     * @brief      Returns callee expression.
     *
     * @return     The callee expression.
     */
    ViewPtr<Expr> getExpr() noexcept;


    /**
     * @brief      Change expression.
     *
     * @param      expr  The new expression.
     */
    void setExpr(UniquePtr<Expr> expr);


    /**
     * @brief      Returns call arguments.
     *
     * @return     The call arguments.
     */
    const PtrVector<Expr>& getArguments() const noexcept;


    /**
     * @brief      Change call arguments.
     *
     * @param      args  The call arguments.
     */
    void setArguments(PtrVector<Expr> args);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      expr   Callee expression.
     * @param      args   Call arguments.
     * @param      range  Location in source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<FunctionCallExpr> make(UniquePtr<Expr> expr, PtrVector<Expr> args = {}, SourceRange range = {});


// Private Data Members
private:

    /// Callee expression.
    UniquePtr<Expr> m_expr;

    /// Call arguments.
    PtrVector<Expr> m_arguments;

};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

inline ViewPtr<const Expr> FunctionCallExpr::getExpr() const noexcept
{
    return makeView(m_expr);
}

/* ************************************************************************* */

inline ViewPtr<Expr> FunctionCallExpr::getExpr() noexcept
{
    return makeView(m_expr);
}

/* ************************************************************************* */

inline const PtrVector<Expr>& FunctionCallExpr::getArguments() const noexcept
{
    return m_arguments;
}

/* ************************************************************************* */

}

/* ************************************************************************* */

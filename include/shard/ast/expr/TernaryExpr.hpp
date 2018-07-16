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
#include "shard/ViewPtr.hpp"
#include "shard/ast/Expr.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

/**
 * @brief      Ternary expression.
 *
 * @details    This expression is used for ternary operator: `<condExpr> ?
 *             <trueExpr> : <falseExpr>`.
 */
class TernaryExpr final : public Expr
{

// Public Constants
public:


    /// Expression kind
    static constexpr ExprKind Kind = ExprKind::Ternary;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      condExpr   Condition expression.
     * @param      trueExpr   Left operand expression.
     * @param      falseExpr  Right operand expression.
     * @param      range      Location in source.
     */
    explicit TernaryExpr(UniquePtr<Expr> condExpr, UniquePtr<Expr> trueExpr, UniquePtr<Expr> falseExpr, SourceRange range = {});


    /**
     * @brief      Destructor.
     */
    ~TernaryExpr();


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns condition expression.
     *
     * @return     Condition expression.
     */
    ViewPtr<const Expr> getCondExpr() const noexcept;


    /**
     * @brief      Returns condition expression.
     *
     * @return     Condition expression.
     */
    ViewPtr<Expr> getCondExpr() noexcept;


    /**
     * @brief      Change condition expression.
     *
     * @param      expr  The new expression.
     */
    void setCondExpr(UniquePtr<Expr> expr);


    /**
     * @brief      Returns true expression.
     *
     * @return     True expression.
     */
    ViewPtr<const Expr> getTrueExpr() const noexcept;


    /**
     * @brief      Returns true expression.
     *
     * @return     True expression.
     */
    ViewPtr<Expr> getTrueExpr() noexcept;


    /**
     * @brief      Change true branch expression.
     *
     * @param      expr  The new expression.
     */
    void setTrueExpr(UniquePtr<Expr> expr);


    /**
     * @brief      Returns false expression.
     *
     * @return     False expression.
     */
    ViewPtr<const Expr> getFalseExpr() const noexcept;


    /**
     * @brief      Returns false expression.
     *
     * @return     False expression.
     */
    ViewPtr<Expr> getFalseExpr() noexcept;


    /**
     * @brief      Change false branch expression.
     *
     * @param      expr  The new expression.
     */
    void setFalseExpr(UniquePtr<Expr> expr);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      condExpr   Condition expression.
     * @param      trueExpr   Left operand expression.
     * @param      falseExpr  Right operand expression.
     * @param      range      Location in source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<TernaryExpr> make(UniquePtr<Expr> condExpr, UniquePtr<Expr> trueExpr, UniquePtr<Expr> falseExpr, SourceRange range = {});


// Private Data Members
private:

    /// Condition expression.
    UniquePtr<Expr> m_condExpr;

    /// True expression.
    UniquePtr<Expr> m_trueExpr;

    /// False expression.
    UniquePtr<Expr> m_falseExpr;
};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

inline ViewPtr<const Expr> TernaryExpr::getCondExpr() const noexcept
{
    return makeView(m_condExpr);
}

/* ************************************************************************* */

inline ViewPtr<Expr> TernaryExpr::getCondExpr() noexcept
{
    return makeView(m_condExpr);
}

/* ************************************************************************* */

inline ViewPtr<const Expr> TernaryExpr::getTrueExpr() const noexcept
{
    return makeView(m_trueExpr);
}

/* ************************************************************************* */

inline ViewPtr<Expr> TernaryExpr::getTrueExpr() noexcept
{
    return makeView(m_trueExpr);
}

/* ************************************************************************* */

inline ViewPtr<const Expr> TernaryExpr::getFalseExpr() const noexcept
{
    return makeView(m_falseExpr);
}

/* ************************************************************************* */

inline ViewPtr<Expr> TernaryExpr::getFalseExpr() noexcept
{
    return makeView(m_falseExpr);
}

/* ************************************************************************* */

}

/* ************************************************************************* */

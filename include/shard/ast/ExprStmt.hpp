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
#include "shard/ast/Stmt.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

class Expr;

/* ************************************************************************* */

/**
 * @brief      Expression statement.
 *
 * @details    In the source it represents: `;` or `<expr>;`. When the `expr` is
 *             `nullptr` it's an empty statement.
 */
class ExprStmt final : public Stmt
{

// Public Constants
public:


    /// Expression kind
    static constexpr StmtKind Kind = StmtKind::Expr;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      expr   Expression.
     * @param      range  Source range.
     */
    explicit ExprStmt(UniquePtr<Expr> expr = nullptr, SourceRange range = {});


    /**
     * @brief      Destructor.
     */
    ~ExprStmt();


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns expression.
     *
     * @return     Expression.
     */
    ViewPtr<Expr> getExpr() noexcept;


    /**
     * @brief      Returns expression.
     *
     * @return     Expression.
     */
    ViewPtr<const Expr> getExpr() const noexcept;


    /**
     * @brief      Change the expression.
     *
     * @param      expr  The new expression.
     */
    void setExpr(UniquePtr<Expr> expr);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      expr   Expression.
     * @param      range  Source range.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<ExprStmt> make(UniquePtr<Expr> expr = nullptr, SourceRange range = {});


// Private Data Members
private:

    /// Expression.
    UniquePtr<Expr> m_expr;

};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

inline ViewPtr<Expr> ExprStmt::getExpr() noexcept
{
    return makeView(m_expr);
}

/* ************************************************************************* */

inline ViewPtr<const Expr> ExprStmt::getExpr() const noexcept
{
    return makeView(m_expr);
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

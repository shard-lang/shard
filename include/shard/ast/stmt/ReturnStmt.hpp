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
#include "shard/ast/utility.hpp"
#include "shard/ast/Stmt.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

/**
 * @brief Return statement.
 *
 * @details    In the source it appears as: `return <resExpr>;` or `return;`.
 */
class ReturnStmt final : public Stmt
{

// Public Constants
public:


    /// Expression kind
    static constexpr StmtKind Kind = StmtKind::Return;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      resExpr  Result expression.
     * @param      range    Source range.
     */
    explicit ReturnStmt(UniquePtr<Expr> resExpr = nullptr, SourceRange range = {});


    /**
     * @brief      Destructor.
     */
    ~ReturnStmt();


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns result expression.
     *
     * @return     Result expression.
     */
    ViewPtr<Expr> getResExpr() noexcept;


    /**
     * @brief      Returns result expression.
     *
     * @return     Result expression.
     */
    ViewPtr<const Expr> getResExpr() const noexcept;


    /**
     * @brief      Change result epxression.
     *
     * @param      expr  The new result expression.
     */
    void setResExpr(UniquePtr<Expr> expr);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      resExpr  Result expression.
     * @param      range    Source range.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<ReturnStmt> make(UniquePtr<Expr> resExpr = nullptr, SourceRange range = {});


// Private Data Members
private:

    /// Return expression.
    UniquePtr<Expr> m_resExpr;

};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

inline ViewPtr<Expr> ReturnStmt::getResExpr() noexcept
{
    return makeView(m_resExpr);
}

/* ************************************************************************* */

inline ViewPtr<const Expr> ReturnStmt::getResExpr() const noexcept
{
    return makeView(m_resExpr);
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

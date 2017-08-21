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
 * @brief      Null literal.
 *
 * @details    In the language it represents `null` keyword.
 */
class NullLiteralExpr final : public Expr
{

// Public Constants
public:


    /// Expression kind
    static constexpr ExprKind Kind = ExprKind::NullLiteral;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      range  Location in source.
     */
    explicit NullLiteralExpr(SourceRange range = {}) noexcept;


    /**
     * @brief      Destructor.
     */
    ~NullLiteralExpr();


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      range  Location in source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<NullLiteralExpr> make(SourceRange range = {});

};

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

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
 * @brief      Identifier expression - represents usage of variable, function or
 *             anything that can be declared.
 */
class IdentifierExpr final : public Expr
{

// Public Constants
public:


    /// Expression kind
    static constexpr ExprKind Kind = ExprKind::Identifier;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      name   Identifier name.
     * @param      range  Location in source.
     */
    explicit IdentifierExpr(String name, SourceRange range = {});


    /**
     * @brief      Destructor.
     */
    ~IdentifierExpr();


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns identifier name.
     *
     * @return     Identifier name.
     */
    const String& getName() const noexcept;


    /**
     * @brief      Change identifier name.
     *
     * @param      name  The new identifier name.
     */
    void setName(String name);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      name   Identifier name.
     * @param      range  Location in source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<IdentifierExpr> make(String name, SourceRange range = {});


// Private Data Members
private:

    /// Identifier name.
    String m_name;

};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

inline const String& IdentifierExpr::getName() const noexcept
{
    return m_name;
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

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
#include "shard/String.hpp"
#include "shard/ast/Expr.hpp"
#include "shard/ast/utility.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

/**
 * @brief      Identifier expression - represents usage of variable, function or
 *             anything that can be declared.
 */
class IdentifierExpr final : public Expr,
                             public PtrBuilder<IdentifierExpr, String>
{
public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      name   Identifier name.
     * @param      range  Location in source.
     */
    explicit IdentifierExpr(String name, SourceRange range = {})
        : Expr(ExprKind::Identifier, range)
        , m_name(std::move(name))
    {
        SHARD_ASSERT(!m_name.empty());
    }

    // Public Accessors & Mutators
public:
    /**
     * @brief      Returns identifier name.
     *
     * @return     Identifier name.
     */
    const String& name() const noexcept
    {
        return m_name;
    }

    /**
     * @brief      Returns identifier name.
     *
     * @return     Identifier name.
     */
    [[deprecated]] const String& getName() const noexcept
    {
        return m_name;
    }

    /**
     * @brief      Change identifier name.
     *
     * @param      name  The new identifier name.
     */
    void setName(String name)
    {
        SHARD_ASSERT(!name.empty());
        m_name = std::move(name);
    }

private:
    // Data Members

    /// Identifier name.
    String m_name;
};

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

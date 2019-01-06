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
#include "shard/ast/Decl.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

/**
 * @brief      Base class for declaration which are compound of other
 *             declarations (class, namespace, ...).
 */
class CompoundDecl : public Decl
{

public:
    // Accessors & Mutators

    /**
     * @brief      Returns declarations.
     *
     * @return     The declarations.
     */
    const DeclPtrVector& decls() const noexcept
    {
        return m_declarations;
    }

    /**
     * @brief      Set declarations.
     *
     * @param      decls  The declarations.
     */
    void setDecls(DeclPtrVector decls)
    {
        m_declarations = std::move(decls);
    }

    /**
     * @brief      Add declaration.
     *
     * @param      decl  The declaration to add.
     */
    void addDecl(DeclPtr decl)
    {
        m_declarations.push_back(std::move(decl));
    }

public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      name   The declaration name in local scope naming scheme.
     * @param      decls  The declarations.
     * @param      range  The declaration location within the source.
     */
    CompoundDecl(String name, DeclPtrVector decls, SourceRange range)
        : Decl(std::move(name), std::move(range))
        , m_declarations(std::move(decls))
    {
        // Nothing to do
    }

private:
    // Data Members

    /// Declarations
    DeclPtrVector m_declarations;
};

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

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
#include "shard/Map.hpp"
#include "shard/ViewPtr.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

class Decl;

/* ************************************************************************* */

/**
 * @brief      Helper class for semantic analysis of the AST.
 */
class AnalysisContext
{
public:
    // Operations

    /**
     * @brief      Create child context.
     *
     * @return     The context.
     */
    AnalysisContext push()
    {
        AnalysisContext context;
        context.m_parent = this;
        return context;
    }

    /**
     * @brief      Add new declaration.
     *
     * @param      decl  The declaration.
     */
    void addDecl(ViewPtr<Decl> decl);

    /**
     * @brief      Try to find declaration by name.
     *
     * @param      name  The name.
     *
     * @return     Declaration or nullptr.
     */
    ViewPtr<Decl> findDecl(const String& name) const;

private:
    // Data Members

    /// Parent context.
    ViewPtr<AnalysisContext> m_parent;

    /// Context declarations.
    Map<String, ViewPtr<Decl>> m_declarations;
};

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

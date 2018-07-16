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
#include "shard/utility.hpp"
#include "shard/ViewPtr.hpp"
#include "shard/ast/decl/FunctionDecl.hpp"

/* ************************************************************************* */

namespace shard::interpreter {

/* ************************************************************************* */

/**
 * @brief      Interpreter function description.
 */
class Function
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      name  The name
     * @param      decl  The declaration
     */
    explicit Function(String name, ViewPtr<const ast::FunctionDecl> decl = nullptr);


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns function name.
     *
     * @return     The name.
     */
    const String& getName() const noexcept;


    /**
     * @brief      Returns function declaration.
     *
     * @return     The declaration or nullptr.
     */
    ViewPtr<const ast::FunctionDecl> getDecl() const noexcept;


// Private Data Members
private:

    /// Function name.
    String m_name;

    /// Function declaration.
    ViewPtr<const ast::FunctionDecl> m_decl;

};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

inline Function::Function(String name, ViewPtr<const ast::FunctionDecl> decl)
    : m_name(moveValue(name))
    , m_decl(decl)
{
    // Nothing to do
}

/* ************************************************************************* */

inline const String& Function::getName() const noexcept
{
    return m_name;
}

/* ************************************************************************* */

inline ViewPtr<const ast::FunctionDecl> Function::getDecl() const noexcept
{
    return m_decl;
}

/* ************************************************************************* */

}

/* ************************************************************************* */

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
#include "shard/String.hpp"
#include "shard/PtrVector.hpp"
#include "shard/ast/decl/CompoundDecl.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

/**
 * @brief      Class declaration.
 *
 * @details    In the source it appears as: `class <name> { <decls> }`.
 */
class ClassDecl final : public CompoundDecl
{

// Public Constants
public:


    /// Declaration kind
    static constexpr DeclKind Kind = DeclKind::Class;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      name   The class name.
     * @param      decls  The list of declarations.
     * @param      range  The declaration location within the source.
     */
    explicit ClassDecl(String name, PtrVector<Decl> decls = {}, SourceRange range = {});


    /**
     * @brief      Destructor.
     */
    ~ClassDecl();


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      name   The class name.
     * @param      decls  The list of declarations.
     * @param      range  The declaration location within the source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<ClassDecl> make(String name, PtrVector<Decl> decls = {}, SourceRange range = {});

};

/* ************************************************************************* */

}

/* ************************************************************************* */

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
#include "shard/PtrDynamicArray.hpp"
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

// Public Ctors & Dtors
public:


    /**
     * @brief      Destructor.
     */
    ~CompoundDecl();


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns declarations.
     *
     * @return     The declarations.
     */
    const PtrDynamicArray<Decl>& getDecls() const noexcept;


    /**
     * @brief      Set declarations.
     *
     * @param      decls  The declarations.
     */
    void setDecls(PtrDynamicArray<Decl> decls);


    /**
     * @brief      Add declaration.
     *
     * @param      decl  The declaration to add.
     */
    void addDecl(UniquePtr<Decl> decl);


// Protected Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      kind   The declaration kind.
     * @param      name   The declaration name in local scope naming scheme.
     * @param      decls  The declarations.
     * @param      range  The declaration location within the source.
     */
    explicit CompoundDecl(DeclKind kind, String name, PtrDynamicArray<Decl> decls, SourceRange range);


// Private Data Members
private:

    /// Declarations
    PtrDynamicArray<Decl> m_declarations;

};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

inline const PtrDynamicArray<Decl>& CompoundDecl::getDecls() const noexcept
{
    return m_declarations;
}

/* ************************************************************************* */

}

/* ************************************************************************* */

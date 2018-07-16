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
#include "shard/PtrVector.hpp"
#include "shard/ast/Decl.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

/**
 * @brief      The compilation unit.
 */
class Unit
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      decls  The declarations.
     */
    explicit Unit(PtrVector<Decl> decls);


    /**
     * @brief      Destructor.
     */
    ~Unit();


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns declarations.
     *
     * @return     The declarations.
     */
    const PtrVector<Decl>& getDeclarations() const noexcept;


    /**
     * @brief      Set declarations.
     *
     * @param      decls  The declarations.
     */
    void setDeclarations(PtrVector<Decl> decls);


    /**
     * @brief      Add declaration.
     *
     * @param      decl  The declaration to add.
     */
    void addDeclaration(UniquePtr<Decl> decl);


// Private Data Members
private:

    /// Declarations
    PtrVector<Decl> m_declarations;

};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

inline const PtrVector<Decl>& Unit::getDeclarations() const noexcept
{
    return m_declarations;
}

/* ************************************************************************* */

}

/* ************************************************************************* */

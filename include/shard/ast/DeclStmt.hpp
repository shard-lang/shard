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
#include "shard/ast/Stmt.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

class Decl;

/* ************************************************************************* */

/**
 * @brief      Declaration statement.
 *
 * @details    Statement which declares a variable. In the source it appears as:
 *             `<decl>;`.
 */
class DeclStmt final : public Stmt
{

// Public Constants
public:


    /// Expression kind
    static constexpr StmtKind Kind = StmtKind::Decl;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      decl   Declaration.
     * @param      range  Source range.
     */
    explicit DeclStmt(UniquePtr<Decl> decl, SourceRange range = {});


    /**
     * @brief      Destructor.
     */
    ~DeclStmt();


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns declaration.
     *
     * @return     Declaration.
     */
    ViewPtr<Decl> getDecl() noexcept;


    /**
     * @brief      Returns declaration.
     *
     * @return     Declaration.
     */
    ViewPtr<const Decl> getDecl() const noexcept;

    /**
     * @brief      Change declaration.
     *
     * @param      decl  The new declaration.
     */
    void setDecl(UniquePtr<Decl> decl);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      decl   Declaration.
     * @param      range  Source range.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<DeclStmt> make(UniquePtr<Decl> decl, SourceRange range = {});


// Private Data Members
private:

    /// Declaration.
    UniquePtr<Decl> m_decl;

};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

inline ViewPtr<Decl> DeclStmt::getDecl() noexcept
{
    return makeView(m_decl);
}

/* ************************************************************************* */

inline ViewPtr<const Decl> DeclStmt::getDecl() const noexcept
{
    return makeView(m_decl);
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

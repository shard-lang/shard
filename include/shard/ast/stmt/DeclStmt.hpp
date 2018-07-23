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
#include "shard/ViewPtr.hpp"
#include "shard/ast/Decl.hpp"
#include "shard/ast/Stmt.hpp"
#include "shard/ast/utility.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

/**
 * @brief      Declaration statement.
 *
 * @details    Statement which declares a variable. In the source it appears as:
 *             `<decl>;`.
 */
class DeclStmt final : public Stmt, public PtrBuilder<DeclStmt, DeclPtr>
{
public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      decl   Declaration.
     * @param      range  Source range.
     */
    explicit DeclStmt(DeclPtr decl, SourceRange range = {})
        : Stmt(StmtKind::Decl, range)
        , m_decl(std::move(decl))
    {
        SHARD_ASSERT(m_decl);
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns declaration.
     *
     * @return     Declaration.
     */
    DeclPtr& decl() noexcept
    {
        return m_decl;
    }

    /**
     * @brief      Returns declaration.
     *
     * @return     Declaration.
     */
    const DeclPtr& decl() const noexcept
    {
        return m_decl;
    }

    /**
     * @brief      Returns declaration.
     *
     * @tparam     DeclType  Declaration type.
     *
     * @return     Declaration.
     *
     * @pre        `decl().is<DeclType>()`
     */
    template<typename DeclType>
    DeclType& decl() noexcept
    {
        return m_decl->cast<DeclType>();
    }

    /**
     * @brief      Returns declaration.
     *
     * @tparam     DeclType  Declaration type.
     *
     * @return     Declaration.
     *
     * @pre        `decl().is<DeclType>()`
     */
    template<typename DeclType>
    const DeclType& decl() const noexcept
    {
        return m_decl->cast<DeclType>();
    }

    /**
     * @brief      Returns declaration.
     *
     * @return     Declaration.
     */
    [[deprecated]] ViewPtr<Decl> getDecl() noexcept
    {
        return makeView(m_decl);
    }

    /**
     * @brief      Returns declaration.
     *
     * @return     Declaration.
     */
    [[deprecated]] ViewPtr<const Decl> getDecl() const noexcept
    {
        return makeView(m_decl);
    }

    /**
     * @brief      Change declaration.
     *
     * @param      decl  The new declaration.
     */
    void setDecl(DeclPtr decl)
    {
        SHARD_ASSERT(decl);
        m_decl = std::move(decl);
    }

private:
    // Data Members

    /// Declaration.
    DeclPtr m_decl;
};

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

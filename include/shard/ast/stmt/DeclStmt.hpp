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
#include "shard/ast/Decl.hpp"
#include "shard/ast/Stmt.hpp"
#include "shard/ast/utility.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

class DeclStmt;

/* ************************************************************************* */

using DeclStmtPtr = UniquePtr<DeclStmt>;

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
        : Stmt(range)
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
     * @tparam     DECL  Declaration type.
     *
     * @return     Declaration.
     *
     * @pre        `decl().is<DECL>()`
     */
    template<typename DECL>
    DECL& decl() noexcept
    {
        return m_decl->cast<DECL>();
    }

    /**
     * @brief      Returns declaration.
     *
     * @tparam     DECL  Declaration type.
     *
     * @return     Declaration.
     *
     * @pre        `decl().is<DECL>()`
     */
    template<typename DECL>
    const DECL& decl() const noexcept
    {
        return m_decl->cast<DECL>();
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

public:
    // Operations

    /**
     * @brief      Dump declaration to stream.
     *
     * @param      context  The context.
     */
    void dump(const DumpContext& context) const override;

private:
    // Data Members

    /// Declaration.
    DeclPtr m_decl;
};

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

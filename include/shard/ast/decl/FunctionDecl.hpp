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
#include "shard/String.hpp"
#include "shard/UniquePtr.hpp"
#include "shard/ast/Decl.hpp"
#include "shard/ast/Type.hpp"
#include "shard/ast/decl/VariableDecl.hpp"
#include "shard/ast/stmt/CompoundStmt.hpp"
#include "shard/ast/utility.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

class VariableDecl;
class CompoundStmt;

/* ************************************************************************* */

/**
 * @brief      Function declaration.
 *
 * @details    In the source it appears as: `<retType> <name> (<params>)
 * <bodyStmt>`.
 */
class FunctionDecl final : public Decl,
                           public PtrBuilder<
                               FunctionDecl,
                               Type,
                               String,
                               CompoundStmtPtr,
                               PtrVector<VariableDecl>>
{

public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      retType   The function return type.
     * @param      name      The function name.
     * @param      params    The function parameters.
     * @param      bodyStmt  The function body.
     * @param      range     The declaration location within the source.
     */
    FunctionDecl(
        Type retType,
        String name,
        CompoundStmtPtr bodyStmt,
        PtrVector<VariableDecl> params = {},
        SourceRange range              = {})
        : Decl(std::move(name), std::move(range))
        , m_retType(std::move(retType))
        , m_parameters(std::move(params))
        , m_bodyStmt(std::move(bodyStmt))
    {
        SHARD_ASSERT(m_bodyStmt);
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Return the function return type.
     *
     * @return     The function return type.
     */
    const Type& retType() const noexcept
    {
        return m_retType;
    }

    /**
     * @brief      Change the return type.
     *
     * @param      type  The return type.
     */
    void setRetType(Type type)
    {
        m_retType = type;
    }

    /**
     * @brief      Returns the function parameters.
     *
     * @return     A list of function parameters.
     */
    const PtrVector<VariableDecl>& parameters() const noexcept
    {
        return m_parameters;
    }

    /**
     * @brief      Change the function parameters.
     *
     * @param      params  The function parameters.
     */
    void setParameters(PtrVector<VariableDecl> params)
    {
        m_parameters = std::move(params);
    }

    /**
     * @brief      Returns the function body statement.
     *
     * @return     The function body compound statement.
     */
    const CompoundStmtPtr& bodyStmt() const noexcept
    {
        return m_bodyStmt;
    }

    /**
     * @brief      Change the function body.
     *
     * @param      stmt  The function body compound statement.
     */
    void setBodyStmt(CompoundStmtPtr stmt)
    {
        m_bodyStmt = std::move(stmt);
    }

private:
    // Data Members

    /// Return type.
    Type m_retType;

    /// Function parameters.
    PtrVector<VariableDecl> m_parameters;

    /// Function body.
    CompoundStmtPtr m_bodyStmt;
};

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

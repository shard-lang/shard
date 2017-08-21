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
#include "shard/String.hpp"
#include "shard/PtrDynamicArray.hpp"
#include "shard/ast/Decl.hpp"
#include "shard/ast/Type.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

class VariableDecl;
class CompoundStmt;

/* ************************************************************************* */

/**
 * @brief      Function declaration.
 *
 * @details    In the source it appears as: `<retType> <name> (<params>) <bodyStmt>`.
 */
class FunctionDecl final : public Decl
{

// Public Constants
public:


    /// Declaration kind
    static constexpr DeclKind Kind = DeclKind::Function;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      retType   The function return type.
     * @param      name      The function name.
     * @param      params    The function parameters.
     * @param      bodyStmt  The function body.
     * @param      range     The declaration location within the source.
     */
    explicit FunctionDecl(Type retType, String name, UniquePtr<CompoundStmt> bodyStmt,
        PtrDynamicArray<VariableDecl> params = {}, SourceRange range = {});


    /**
     * @brief      Destructor.
     */
    ~FunctionDecl();


// Public Accessors & Mutators
public:


    /**
     * @brief      Return the function return type.
     *
     * @return     The function return type.
     */
    const Type& getRetType() const noexcept;


    /**
     * @brief      Change the return type.
     *
     * @param      type  The return type.
     */
    void setRetType(Type type);


    /**
     * @brief      Returns the function parameters.
     *
     * @return     A list of function parameters.
     */
    const PtrDynamicArray<VariableDecl>& getParameters() const noexcept;


    /**
     * @brief      Change the function parameters.
     *
     * @param      params  The function parameters.
     */
    void setParameters(PtrDynamicArray<VariableDecl> params);


    /**
     * @brief      Returns the function body statement.
     *
     * @return     The function body compound statement.
     */
    ViewPtr<const CompoundStmt> getBodyStmt() const noexcept;


    /**
     * @brief      Returns the function body statement.
     *
     * @return     The function body compound statement.
     */
    ViewPtr<CompoundStmt> getBodyStmt() noexcept;


    /**
     * @brief      Change the function body.
     *
     * @param      stmt  The function body compound statement.
     */
    void setBodyStmt(UniquePtr<CompoundStmt> stmt);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      retType   The function return type.
     * @param      name      The function name.
     * @param      bodyStmt  The function body.
     * @param      params    The function parameters.
     * @param      range     The declaration location within the source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<FunctionDecl> make(Type retType, String name, UniquePtr<CompoundStmt> bodyStmt,
        PtrDynamicArray<VariableDecl> params = {}, SourceRange range = {});


// Private Data Members
private:

    /// Return type.
    Type m_retType;

    /// Function parameters.
    PtrDynamicArray<VariableDecl> m_parameters;

    /// Function body.
    UniquePtr<CompoundStmt> m_bodyStmt;
};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

inline const Type& FunctionDecl::getRetType() const noexcept
{
    return m_retType;
}

/* ************************************************************************* */

inline const PtrDynamicArray<VariableDecl>& FunctionDecl::getParameters() const noexcept
{
    return m_parameters;
}

/* ************************************************************************* */

inline ViewPtr<const CompoundStmt> FunctionDecl::getBodyStmt() const noexcept
{
    return makeView(m_bodyStmt);
}

/* ************************************************************************* */

inline ViewPtr<CompoundStmt> FunctionDecl::getBodyStmt() noexcept
{
    return makeView(m_bodyStmt);
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

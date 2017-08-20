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
#include "shard/UniquePtr.hpp"
#include "shard/ViewPtr.hpp"
#include "shard/PtrDynamicArray.hpp"
#include "shard/ast/utility.hpp"
#include "shard/ast/Node.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

class Expr;
class Decl;

/* ************************************************************************* */

/**
 * @brief      Statement kind.
 */
enum class StmtKind
{
    Expr,
    Decl,
    Compound,
    If,
    While,
    DoWhile,
    For,
    Switch,
    Case,
    Default,
    Continue,
    Break,
    Return
};

/* ************************************************************************* */

/**
 * @brief      Base statement class.
 */
class Stmt : public Node
{

// Public Ctors & Dtors
public:


    /**
     * @brief Destructor.
     */
    virtual ~Stmt() = 0;


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns statement kind.
     *
     * @return     Statement kind.
     */
    StmtKind getKind() const noexcept;


// Public Operations
public:


    /**
     * @brief      Test if statement match required kind.
     *
     * @tparam     StmtType  Statement type.
     *
     * @return     Returns `true` if this is `StmtType`, `false` otherwise.
     */
    template<typename StmtType>
    bool is() const noexcept;


    /**
     * @brief      Cast this to required statement type.
     *
     * @tparam     StmtType  Statement type.
     *
     * @return     Reference to required statement type.
     */
    template<typename StmtType>
    StmtType& cast() noexcept;


    /**
     * @brief      Cast this to required statement type.
     *
     * @tparam     StmtType  Statement type.
     *
     * @return     Reference to required statement type.
     */
    template<typename StmtType>
    const StmtType& cast() const noexcept;


// Protected Ctors & Dtors
protected:


    /**
     * @brief      Constructor.
     *
     * @param      kind   Statement kind.
     * @param      range  Source range.
     */
    explicit Stmt(StmtKind kind, SourceRange range);


// Private Data Members
private:

    /// Statement kind.
    StmtKind m_kind;

};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

inline StmtKind Stmt::getKind() const noexcept
{
    return m_kind;
}

/* ************************************************************************* */

template<typename StmtType>
inline bool Stmt::is() const noexcept
{
    return getKind() == StmtType::Kind;
}

/* ************************************************************************* */

template<typename StmtType>
inline StmtType& Stmt::cast() noexcept
{
    SHARD_ASSERT(is<StmtType>());
    return static_cast<StmtType&>(*this);
}

/* ************************************************************************* */

template<typename StmtType>
inline const StmtType& Stmt::cast() const noexcept
{
    SHARD_ASSERT(is<StmtType>());
    return static_cast<const StmtType&>(*this);
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

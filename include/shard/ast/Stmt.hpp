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
#include "shard/DynamicArray.hpp"
#include "shard/ast/utility.hpp"
#include "shard/ast/StmtContainer.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

class Expr;
class Decl;

/* ************************************************************************* */

/**
 * @brief Statement kind.
 */
enum class StmtKind
{
    Expr,
    Decl,
    Compound
};

/* ************************************************************************* */

/**
 * @brief Base statement class.
 */
class Stmt : public LocationInfo
{

// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param kind  Statement kind.
     * @param range Source range.
     */
    Stmt(StmtKind kind, SourceRange range) noexcept;


    /**
     * @brief Destructor.
     */
    virtual ~Stmt() = 0;


// Public Accessors & Mutators
public:


    /**
     * @brief Returns statement kind.
     * @return Statement kind.
     */
    StmtKind getKind() const noexcept
    {
        return m_kind;
    }


// Private Data Members
private:

    /// Statement kind.
    StmtKind m_kind;

};

/* ************************************************************************* */

/**
 * @brief Helper class for statement types.
 * @tparam KIND Tested statement type.
 * @tparam T    Class type.
 */
template<StmtKind KIND, typename T>
struct StmtHelper
    : public TypeHelper<StmtKind, KIND, Stmt>
    , public CastHelper<Stmt, T>
{
    // Nothing to do
};

/* ************************************************************************* */

/**
 * @brief Expression statement.
 */
class ExprStmt final
    : public Stmt
    , private StmtHelper<StmtKind::Expr, ExprStmt>
{

// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param expr  Expression.
     * @param range Source range.
     */
    explicit ExprStmt(UniquePtr<Expr> expr, SourceRange range = {}) noexcept;


// Public Accessors & Mutators
public:


    /**
     * @brief Returns expression.
     * @return Expression.
     */
    ViewPtr<const Expr> getExpr() const noexcept
    {
        return m_expr.get();
    }


// Public Operations
public:


    using StmtHelper<StmtKind::Expr, ExprStmt>::is;
    using StmtHelper<StmtKind::Expr, ExprStmt>::cast;


// Private Data Members
private:

    /// Expression.
    UniquePtr<Expr> m_expr;

};

/* ************************************************************************* */

/**
 * @brief Declaration statement.
 */
class DeclStmt final
    : public Stmt
    , private StmtHelper<StmtKind::Decl, DeclStmt>
{

// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param decl  Declaration.
     * @param range Source range.
     */
    explicit DeclStmt(UniquePtr<Decl> decl, SourceRange range = {}) noexcept;


    /**
     * @brief Destructor.
     */
    ~DeclStmt();


// Public Accessors & Mutators
public:


    /**
     * @brief Returns declaration.
     * @return Declaration.
     */
    ViewPtr<const Decl> getDecl() const noexcept
    {
        return m_decl.get();
    }


// Public Operations
public:


    using StmtHelper<StmtKind::Decl, DeclStmt>::is;
    using StmtHelper<StmtKind::Decl, DeclStmt>::cast;


// Private Data Members
private:

    /// Declaration.
    UniquePtr<Decl> m_decl;

};

/* ************************************************************************* */

/**
 * @brief Compound statement.
 */
class CompoundStmt
    : public Stmt
    , private StmtHelper<StmtKind::Compound, CompoundStmt>
    , public StmtContainer
{

// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param stmts A list of statements.
     * @param range Source range.
     */
    explicit CompoundStmt(DynamicArray<UniquePtr<Stmt>> stmts = {}, SourceRange range = {}) noexcept;


// Public Operations
public:


    using StmtHelper<StmtKind::Compound, CompoundStmt>::is;
    using StmtHelper<StmtKind::Compound, CompoundStmt>::cast;

};

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

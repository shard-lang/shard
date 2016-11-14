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
#include "shard/PtrDynamicArray.hpp"
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
    : public KindTester<StmtKind, KIND, Stmt>
    , public KindCaster<Stmt, T>
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
    explicit ExprStmt(UniquePtr<Expr> expr = nullptr, SourceRange range = {}) noexcept;


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
    explicit CompoundStmt(PtrDynamicArray<Stmt>> stmts = {}, SourceRange range = {}) noexcept;


// Public Operations
public:


    using StmtHelper<StmtKind::Compound, CompoundStmt>::is;
    using StmtHelper<StmtKind::Compound, CompoundStmt>::cast;

};

/* ************************************************************************* */

/**
 * @brief If branch statement.
 */
class IfStmt
    : public Stmt
    , private StmtHelper<StmtKind::If, IfStmt>
{

// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param condExpr Condition expression.
     * @param thenStmt Then branch statement.
     * @param elseStmt Else branch statement.
     * @param range    Source range.
     */
    explicit IfStmt(UniquePtr<Expr> condExpr, UniquePtr<Stmt> thenStmt, UniquePtr<Stmt> elseStmt = nullptr, SourceRange range = {}) noexcept;


// Public Accessors & Mutators
public:


    /**
     * @brief Return condition expression.
     * @return Condition expression.
     */
    ViewPtr<const Expr> getCondExpr() const noexcept
    {
        return m_condExpr.get();
    }


    /**
     * @brief Return then branch statement.
     * @return Then branch statement.
     */
    ViewPtr<const Stmt> getThenStmt() const noexcept
    {
        return m_thenStmt.get();
    }


    /**
     * @brief Return else branch statement.
     * @return Else branch statement.
     */
    ViewPtr<const Stmt> getElseStmt() const noexcept
    {
        return m_elseStmt.get();
    }


// Public Operations
public:


    using StmtHelper<StmtKind::If, IfStmt>::is;
    using StmtHelper<StmtKind::If, IfStmt>::cast;


// Private Data Members
private:

    /// Condition expression.
    UniquePtr<Expr> m_condExpr;

    /// Then branch statement.
    UniquePtr<Stmt> m_thenStmt;

    /// Else branch statement.
    UniquePtr<Stmt> m_elseStmt;

};

/* ************************************************************************* */

/**
 * @brief While loop statement.
 */
class WhileStmt
    : public Stmt
    , private StmtHelper<StmtKind::While, WhileStmt>
{

// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param condExpr  Condition expression.
     * @param bodyStmt  Body statement.
     * @param range     Source range.
     */
    explicit WhileStmt(UniquePtr<Expr> condExpr, UniquePtr<Stmt> bodyStmt, SourceRange range = {}) noexcept;


// Public Accessors & Mutators
public:


    /**
     * @brief Returns condition expression.
     * @return Expression.
     */
    ViewPtr<const Expr> getCondExpr() const noexcept
    {
        return m_condExpr.get();
    }


    /**
     * @brief Returns body statement.
     * @return Body statement.
     */
    ViewPtr<const Stmt> getBodyStmt() const noexcept
    {
        return m_bodyStmt.get();
    }


// Public Operations
public:


    using StmtHelper<StmtKind::While, WhileStmt>::is;
    using StmtHelper<StmtKind::While, WhileStmt>::cast;


// Private Data Members
private:

    /// Loop condition.
    UniquePtr<Expr> m_condExpr;

    /// Body statement.
    UniquePtr<Stmt> m_bodyStmt;

};

/* ************************************************************************* */

/**
 * @brief Do-while loop statement.
 */
class DoWhileStmt
    : public Stmt
    , private StmtHelper<StmtKind::DoWhile, DoWhileStmt>
{

// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param condExpr Condition expression.
     * @param bodyStmt Body statement.
     * @param range    Source range.
     */
    explicit DoWhileStmt(UniquePtr<Expr> condExpr, UniquePtr<CompoundStmt> bodyStmt, SourceRange range = {}) noexcept;


// Public Accessors & Mutators
public:


    /**
     * @brief Returns condition expression.
     * @return Expression.
     */
    ViewPtr<const Expr> getCondExpr() const noexcept
    {
        return m_condExpr.get();
    }


    /**
     * @brief Returns body statement.
     * @return Body statement.
     */
    ViewPtr<const CompoundStmt> getBodyStmt() const noexcept
    {
        return m_bodyStmt.get();
    }


// Public Operations
public:


    using StmtHelper<StmtKind::DoWhile, DoWhileStmt>::is;
    using StmtHelper<StmtKind::DoWhile, DoWhileStmt>::cast;


// Private Data Members
private:

    /// Loop condition.
    UniquePtr<Expr> m_condExpr;

    /// Body statement.
    UniquePtr<CompoundStmt> m_bodyStmt;

};

/* ************************************************************************* */

/**
 * @brief For loop statement.
 */
class ForStmt
    : public Stmt
    , private StmtHelper<StmtKind::For, ForStmt>
{

// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param initStmt Initialization statement.
     * @param condExpr Test expression.
     * @param incExpr  Increment statement.
     * @param bodyStmt Body statement.
     * @param range    Source range.
     */
    explicit ForStmt(UniquePtr<Stmt> initStmt, UniquePtr<Expr> condExpr, UniquePtr<Expr> incExpr, UniquePtr<Stmt> bodyStmt, SourceRange range = {}) noexcept;


// Public Accessors & Mutators
public:


    /**
     * @brief Returns initialization statement.
     * @return Initialization statement.
     */
    ViewPtr<const Stmt> getInitStmt() const noexcept
    {
        return m_initStmt.get();
    }


    /**
     * @brief Returns condition epxression.
     * @return Condition epxression.
     */
    ViewPtr<const Expr> getCondExpr() const noexcept
    {
        return m_condExpr.get();
    }


    /**
     * @brief Returns increment expression.
     * @return Increment expression.
     */
    ViewPtr<const Expr> getIncExpr() const noexcept
    {
        return m_incExpr.get();
    }


    /**
     * @brief Returns body statement.
     * @return Body statement.
     */
    ViewPtr<const Stmt> getBodyStmt() const noexcept
    {
        return m_bodyStmt.get();
    }


// Public Operations
public:


    using StmtHelper<StmtKind::For, ForStmt>::is;
    using StmtHelper<StmtKind::For, ForStmt>::cast;


// Private Data Members
private:

    /// Initialization statement.
    UniquePtr<Stmt> m_initStmt;

    /// Loop condition.
    UniquePtr<Expr> m_condExpr;

    /// Increment expression.
    UniquePtr<Expr> m_incExpr;

    /// Body statement.
    UniquePtr<Stmt> m_bodyStmt;

};

/* ************************************************************************* */

/**
 * @brief Switch branch statement.
 */
class SwitchStmt
    : public Stmt
    , private StmtHelper<StmtKind::Switch, SwitchStmt>
{

// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param condExpr Condition expression.
     * @param bodyStmt Body statement.
     * @param range    Source range.
     */
    explicit SwitchStmt(UniquePtr<Expr> condExpr, UniquePtr<CompoundStmt> bodyStmt, SourceRange range = {}) noexcept;


// Public Accessors & Mutators
public:


    /**
     * @brief Returns condition expression.
     * @return Condition expression.
     */
    ViewPtr<const Expr> getCondExpr() const noexcept
    {
        return m_condExpr.get();
    }


    /**
     * @brief Returns body statement.
     * @return Body statement.
     */
    ViewPtr<const CompoundStmt> getBodyStmt() const noexcept
    {
        return m_bodyStmt.get();
    }


// Public Operations
public:


    using StmtHelper<StmtKind::Switch, SwitchStmt>::is;
    using StmtHelper<StmtKind::Switch, SwitchStmt>::cast;


// Private Data Members
private:

    /// Switch expression.
    UniquePtr<Expr> m_condExpr;

    /// Body statement.
    UniquePtr<CompoundStmt> m_bodyStmt;

};

/* ************************************************************************* */

/**
 * @brief Case statement.
 */
class CaseStmt
    : public Stmt
    , private StmtHelper<StmtKind::Case, CaseStmt>
{

// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param expr  Test expression.
     * @param stmt  Body statement.
     * @param range Source range.
     */
    explicit CaseStmt(UniquePtr<Expr> expr, UniquePtr<Stmt> bodyStmt, SourceRange range = {}) noexcept;


// Public Accessors & Mutators
public:


    /**
     * @brief Returns condition expression.
     * @return Condition expression.
     */
    ViewPtr<const Expr> getExpr() const noexcept
    {
        return m_expr.get();
    }


    /**
     * @brief Returns body statement.
     * @return Body statement.
     */
    ViewPtr<const Stmt> getBodyStmt() const noexcept
    {
        return m_bodyStmt.get();
    }


// Public Operations
public:


    using StmtHelper<StmtKind::Case, CaseStmt>::is;
    using StmtHelper<StmtKind::Case, CaseStmt>::cast;


// Private Data Members
private:

    /// Case test expression.
    UniquePtr<Expr> m_expr;

    /// Body statement.
    UniquePtr<Stmt> m_bodyStmt;

};

/* ************************************************************************* */

/**
 * @brief Default statement.
 */
class DefaultStmt
    : public Stmt
    , private StmtHelper<StmtKind::Default, DefaultStmt>
{

// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param bodyStmt Body statement.
     * @param range    Source range.
     */
    explicit DefaultStmt(UniquePtr<Stmt> bodyStmt, SourceRange range = {}) noexcept;


// Public Accessors & Mutators
public:


    /**
     * @brief Returns body statement.
     * @return Body statement.
     */
    ViewPtr<const Stmt> getBodyStmt() const noexcept
    {
        return m_bodyStmt.get();
    }


// Public Operations
public:


    using StmtHelper<StmtKind::Default, DefaultStmt>::is;
    using StmtHelper<StmtKind::Default, DefaultStmt>::cast;


// Private Data Members
private:

    /// Body statement.
    UniquePtr<Stmt> m_bodyStmt;

};

/* ************************************************************************* */

/**
 * @brief Continue statement.
 */
class ContinueStmt
    : public Stmt
    , private StmtHelper<StmtKind::Continue, ContinueStmt>
{

// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param range Source range.
     */
    explicit ContinueStmt(SourceRange range = {}) noexcept;


// Public Operations
public:


    using StmtHelper<StmtKind::Continue, ContinueStmt>::is;
    using StmtHelper<StmtKind::Continue, ContinueStmt>::cast;

};

/* ************************************************************************* */

/**
 * @brief Break statement.
 */
class BreakStmt
    : public Stmt
    , private StmtHelper<StmtKind::Break, BreakStmt>
{

// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param range Source range.
     */
    explicit BreakStmt(SourceRange range = {}) noexcept;


// Public Operations
public:


    using StmtHelper<StmtKind::Break, BreakStmt>::is;
    using StmtHelper<StmtKind::Break, BreakStmt>::cast;

};

/* ************************************************************************* */

/**
 * @brief Return statement.
 */
class ReturnStmt
    : public Stmt
    , private StmtHelper<StmtKind::Return, ReturnStmt>
{

// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param resExpr Result expression.
     * @param range   Source range.
     */
    explicit ReturnStmt(UniquePtr<Expr> resExpr = nullptr, SourceRange range = {}) noexcept;


// Public Accessors & Mutators
public:


    /**
     * @brief Returns result expression.
     * @return Result expression.
     */
    ViewPtr<const Expr> getResExpr() const noexcept
    {
        return m_resExpr.get();
    }


// Public Operations
public:


    using StmtHelper<StmtKind::Return, ReturnStmt>::is;
    using StmtHelper<StmtKind::Return, ReturnStmt>::cast;


// Private Data Members
private:

    /// Return expression.
    UniquePtr<Expr> m_resExpr;

};

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

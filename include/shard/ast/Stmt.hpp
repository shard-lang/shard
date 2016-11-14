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
class Stmt : public LocationInfo
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
     * @brief Returns statement kind.
     * @return Statement kind.
     */
    StmtKind getKind() const noexcept
    {
        return m_kind;
    }


// Protected Ctors & Dtors
protected:


    /**
     * @brief      Constructor.
     *
     * @param      kind   Statement kind.
     * @param      range  Source range.
     */
    explicit Stmt(StmtKind kind, SourceRange range) noexcept;


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
    , public KindMaker<T>
{
    // Nothing to do
};

/* ************************************************************************* */

/**
 * @brief      Expression statement.
 *
 * @details    In the source it represents: `;` or `<expr>;`. When the `expr` is
 *             `nullptr` it's an empty statement.
 */
class ExprStmt final
    : public Stmt
    , private StmtHelper<StmtKind::Expr, ExprStmt>
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      expr   Expression.
     * @param      range  Source range.
     */
    explicit ExprStmt(UniquePtr<Expr> expr = nullptr, SourceRange range = {}) noexcept;


    /**
     * @brief      Destructor.
     */
    ~ExprStmt();


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns expression.
     *
     * @return     Expression.
     */
    ViewPtr<Expr> getExpr() noexcept
    {
        return makeView(m_expr);
    }


    /**
     * @brief      Returns expression.
     *
     * @return     Expression.
     */
    ViewPtr<const Expr> getExpr() const noexcept
    {
        return makeView(m_expr);
    }


    /**
     * @brief      Change the expression.
     *
     * @param      expr  The new expression.
     */
    void setExpr(UniquePtr<Expr> expr) noexcept;


// Public Operations
public:


    using StmtHelper<StmtKind::Expr, ExprStmt>::is;
    using StmtHelper<StmtKind::Expr, ExprStmt>::cast;
    using StmtHelper<StmtKind::Expr, ExprStmt>::make;


// Private Data Members
private:

    /// Expression.
    UniquePtr<Expr> m_expr;

};

/* ************************************************************************* */

/**
 * @brief      Declaration statement.
 *
 * @details    Statement which declares a variable. In the source it appears as:
 *             `<decl>;`.
 */
class DeclStmt final
    : public Stmt
    , private StmtHelper<StmtKind::Decl, DeclStmt>
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      decl   Declaration.
     * @param      range  Source range.
     */
    explicit DeclStmt(UniquePtr<Decl> decl, SourceRange range = {}) noexcept;


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
    ViewPtr<Decl> getDecl() noexcept
    {
        return makeView(m_decl);
    }


    /**
     * @brief      Returns declaration.
     *
     * @return     Declaration.
     */
    ViewPtr<const Decl> getDecl() const noexcept
    {
        return makeView(m_decl);
    }


    /**
     * @brief      Change declaration.
     *
     * @param      decl  The new declaration.
     */
    void setDecl(UniquePtr<Decl> decl) noexcept;


// Public Operations
public:


    using StmtHelper<StmtKind::Decl, DeclStmt>::is;
    using StmtHelper<StmtKind::Decl, DeclStmt>::cast;
    using StmtHelper<StmtKind::Decl, DeclStmt>::make;


// Private Data Members
private:

    /// Declaration.
    UniquePtr<Decl> m_decl;

};

/* ************************************************************************* */

/**
 * @brief      Compound statement.
 *
 * @details    It's a container for other statements. In the source is looks
 *             like this: `{ <stmts> }`.
 */
class CompoundStmt final
    : public Stmt
    , private StmtHelper<StmtKind::Compound, CompoundStmt>
    , public StmtContainer
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      stmts  A list of statements.
     * @param      range  Source range.
     */
    explicit CompoundStmt(PtrDynamicArray<Stmt> stmts = {}, SourceRange range = {}) noexcept;


// Public Operations
public:


    using StmtHelper<StmtKind::Compound, CompoundStmt>::is;
    using StmtHelper<StmtKind::Compound, CompoundStmt>::cast;
    using StmtHelper<StmtKind::Compound, CompoundStmt>::make;

};

/* ************************************************************************* */

/**
 * @brief      If branch statement.
 *
 * @details    In the source it appears as: `if (<condExpr>) <thenStmt>` or `if
 *             (<condExpr>) <thenStmt> else <elseStmt>`.
 */
class IfStmt final
    : public Stmt
    , private StmtHelper<StmtKind::If, IfStmt>
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      condExpr  Condition expression.
     * @param      thenStmt  Then branch statement.
     * @param      elseStmt  Else branch statement.
     * @param      range     Source range.
     */
    explicit IfStmt(UniquePtr<Expr> condExpr, UniquePtr<Stmt> thenStmt, UniquePtr<Stmt> elseStmt = nullptr, SourceRange range = {}) noexcept;


    /**
     * @brief      Destructor.
     */
    ~IfStmt();


// Public Accessors & Mutators
public:


    /**
     * @brief      Return condition expression.
     *
     * @return     Condition expression.
     */
    ViewPtr<Expr> getCondExpr() noexcept
    {
        return makeView(m_condExpr);
    }


    /**
     * @brief      Return condition expression.
     *
     * @return     Condition expression.
     */
    ViewPtr<const Expr> getCondExpr() const noexcept
    {
        return makeView(m_condExpr);
    }


    /**
     * @brief      Change condition expression.
     *
     * @param      expr  The new condition expression.
     */
    void setCondExpr(UniquePtr<Expr> expr) noexcept;


    /**
     * @brief      Return then branch statement.
     *
     * @return     Then branch statement.
     */
    ViewPtr<Stmt> getThenStmt() noexcept
    {
        return makeView(m_thenStmt);
    }


    /**
     * @brief      Return then branch statement.
     *
     * @return     Then branch statement.
     */
    ViewPtr<const Stmt> getThenStmt() const noexcept
    {
        return makeView(m_thenStmt);
    }


    /**
     * @brief      Change then branch statement.
     *
     * @param      stmt  The new then branch statement.
     */
    void setThenStmt(UniquePtr<Stmt> stmt) noexcept;


    /**
     * @brief      Return else branch statement.
     *
     * @return     Else branch statement.
     */
    ViewPtr<Stmt> getElseStmt() noexcept
    {
        return makeView(m_elseStmt);
    }


    /**
     * @brief      Return else branch statement.
     *
     * @return     Else branch statement.
     */
    ViewPtr<const Stmt> getElseStmt() const noexcept
    {
        return makeView(m_elseStmt);
    }


    /**
     * @brief      Change else branch statement.
     *
     * @param      stmt  The new else branch statement.
     */
    void setElseStmt(UniquePtr<Stmt> stmt) noexcept;


// Public Operations
public:


    using StmtHelper<StmtKind::If, IfStmt>::is;
    using StmtHelper<StmtKind::If, IfStmt>::cast;
    using StmtHelper<StmtKind::If, IfStmt>::make;


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
 * @brief      While loop statement.
 *
 * @details    In the source it appears as: `while (<condExpr>) <bodyStmt>`.
 */
class WhileStmt final
    : public Stmt
    , private StmtHelper<StmtKind::While, WhileStmt>
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      condExpr  Condition expression.
     * @param      bodyStmt  Body statement.
     * @param      range     Source range.
     */
    explicit WhileStmt(UniquePtr<Expr> condExpr, UniquePtr<Stmt> bodyStmt, SourceRange range = {}) noexcept;


    /**
     * @brief      Destructor.
     */
    ~WhileStmt();


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns condition expression.
     *
     * @return     Expression.
     */
    ViewPtr<Expr> getCondExpr() noexcept
    {
        return makeView(m_condExpr);
    }


    /**
     * @brief      Returns condition expression.
     *
     * @return     Expression.
     */
    ViewPtr<const Expr> getCondExpr() const noexcept
    {
        return makeView(m_condExpr);
    }


    /**
     * @brief      Change condition expression.
     *
     * @param      expr  The new condition expression.
     */
    void setCondExpr(UniquePtr<Expr> expr) noexcept;


    /**
     * @brief      Returns body statement.
     *
     * @return     Body statement.
     */
    ViewPtr<Stmt> getBodyStmt() noexcept
    {
        return makeView(m_bodyStmt);
    }


    /**
     * @brief      Returns body statement.
     *
     * @return     Body statement.
     */
    ViewPtr<const Stmt> getBodyStmt() const noexcept
    {
        return makeView(m_bodyStmt);
    }


    /**
     * @brief      Change body statement.
     *
     * @param      stmt  The new body statement.
     */
    void setBodyStmt(UniquePtr<Stmt> stmt) noexcept;


// Public Operations
public:


    using StmtHelper<StmtKind::While, WhileStmt>::is;
    using StmtHelper<StmtKind::While, WhileStmt>::cast;
    using StmtHelper<StmtKind::While, WhileStmt>::make;


// Private Data Members
private:

    /// Loop condition.
    UniquePtr<Expr> m_condExpr;

    /// Body statement.
    UniquePtr<Stmt> m_bodyStmt;

};

/* ************************************************************************* */

/**
 * @brief      Do-while loop statement.
 *
 * @details    In the source it appears as: `do <bodyStmt> while (<condExpr>);`.
 */
class DoWhileStmt final
    : public Stmt
    , private StmtHelper<StmtKind::DoWhile, DoWhileStmt>
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      condExpr  Condition expression.
     * @param      bodyStmt  Body statement.
     * @param      range     Source range.
     */
    explicit DoWhileStmt(UniquePtr<Expr> condExpr, UniquePtr<CompoundStmt> bodyStmt, SourceRange range = {}) noexcept;


    /**
     * @brief      Destructor.
     */
    ~DoWhileStmt();


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns condition expression.
     *
     * @return     Expression.
     */
    ViewPtr<Expr> getCondExpr() noexcept
    {
        return makeView(m_condExpr);
    }


    /**
     * @brief      Returns condition expression.
     *
     * @return     Expression.
     */
    ViewPtr<const Expr> getCondExpr() const noexcept
    {
        return makeView(m_condExpr);
    }


    /**
     * @brief      Change condition expression.
     *
     * @param      expr  The new condition expression.
     */
    void setCondExpr(UniquePtr<Expr> expr) noexcept;


    /**
     * @brief      Returns body statement.
     *
     * @return     Body statement.
     */
    ViewPtr<CompoundStmt> getBodyStmt() noexcept
    {
        return makeView(m_bodyStmt);
    }


    /**
     * @brief      Returns body statement.
     *
     * @return     Body statement.
     */
    ViewPtr<const CompoundStmt> getBodyStmt() const noexcept
    {
        return makeView(m_bodyStmt);
    }


    /**
     * @brief      Change body statement.
     *
     * @param      stmt  The new body statement.
     */
    void setBodyStmt(UniquePtr<CompoundStmt> stmt) noexcept;


// Public Operations
public:


    using StmtHelper<StmtKind::DoWhile, DoWhileStmt>::is;
    using StmtHelper<StmtKind::DoWhile, DoWhileStmt>::cast;
    using StmtHelper<StmtKind::DoWhile, DoWhileStmt>::make;


// Private Data Members
private:

    /// Loop condition.
    UniquePtr<Expr> m_condExpr;

    /// Body statement.
    UniquePtr<CompoundStmt> m_bodyStmt;

};

/* ************************************************************************* */

/**
 * @brief      For loop statement.
 *
 * @details    In the source it appears as: `for (<initStmt> <condExpr> ;
 *             <incExpr>) <bodyStmt>`.
 */
class ForStmt final
    : public Stmt
    , private StmtHelper<StmtKind::For, ForStmt>
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      initStmt  Initialization statement.
     * @param      condExpr  Test expression.
     * @param      incExpr   Increment statement.
     * @param      bodyStmt  Body statement.
     * @param      range     Source range.
     */
    explicit ForStmt(UniquePtr<Stmt> initStmt, UniquePtr<Expr> condExpr, UniquePtr<Expr> incExpr, UniquePtr<Stmt> bodyStmt, SourceRange range = {}) noexcept;


    /**
     * @brief      Destructor.
     */
    ~ForStmt();


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns initialization statement.
     *
     * @return     Initialization statement.
     */
    ViewPtr<Stmt> getInitStmt() noexcept
    {
        return makeView(m_initStmt);
    }


    /**
     * @brief      Returns initialization statement.
     *
     * @return     Initialization statement.
     */
    ViewPtr<const Stmt> getInitStmt() const noexcept
    {
        return makeView(m_initStmt);
    }


    /**
     * @brief      Change initialization statement.
     *
     * @param      stmt  THe new initialization statement.
     */
    void setInitStmt(UniquePtr<Stmt> stmt) noexcept;


    /**
     * @brief      Returns condition epxression.
     *
     * @return     Condition epxression.
     */
    ViewPtr<Expr> getCondExpr() noexcept
    {
        return makeView(m_condExpr);
    }


    /**
     * @brief      Returns condition epxression.
     *
     * @return     Condition epxression.
     */
    ViewPtr<const Expr> getCondExpr() const noexcept
    {
        return makeView(m_condExpr);
    }


    /**
     * @brief      Change condition epxression.
     *
     * @param      expr  The new condition epxression.
     */
    void setCondExpr(UniquePtr<Expr> expr) noexcept;


    /**
     * @brief      Returns increment expression.
     *
     * @return     Increment expression.
     */
    ViewPtr<Expr> getIncExpr() noexcept
    {
        return makeView(m_incExpr);
    }


    /**
     * @brief      Returns increment expression.
     *
     * @return     Increment expression.
     */
    ViewPtr<const Expr> getIncExpr() const noexcept
    {
        return makeView(m_incExpr);
    }


    /**
     * @brief      Change increment expression.
     *
     * @param      expr  The new increment expression.
     */
    void setIncExpr(UniquePtr<Expr> expr) noexcept;


    /**
     * @brief      Returns body statement.
     *
     * @return     Body statement.
     */
    ViewPtr<Stmt> getBodyStmt() noexcept
    {
        return makeView(m_bodyStmt);
    }


    /**
     * @brief      Returns body statement.
     *
     * @return     Body statement.
     */
    ViewPtr<const Stmt> getBodyStmt() const noexcept
    {
        return makeView(m_bodyStmt);
    }


    /**
     * @brief      Change body statement.
     *
     * @param      stmt  The new body statement.
     */
    void setBodyStmt(UniquePtr<Stmt> stmt) noexcept;


// Public Operations
public:


    using StmtHelper<StmtKind::For, ForStmt>::is;
    using StmtHelper<StmtKind::For, ForStmt>::cast;
    using StmtHelper<StmtKind::For, ForStmt>::make;


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
 * @brief      Switch branch statement.
 *
 * @details    In the source it appears as: `switch (<condExpr>) <bodyStmt>`.
 */
class SwitchStmt final
    : public Stmt
    , private StmtHelper<StmtKind::Switch, SwitchStmt>
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      condExpr  Condition expression.
     * @param      bodyStmt  Body statement.
     * @param      range     Source range.
     */
    explicit SwitchStmt(UniquePtr<Expr> condExpr, UniquePtr<CompoundStmt> bodyStmt, SourceRange range = {}) noexcept;


    /**
     * @brief      Destructor.
     */
    ~SwitchStmt();


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns condition expression.
     *
     * @return     Condition expression.
     */
    ViewPtr<Expr> getCondExpr() noexcept
    {
        return makeView(m_condExpr);
    }


    /**
     * @brief      Returns condition expression.
     *
     * @return     Condition expression.
     */
    ViewPtr<const Expr> getCondExpr() const noexcept
    {
        return makeView(m_condExpr);
    }


    /**
     * @brief      Change condition epxression.
     *
     * @param      expr  The new condition epxression.
     */
    void setCondExpr(UniquePtr<Expr> expr) noexcept;


    /**
     * @brief      Returns body statement.
     *
     * @return     Body statement.
     */
    ViewPtr<CompoundStmt> getBodyStmt() noexcept
    {
        return makeView(m_bodyStmt);
    }


    /**
     * @brief      Returns body statement.
     *
     * @return     Body statement.
     */
    ViewPtr<const CompoundStmt> getBodyStmt() const noexcept
    {
        return makeView(m_bodyStmt);
    }


    /**
     * @brief      Change body statement.
     *
     * @param      stmt  The new body statement.
     */
    void setBodyStmt(UniquePtr<CompoundStmt> stmt) noexcept;


// Public Operations
public:


    using StmtHelper<StmtKind::Switch, SwitchStmt>::is;
    using StmtHelper<StmtKind::Switch, SwitchStmt>::cast;
    using StmtHelper<StmtKind::Switch, SwitchStmt>::make;


// Private Data Members
private:

    /// Switch expression.
    UniquePtr<Expr> m_condExpr;

    /// Body statement.
    UniquePtr<CompoundStmt> m_bodyStmt;

};

/* ************************************************************************* */

/**
 * @brief      Case statement.
 *
 * @details    In the source it appears as: `case <expr>: <bodyStmt>`.
 */
class CaseStmt final
    : public Stmt
    , private StmtHelper<StmtKind::Case, CaseStmt>
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      expr      Test expression.
     * @param      bodyStmt  The body statement
     * @param      range     Source range.
     * @param      stmt  Body statement.
     */
    explicit CaseStmt(UniquePtr<Expr> expr, UniquePtr<Stmt> bodyStmt, SourceRange range = {}) noexcept;


    /**
     * @brief      Destructor.
     */
    ~CaseStmt();


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns condition expression.
     *
     * @return     Condition expression.
     */
    ViewPtr<Expr> getExpr() noexcept
    {
        return makeView(m_expr);
    }


    /**
     * @brief      Returns condition expression.
     *
     * @return     Condition expression.
     */
    ViewPtr<const Expr> getExpr() const noexcept
    {
        return makeView(m_expr);
    }


    /**
     * @brief      Change epxression.
     *
     * @param      expr  The new epxression.
     */
    void setExpr(UniquePtr<Expr> expr) noexcept;


    /**
     * @brief      Returns body statement.
     *
     * @return     Body statement.
     */
    ViewPtr<Stmt> getBodyStmt() noexcept
    {
        return makeView(m_bodyStmt);
    }


    /**
     * @brief      Returns body statement.
     *
     * @return     Body statement.
     */
    ViewPtr<const Stmt> getBodyStmt() const noexcept
    {
        return makeView(m_bodyStmt);
    }


    /**
     * @brief      Change body statement.
     *
     * @param      stmt  The new body statement.
     */
    void setBodyStmt(UniquePtr<Stmt> stmt) noexcept;


// Public Operations
public:


    using StmtHelper<StmtKind::Case, CaseStmt>::is;
    using StmtHelper<StmtKind::Case, CaseStmt>::cast;
    using StmtHelper<StmtKind::Case, CaseStmt>::make;


// Private Data Members
private:

    /// Case test expression.
    UniquePtr<Expr> m_expr;

    /// Body statement.
    UniquePtr<Stmt> m_bodyStmt;

};

/* ************************************************************************* */

/**
 * @brief      Default statement.
 *
 * @details    In the source it appears as: `default: <bodyStmt>`.
 */
class DefaultStmt final
    : public Stmt
    , private StmtHelper<StmtKind::Default, DefaultStmt>
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      bodyStmt  Body statement.
     * @param      range     Source range.
     */
    explicit DefaultStmt(UniquePtr<Stmt> bodyStmt, SourceRange range = {}) noexcept;


    /**
     * @brief      Destructor.
     */
    ~DefaultStmt();


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns body statement.
     *
     * @return     Body statement.
     */
    ViewPtr<Stmt> getBodyStmt() noexcept
    {
        return makeView(m_bodyStmt);
    }


    /**
     * @brief      Returns body statement.
     *
     * @return     Body statement.
     */
    ViewPtr<const Stmt> getBodyStmt() const noexcept
    {
        return makeView(m_bodyStmt);
    }


    /**
     * @brief      Change body statement.
     *
     * @param      stmt  The new body statement.
     */
    void setBodyStmt(UniquePtr<Stmt> stmt) noexcept;


// Public Operations
public:


    using StmtHelper<StmtKind::Default, DefaultStmt>::is;
    using StmtHelper<StmtKind::Default, DefaultStmt>::cast;
    using StmtHelper<StmtKind::Default, DefaultStmt>::make;


// Private Data Members
private:

    /// Body statement.
    UniquePtr<Stmt> m_bodyStmt;

};

/* ************************************************************************* */

/**
 * @brief      Continue statement.
 *
 * @details    In the source it appears as: `continue;`.
 */
class ContinueStmt final
    : public Stmt
    , private StmtHelper<StmtKind::Continue, ContinueStmt>
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      range  Source range.
     */
    explicit ContinueStmt(SourceRange range = {}) noexcept;


// Public Operations
public:


    using StmtHelper<StmtKind::Continue, ContinueStmt>::is;
    using StmtHelper<StmtKind::Continue, ContinueStmt>::cast;
    using StmtHelper<StmtKind::Continue, ContinueStmt>::make;

};

/* ************************************************************************* */

/**
 * @brief      Break statement.
 *
 * @details    In the source it appears as: `break;`.
 */
class BreakStmt final
    : public Stmt
    , private StmtHelper<StmtKind::Break, BreakStmt>
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      range  Source range.
     */
    explicit BreakStmt(SourceRange range = {}) noexcept;


// Public Operations
public:


    using StmtHelper<StmtKind::Break, BreakStmt>::is;
    using StmtHelper<StmtKind::Break, BreakStmt>::cast;
    using StmtHelper<StmtKind::Break, BreakStmt>::make;

};

/* ************************************************************************* */

/**
 * @brief Return statement.
 *
 * @details    In the source it appears as: `return <resExpr>;` or `return;`.
 */
class ReturnStmt final
    : public Stmt
    , private StmtHelper<StmtKind::Return, ReturnStmt>
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      resExpr  Result expression.
     * @param      range    Source range.
     */
    explicit ReturnStmt(UniquePtr<Expr> resExpr = nullptr, SourceRange range = {}) noexcept;


    /**
     * @brief      Destructor.
     */
    ~ReturnStmt();


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns result expression.
     *
     * @return     Result expression.
     */
    ViewPtr<Expr> getResExpr() noexcept
    {
        return makeView(m_resExpr);
    }


    /**
     * @brief      Returns result expression.
     *
     * @return     Result expression.
     */
    ViewPtr<const Expr> getResExpr() const noexcept
    {
        return makeView(m_resExpr);
    }


    /**
     * @brief      Change result epxression.
     *
     * @param      expr  The new result expression.
     */
    void setResExpr(UniquePtr<Expr> expr) noexcept;


// Public Operations
public:


    using StmtHelper<StmtKind::Return, ReturnStmt>::is;
    using StmtHelper<StmtKind::Return, ReturnStmt>::cast;
    using StmtHelper<StmtKind::Return, ReturnStmt>::make;


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

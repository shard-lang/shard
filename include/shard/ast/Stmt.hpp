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

/**
 * @brief      Expression statement.
 *
 * @details    In the source it represents: `;` or `<expr>;`. When the `expr` is
 *             `nullptr` it's an empty statement.
 */
class ExprStmt final : public Stmt
{

// Public Constants
public:


    /// Expression kind
    static constexpr StmtKind Kind = StmtKind::Expr;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      expr   Expression.
     * @param      range  Source range.
     */
    explicit ExprStmt(UniquePtr<Expr> expr = nullptr, SourceRange range = {});


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
    ViewPtr<Expr> getExpr() noexcept;


    /**
     * @brief      Returns expression.
     *
     * @return     Expression.
     */
    ViewPtr<const Expr> getExpr() const noexcept;


    /**
     * @brief      Change the expression.
     *
     * @param      expr  The new expression.
     */
    void setExpr(UniquePtr<Expr> expr);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      expr   Expression.
     * @param      range  Source range.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<ExprStmt> make(UniquePtr<Expr> expr = nullptr, SourceRange range = {});


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

/**
 * @brief      Compound statement.
 *
 * @details    It's a container for other statements. In the source is looks
 *             like this: `{ <stmts> }`.
 */
class CompoundStmt final : public Stmt
{

// Public Constants
public:


    /// Expression kind
    static constexpr StmtKind Kind = StmtKind::Compound;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      stmts  A list of statements.
     * @param      range  Source range.
     */
    explicit CompoundStmt(PtrDynamicArray<Stmt> stmts = {}, SourceRange range = {});


    /**
     * @brief      Destructor.
     */
    ~CompoundStmt();


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns the statements.
     *
     * @return     The statements.
     */
    const PtrDynamicArray<Stmt>& getStmts() const noexcept;


    /**
     * @brief      Change the statements.
     *
     * @param      stmt  The new statements.
     */
    void setStmts(PtrDynamicArray<Stmt> stmts);


    /**
     * @brief      Add statement to body statement list.
     *
     * @param      stmt  Statement to be added.
     */
    void addStmt(UniquePtr<Stmt> stmt);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      stmts  A list of statements.
     * @param      range  Source range.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<CompoundStmt> make(PtrDynamicArray<Stmt> stmts = {}, SourceRange range = {});


// Private Data Members
private:

    /// Case statements.
    PtrDynamicArray<Stmt> m_statements;

};

/* ************************************************************************* */

/**
 * @brief      If branch statement.
 *
 * @details    In the source it appears as: `if (<condExpr>) <thenStmt>` or `if
 *             (<condExpr>) <thenStmt> else <elseStmt>`.
 */
class IfStmt final : public Stmt
{

// Public Constants
public:


    /// Expression kind
    static constexpr StmtKind Kind = StmtKind::If;


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
    explicit IfStmt(UniquePtr<Expr> condExpr, UniquePtr<Stmt> thenStmt, UniquePtr<Stmt> elseStmt = nullptr, SourceRange range = {});


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
    ViewPtr<Expr> getCondExpr() noexcept;


    /**
     * @brief      Return condition expression.
     *
     * @return     Condition expression.
     */
    ViewPtr<const Expr> getCondExpr() const noexcept;


    /**
     * @brief      Change condition expression.
     *
     * @param      expr  The new condition expression.
     */
    void setCondExpr(UniquePtr<Expr> expr);


    /**
     * @brief      Return then branch statement.
     *
     * @return     Then branch statement.
     */
    ViewPtr<Stmt> getThenStmt() noexcept;


    /**
     * @brief      Return then branch statement.
     *
     * @return     Then branch statement.
     */
    ViewPtr<const Stmt> getThenStmt() const noexcept;


    /**
     * @brief      Change then branch statement.
     *
     * @param      stmt  The new then branch statement.
     */
    void setThenStmt(UniquePtr<Stmt> stmt);


    /**
     * @brief      Return else branch statement.
     *
     * @return     Else branch statement.
     */
    ViewPtr<Stmt> getElseStmt() noexcept;


    /**
     * @brief      Return else branch statement.
     *
     * @return     Else branch statement.
     */
    ViewPtr<const Stmt> getElseStmt() const noexcept;


    /**
     * @brief      Change else branch statement.
     *
     * @param      stmt  The new else branch statement.
     */
    void setElseStmt(UniquePtr<Stmt> stmt);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      condExpr  Condition expression.
     * @param      thenStmt  Then branch statement.
     * @param      elseStmt  Else branch statement.
     * @param      range     Source range.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<IfStmt> make(UniquePtr<Expr> condExpr, UniquePtr<Stmt> thenStmt, UniquePtr<Stmt> elseStmt = nullptr, SourceRange range = {});


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
class WhileStmt final : public Stmt
{

// Public Constants
public:


    /// Expression kind
    static constexpr StmtKind Kind = StmtKind::While;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      condExpr  Condition expression.
     * @param      bodyStmt  Body statement.
     * @param      range     Source range.
     */
    explicit WhileStmt(UniquePtr<Expr> condExpr, UniquePtr<Stmt> bodyStmt, SourceRange range = {}) ;


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
    ViewPtr<Expr> getCondExpr() noexcept;


    /**
     * @brief      Returns condition expression.
     *
     * @return     Expression.
     */
    ViewPtr<const Expr> getCondExpr() const noexcept;


    /**
     * @brief      Change condition expression.
     *
     * @param      expr  The new condition expression.
     */
    void setCondExpr(UniquePtr<Expr> expr);


    /**
     * @brief      Returns body statement.
     *
     * @return     Body statement.
     */
    ViewPtr<Stmt> getBodyStmt() noexcept;


    /**
     * @brief      Returns body statement.
     *
     * @return     Body statement.
     */
    ViewPtr<const Stmt> getBodyStmt() const noexcept;


    /**
     * @brief      Change body statement.
     *
     * @param      stmt  The new body statement.
     */
    void setBodyStmt(UniquePtr<Stmt> stmt);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      condExpr  Condition expression.
     * @param      bodyStmt  Body statement.
     * @param      range     Source range.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<WhileStmt> make(UniquePtr<Expr> condExpr, UniquePtr<Stmt> bodyStmt, SourceRange range = {});


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
class DoWhileStmt final : public Stmt
{

// Public Constants
public:


    /// Expression kind
    static constexpr StmtKind Kind = StmtKind::DoWhile;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      condExpr  Condition expression.
     * @param      bodyStmt  Body statement.
     * @param      range     Source range.
     */
    explicit DoWhileStmt(UniquePtr<Expr> condExpr, UniquePtr<CompoundStmt> bodyStmt, SourceRange range = {});


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
    ViewPtr<Expr> getCondExpr() noexcept;


    /**
     * @brief      Returns condition expression.
     *
     * @return     Expression.
     */
    ViewPtr<const Expr> getCondExpr() const noexcept;


    /**
     * @brief      Change condition expression.
     *
     * @param      expr  The new condition expression.
     */
    void setCondExpr(UniquePtr<Expr> expr);


    /**
     * @brief      Returns body statement.
     *
     * @return     Body statement.
     */
    ViewPtr<CompoundStmt> getBodyStmt() noexcept;


    /**
     * @brief      Returns body statement.
     *
     * @return     Body statement.
     */
    ViewPtr<const CompoundStmt> getBodyStmt() const noexcept;


    /**
     * @brief      Change body statement.
     *
     * @param      stmt  The new body statement.
     */
    void setBodyStmt(UniquePtr<CompoundStmt> stmt);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      condExpr  Condition expression.
     * @param      bodyStmt  Body statement.
     * @param      range     Source range.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<DoWhileStmt> make(UniquePtr<Expr> condExpr, UniquePtr<CompoundStmt> bodyStmt, SourceRange range = {});


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
class ForStmt final : public Stmt
{

// Public Constants
public:


    /// Expression kind
    static constexpr StmtKind Kind = StmtKind::For;


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
    explicit ForStmt(UniquePtr<Stmt> initStmt, UniquePtr<Expr> condExpr, UniquePtr<Expr> incExpr, UniquePtr<Stmt> bodyStmt, SourceRange range = {});


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
    ViewPtr<Stmt> getInitStmt() noexcept;


    /**
     * @brief      Returns initialization statement.
     *
     * @return     Initialization statement.
     */
    ViewPtr<const Stmt> getInitStmt() const noexcept;


    /**
     * @brief      Change initialization statement.
     *
     * @param      stmt  THe new initialization statement.
     */
    void setInitStmt(UniquePtr<Stmt> stmt);


    /**
     * @brief      Returns condition epxression.
     *
     * @return     Condition epxression.
     */
    ViewPtr<Expr> getCondExpr() noexcept;


    /**
     * @brief      Returns condition epxression.
     *
     * @return     Condition epxression.
     */
    ViewPtr<const Expr> getCondExpr() const noexcept;


    /**
     * @brief      Change condition epxression.
     *
     * @param      expr  The new condition epxression.
     */
    void setCondExpr(UniquePtr<Expr> expr);


    /**
     * @brief      Returns increment expression.
     *
     * @return     Increment expression.
     */
    ViewPtr<Expr> getIncExpr() noexcept;


    /**
     * @brief      Returns increment expression.
     *
     * @return     Increment expression.
     */
    ViewPtr<const Expr> getIncExpr() const noexcept;


    /**
     * @brief      Change increment expression.
     *
     * @param      expr  The new increment expression.
     */
    void setIncExpr(UniquePtr<Expr> expr);


    /**
     * @brief      Returns body statement.
     *
     * @return     Body statement.
     */
    ViewPtr<Stmt> getBodyStmt() noexcept;


    /**
     * @brief      Returns body statement.
     *
     * @return     Body statement.
     */
    ViewPtr<const Stmt> getBodyStmt() const noexcept;


    /**
     * @brief      Change body statement.
     *
     * @param      stmt  The new body statement.
     */
    void setBodyStmt(UniquePtr<Stmt> stmt);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      initStmt  Initialization statement.
     * @param      condExpr  Test expression.
     * @param      incExpr   Increment statement.
     * @param      bodyStmt  Body statement.
     * @param      range     Source range.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<ForStmt> make(UniquePtr<Stmt> initStmt, UniquePtr<Expr> condExpr, UniquePtr<Expr> incExpr, UniquePtr<Stmt> bodyStmt, SourceRange range = {});


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
class SwitchStmt final : public Stmt
{

// Public Constants
public:


    /// Expression kind
    static constexpr StmtKind Kind = StmtKind::Switch;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      condExpr  Condition expression.
     * @param      bodyStmt  Body statement.
     * @param      range     Source range.
     */
    explicit SwitchStmt(UniquePtr<Expr> condExpr, UniquePtr<CompoundStmt> bodyStmt, SourceRange range = {});


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
    ViewPtr<Expr> getCondExpr() noexcept;


    /**
     * @brief      Returns condition expression.
     *
     * @return     Condition expression.
     */
    ViewPtr<const Expr> getCondExpr() const noexcept;


    /**
     * @brief      Change condition epxression.
     *
     * @param      expr  The new condition epxression.
     */
    void setCondExpr(UniquePtr<Expr> expr);


    /**
     * @brief      Returns body statement.
     *
     * @return     Body statement.
     */
    ViewPtr<CompoundStmt> getBodyStmt() noexcept;


    /**
     * @brief      Returns body statement.
     *
     * @return     Body statement.
     */
    ViewPtr<const CompoundStmt> getBodyStmt() const noexcept;


    /**
     * @brief      Change body statement.
     *
     * @param      stmt  The new body statement.
     */
    void setBodyStmt(UniquePtr<CompoundStmt> stmt);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      condExpr  Condition expression.
     * @param      bodyStmt  Body statement.
     * @param      range     Source range.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<SwitchStmt> make(UniquePtr<Expr> condExpr, UniquePtr<CompoundStmt> bodyStmt, SourceRange range = {});


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
class CaseStmt final : public Stmt
{

// Public Constants
public:


    /// Expression kind
    static constexpr StmtKind Kind = StmtKind::Case;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      expr   The case expression.
     * @param      stmts  The statement list.
     * @param      range  Source range.
     */
    explicit CaseStmt(UniquePtr<Expr> expr, PtrDynamicArray<Stmt> stmts = {}, SourceRange range = {});


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
    ViewPtr<Expr> getExpr() noexcept;


    /**
     * @brief      Returns condition expression.
     *
     * @return     Condition expression.
     */
    ViewPtr<const Expr> getExpr() const noexcept;


    /**
     * @brief      Change expression.
     *
     * @param      expr  The new expression.
     */
    void setExpr(UniquePtr<Expr> expr);


    /**
     * @brief      Returns the statements.
     *
     * @return     The statements.
     */
    const PtrDynamicArray<Stmt>& getStmts() const noexcept;


    /**
     * @brief      Change the statements.
     *
     * @param      stmt  The new statements.
     */
    void setStmts(PtrDynamicArray<Stmt> stmts);


    /**
     * @brief      Add statement to body statement list.
     *
     * @param      stmt  Statement to be added.
     */
    void addStmt(UniquePtr<Stmt> stmt);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      expr   The case expression.
     * @param      stmts  The statement list.
     * @param      range  Source range.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<CaseStmt> make(UniquePtr<Expr> expr, PtrDynamicArray<Stmt> stmts = {}, SourceRange range = {});


// Private Data Members
private:

    /// Case test expression.
    UniquePtr<Expr> m_expr;

    /// The statements.
    PtrDynamicArray<Stmt> m_statements;

};

/* ************************************************************************* */

/**
 * @brief      Default statement.
 *
 * @details    In the source it appears as: `default: <bodyStmt>`.
 */
class DefaultStmt final : public Stmt
{

// Public Constants
public:


    /// Expression kind
    static constexpr StmtKind Kind = StmtKind::Default;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      body      Body statements.
     * @param      range     Source range.
     */
    explicit DefaultStmt(PtrDynamicArray<Stmt> body = {}, SourceRange range = {});


    /**
     * @brief      Destructor.
     */
    ~DefaultStmt();


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns the statements.
     *
     * @return     The statements.
     */
    const PtrDynamicArray<Stmt>& getStmts() const noexcept;


    /**
     * @brief      Change the statements.
     *
     * @param      stmt  The new statements.
     */
    void setStmts(PtrDynamicArray<Stmt> stmts);


    /**
     * @brief      Add statement to body statement list.
     *
     * @param      stmt  Statement to be added.
     */
    void addStmt(UniquePtr<Stmt> stmt);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      body      Body statements.
     * @param      range     Source range.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<DefaultStmt> make(PtrDynamicArray<Stmt> body = {}, SourceRange range = {});


// Private Data Members
private:

    /// The statements.
    PtrDynamicArray<Stmt> m_statements;

};

/* ************************************************************************* */

/**
 * @brief      Continue statement.
 *
 * @details    In the source it appears as: `continue;`.
 */
class ContinueStmt final : public Stmt
{

// Public Constants
public:


    /// Expression kind
    static constexpr StmtKind Kind = StmtKind::Continue;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      range  Source range.
     */
    explicit ContinueStmt(SourceRange range = {});


    /**
     * @brief      Destructor.
     */
    ~ContinueStmt();


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      range  Source range.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<ContinueStmt> make(SourceRange range = {});

};

/* ************************************************************************* */

/**
 * @brief      Break statement.
 *
 * @details    In the source it appears as: `break;`.
 */
class BreakStmt final : public Stmt
{

// Public Constants
public:


    /// Expression kind
    static constexpr StmtKind Kind = StmtKind::Break;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      range  Source range.
     */
    explicit BreakStmt(SourceRange range = {});


    /**
     * @brief      Destructor.
     */
    ~BreakStmt();


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      range  Source range.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<BreakStmt> make(SourceRange range = {});

};

/* ************************************************************************* */

/**
 * @brief Return statement.
 *
 * @details    In the source it appears as: `return <resExpr>;` or `return;`.
 */
class ReturnStmt final : public Stmt
{

// Public Constants
public:


    /// Expression kind
    static constexpr StmtKind Kind = StmtKind::Return;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      resExpr  Result expression.
     * @param      range    Source range.
     */
    explicit ReturnStmt(UniquePtr<Expr> resExpr = nullptr, SourceRange range = {});


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
    ViewPtr<Expr> getResExpr() noexcept;


    /**
     * @brief      Returns result expression.
     *
     * @return     Result expression.
     */
    ViewPtr<const Expr> getResExpr() const noexcept;


    /**
     * @brief      Change result epxression.
     *
     * @param      expr  The new result expression.
     */
    void setResExpr(UniquePtr<Expr> expr);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      resExpr  Result expression.
     * @param      range    Source range.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<ReturnStmt> make(UniquePtr<Expr> resExpr = nullptr, SourceRange range = {});


// Private Data Members
private:

    /// Return expression.
    UniquePtr<Expr> m_resExpr;

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

inline ViewPtr<Expr> ExprStmt::getExpr() noexcept
{
    return makeView(m_expr);
}

/* ************************************************************************* */

inline ViewPtr<const Expr> ExprStmt::getExpr() const noexcept
{
    return makeView(m_expr);
}

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

inline const PtrDynamicArray<Stmt>& CompoundStmt::getStmts() const noexcept
{
    return m_statements;
}

/* ************************************************************************* */

inline ViewPtr<Expr> IfStmt::getCondExpr() noexcept
{
    return makeView(m_condExpr);
}

/* ************************************************************************* */

inline ViewPtr<const Expr> IfStmt::getCondExpr() const noexcept
{
    return makeView(m_condExpr);
}

/* ************************************************************************* */

inline ViewPtr<Stmt> IfStmt::getThenStmt() noexcept
{
    return makeView(m_thenStmt);
}

/* ************************************************************************* */

inline ViewPtr<const Stmt> IfStmt::getThenStmt() const noexcept
{
    return makeView(m_thenStmt);
}

/* ************************************************************************* */

inline ViewPtr<Stmt> IfStmt::getElseStmt() noexcept
{
    return makeView(m_elseStmt);
}

/* ************************************************************************* */

inline ViewPtr<const Stmt> IfStmt::getElseStmt() const noexcept
{
    return makeView(m_elseStmt);
}

/* ************************************************************************* */

inline ViewPtr<Expr> WhileStmt::getCondExpr() noexcept
{
    return makeView(m_condExpr);
}

/* ************************************************************************* */

inline ViewPtr<const Expr> WhileStmt::getCondExpr() const noexcept
{
    return makeView(m_condExpr);
}

/* ************************************************************************* */

inline ViewPtr<Stmt> WhileStmt::getBodyStmt() noexcept
{
    return makeView(m_bodyStmt);
}

/* ************************************************************************* */

inline ViewPtr<const Stmt> WhileStmt::getBodyStmt() const noexcept
{
    return makeView(m_bodyStmt);
}

/* ************************************************************************* */

inline ViewPtr<Expr> DoWhileStmt::getCondExpr() noexcept
{
    return makeView(m_condExpr);
}

/* ************************************************************************* */

inline ViewPtr<const Expr> DoWhileStmt::getCondExpr() const noexcept
{
    return makeView(m_condExpr);
}

/* ************************************************************************* */

inline ViewPtr<CompoundStmt> DoWhileStmt::getBodyStmt() noexcept
{
    return makeView(m_bodyStmt);
}

/* ************************************************************************* */

inline ViewPtr<const CompoundStmt> DoWhileStmt::getBodyStmt() const noexcept
{
    return makeView(m_bodyStmt);
}

/* ************************************************************************* */

inline ViewPtr<Stmt> ForStmt::getInitStmt() noexcept
{
    return makeView(m_initStmt);
}

/* ************************************************************************* */

inline ViewPtr<const Stmt> ForStmt::getInitStmt() const noexcept
{
    return makeView(m_initStmt);
}

/* ************************************************************************* */

inline ViewPtr<Expr> ForStmt::getCondExpr() noexcept
{
    return makeView(m_condExpr);
}

/* ************************************************************************* */

inline ViewPtr<const Expr> ForStmt::getCondExpr() const noexcept
{
    return makeView(m_condExpr);
}

/* ************************************************************************* */

inline ViewPtr<Expr> ForStmt::getIncExpr() noexcept
{
    return makeView(m_incExpr);
}

/* ************************************************************************* */

inline ViewPtr<const Expr> ForStmt::getIncExpr() const noexcept
{
    return makeView(m_incExpr);
}

/* ************************************************************************* */

inline ViewPtr<Stmt> ForStmt::getBodyStmt() noexcept
{
    return makeView(m_bodyStmt);
}

/* ************************************************************************* */

inline ViewPtr<const Stmt> ForStmt::getBodyStmt() const noexcept
{
    return makeView(m_bodyStmt);
}

/* ************************************************************************* */

inline ViewPtr<Expr> SwitchStmt::getCondExpr() noexcept
{
    return makeView(m_condExpr);
}

/* ************************************************************************* */

inline ViewPtr<const Expr> SwitchStmt::getCondExpr() const noexcept
{
    return makeView(m_condExpr);
}

/* ************************************************************************* */

inline ViewPtr<CompoundStmt> SwitchStmt::getBodyStmt() noexcept
{
    return makeView(m_bodyStmt);
}

/* ************************************************************************* */

inline ViewPtr<const CompoundStmt> SwitchStmt::getBodyStmt() const noexcept
{
    return makeView(m_bodyStmt);
}

/* ************************************************************************* */

inline ViewPtr<Expr> CaseStmt::getExpr() noexcept
{
    return makeView(m_expr);
}

/* ************************************************************************* */

inline ViewPtr<const Expr> CaseStmt::getExpr() const noexcept
{
    return makeView(m_expr);
}

/* ************************************************************************* */

inline const PtrDynamicArray<Stmt>& CaseStmt::getStmts() const noexcept
{
    return m_statements;
}

/* ************************************************************************* */

inline const PtrDynamicArray<Stmt>& DefaultStmt::getStmts() const noexcept
{
    return m_statements;
}

/* ************************************************************************* */

inline ViewPtr<Expr> ReturnStmt::getResExpr() noexcept
{
    return makeView(m_resExpr);
}

/* ************************************************************************* */

inline ViewPtr<const Expr> ReturnStmt::getResExpr() const noexcept
{
    return makeView(m_resExpr);
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

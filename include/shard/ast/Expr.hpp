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
#include "shard/Assert.hpp"
#include "shard/String.hpp"
#include "shard/StringView.hpp"
#include "shard/SourceRange.hpp"
#include "shard/UniquePtr.hpp"
#include "shard/ViewPtr.hpp"
#include "shard/PtrDynamicArray.hpp"
#include "shard/ast/utility.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

/**
 * @brief Type of expression.
 */
enum class ExprKind
{
    NullLiteral,
    BoolLiteral,
    IntLiteral,
    FloatLiteral,
    CharLiteral,
    StringLiteral,
    Binary,
    Unary,
    Ternary,
    Paren,
    Identifier,
    FunctionCall,
    MemberAccess,
    Subscript,
    Literal_First       = NullLiteral,
    Literal_Last        = StringLiteral,
    NumberLiteral_First = IntLiteral,
    NumberLiteral_Last  = FloatLiteral,
};

/* ************************************************************************* */

/**
 * @brief      Base expression class.
 *
 * @details    An instance of this class cannot be created directly a child
 *             class must be created. Type of child class can be determined from
 *             ExprKind value obtained by calling `getKind`. Kind cannot be
 *             changed because it's bind to the child class.
 */
class Expr : public LocationInfo
{


// Public Ctors & Dtors
public:


    /**
     * @brief Destructor.
     */
    virtual ~Expr() = 0;


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns expression kind.
     *
     * @return     Expression kind.
     */
    ExprKind getKind() const noexcept
    {
        return m_kind;
    }


// Protected Ctors & Dtors
protected:


    /**
     * @brief      Constructor.
     *
     * @param      kind   Expression kind.
     * @param      range  Source range.
     */
    explicit Expr(ExprKind kind, SourceRange range) noexcept;


// Private Data Members
private:

    /// Expression kind.
    ExprKind m_kind;

};

/* ************************************************************************* */

/**
 * @brief Helper class for expression kinds.
 * @tparam KIND Tested expression kind.
 * @tparam T    Class type.
 */
template<ExprKind KIND, typename T>
struct ExprHelper
    : public KindTester<ExprKind, KIND, Expr>
    , public KindCaster<Expr, T>
    , public KindMaker<T>
{
    // Nothing to do
};

/* ************************************************************************* */

/**
 * @brief Helper class for declaration kinds.
 * @tparam KIND1 The first tested declaration kind.
 * @tparam KIND2 The last tested declaration kind.
 * @tparam T     Class type.
 */
template<ExprKind KIND1, ExprKind KIND2, typename T>
struct ExprRangeHelper
    : public KindRangeTester<ExprKind, KIND1, KIND2, Expr>
    , public KindCaster<Expr, T>
    , public KindMaker<T>
{
    // Nothing to do
};

/* ************************************************************************* */

/**
 * @brief      Base class for all literal kinds.
 *
 * @details    It expression is a literal `LiteralExpr::is(expr)` returns true.
 */
class LiteralExpr
    : public Expr
    , private ExprRangeHelper<ExprKind::Literal_First, ExprKind::Literal_Last, LiteralExpr>
{


// Public Operations
public:


    using ExprRangeHelper<ExprKind::Literal_First, ExprKind::Literal_Last, LiteralExpr>::is;
    using ExprRangeHelper<ExprKind::Literal_First, ExprKind::Literal_Last, LiteralExpr>::cast;
    using ExprRangeHelper<ExprKind::Literal_First, ExprKind::Literal_Last, LiteralExpr>::make;


// Protected Ctors & Dtors
protected:


    using Expr::Expr;

};

/* ************************************************************************* */

/**
 * @brief      Null literal.
 *
 * @details    In the language it represents `null` keyword.
 */
class NullLiteralExpr final
    : public LiteralExpr
    , private ExprHelper<ExprKind::NullLiteral, NullLiteralExpr>
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      range  Location in source.
     */
    explicit NullLiteralExpr(SourceRange range = {}) noexcept;


// Public Operations
public:


    using ExprHelper<ExprKind::NullLiteral, NullLiteralExpr>::is;
    using ExprHelper<ExprKind::NullLiteral, NullLiteralExpr>::cast;
    using ExprHelper<ExprKind::NullLiteral, NullLiteralExpr>::make;

};

/* ************************************************************************* */

/**
 * @brief      Boolean literal.
 *
 * @details    In the language it represents `true` or `false` keyword. The
 *             value can be accessed by calling `getValue` and changed by
 *             `setValue`.
 */
class BoolLiteralExpr final
    : public LiteralExpr
    , private ExprHelper<ExprKind::BoolLiteral, BoolLiteralExpr>
{

// Public Types
public:


    /// Boolean type.
    using ValueType = bool;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      value  The literal value, can be `true` or `false`.
     * @param      range  Location in source.
     */
    explicit BoolLiteralExpr(ValueType value, SourceRange range = {}) noexcept;


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns literal value.
     *
     * @return     Literal value.
     */
    ValueType getValue() const noexcept
    {
        return m_value;
    }


    /**
     * @brief      Change literal value.
     *
     * @param      value  The new literal value.
     */
    void setValue(ValueType value) noexcept
    {
        m_value = value;
    }


// Public Operations
public:


    using ExprHelper<ExprKind::BoolLiteral, BoolLiteralExpr>::is;
    using ExprHelper<ExprKind::BoolLiteral, BoolLiteralExpr>::cast;
    using ExprHelper<ExprKind::BoolLiteral, BoolLiteralExpr>::make;


// Private Data Members
private:

    /// Literal value.
    ValueType m_value;

};

/* ************************************************************************* */

/**
 * @brief      Base class for all number literals.
 */
class NumberLiteralExpr
    : public LiteralExpr
    , private ExprRangeHelper<ExprKind::NumberLiteral_First, ExprKind::NumberLiteral_Last, NumberLiteralExpr>
{

// Public Operations
public:


    using ExprRangeHelper<ExprKind::NumberLiteral_First, ExprKind::NumberLiteral_Last, NumberLiteralExpr>::is;
    using ExprRangeHelper<ExprKind::NumberLiteral_First, ExprKind::NumberLiteral_Last, NumberLiteralExpr>::cast;
    using ExprRangeHelper<ExprKind::NumberLiteral_First, ExprKind::NumberLiteral_Last, NumberLiteralExpr>::make;


// Protected Ctors & Dtors
protected:


    using LiteralExpr::LiteralExpr;

};

/* ************************************************************************* */

/**
 * @brief      The integer literal.
 *
 * @details    In the language it represents an integer literal like 0, 5624,
 *             0x12345. The value can be accessed by calling `getValue` and
 *             changed by `setValue`.
 */
class IntLiteralExpr final
    : public NumberLiteralExpr
    , private ExprHelper<ExprKind::IntLiteral, IntLiteralExpr>
{

// Public Types
public:


    /// Integer type.
    using ValueType = int;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      value  Integer value.
     * @param      range  Location in source.
     */
    explicit IntLiteralExpr(ValueType value, SourceRange range = {}) noexcept;


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns literal value.
     *
     * @return     Literal value.
     */
    ValueType getValue() const noexcept
    {
        return m_value;
    }


    /**
     * @brief      Change literal value.
     *
     * @param      value  The new literal value.
     */
    void setValue(ValueType value) noexcept
    {
        m_value = value;
    }


// Public Operations
public:


    using ExprHelper<ExprKind::IntLiteral, IntLiteralExpr>::is;
    using ExprHelper<ExprKind::IntLiteral, IntLiteralExpr>::cast;
    using ExprHelper<ExprKind::IntLiteral, IntLiteralExpr>::make;


// Private Data Members
private:

    /// Literal value.
    ValueType m_value;

};

/* ************************************************************************* */

/**
 * @brief      The float literal.
 *
 * @details    In the language it represents a float literal like 0, 1.346,
 *             15e456. The value can be accessed by calling `getValue` and
 *             changed by `setValue`.
 */
class FloatLiteralExpr final
    : public NumberLiteralExpr
    , private ExprHelper<ExprKind::FloatLiteral, FloatLiteralExpr>
{

// Public Types
public:


    /// Float type.
    using ValueType = float;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      value  The float value.
     * @param      range  Location in source.
     */
    explicit FloatLiteralExpr(ValueType value, SourceRange range = {}) noexcept;


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns literal value.
     *
     * @return     Literal value.
     */
    ValueType getValue() const noexcept
    {
        return m_value;
    }


    /**
     * @brief      Change literal value.
     *
     * @param      value  The new literal value.
     */
    void setValue(ValueType value) noexcept
    {
        m_value = value;
    }


// Public Operations
public:


    using ExprHelper<ExprKind::FloatLiteral, FloatLiteralExpr>::is;
    using ExprHelper<ExprKind::FloatLiteral, FloatLiteralExpr>::cast;
    using ExprHelper<ExprKind::FloatLiteral, FloatLiteralExpr>::make;


// Private Data Members
private:

    /// Literal value.
    ValueType m_value;

};

/* ************************************************************************* */

/**
 * @brief      The character literal.
 *
 * @details    In the language it represents a character literal like '0', 'x',
 *             'á'. The value can be accessed by calling `getValue` and changed
 *             by `setValue`. Value is stored as a UNICODE code point.
 */
class CharLiteralExpr final
    : public LiteralExpr
    , private ExprHelper<ExprKind::CharLiteral, CharLiteralExpr>
{

// Public Types
public:


    /// Character type (UNICODE code point).
    using ValueType = char32_t;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      value  The character UNICODE code point.
     * @param      range  Location in source.
     */
    explicit CharLiteralExpr(ValueType value, SourceRange range = {}) noexcept;


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns literal value.
     *
     * @return     Literal value.
     */
    ValueType getValue() const noexcept
    {
        return m_value;
    }


    /**
     * @brief      Change literal value.
     *
     * @param      value  The new literal value.
     */
    void setValue(ValueType value) noexcept
    {
        m_value = value;
    }


// Public Operations
public:


    using ExprHelper<ExprKind::CharLiteral, CharLiteralExpr>::is;
    using ExprHelper<ExprKind::CharLiteral, CharLiteralExpr>::cast;
    using ExprHelper<ExprKind::CharLiteral, CharLiteralExpr>::make;


// Private Data Members
private:

    /// Literal value.
    ValueType m_value;

};

/* ************************************************************************* */

/**
 * @brief      String literal.
 *
 * @details    In the language it represents a string literal like
 *             "hello world". The value can be accessed by calling `getValue`
 *             and changed by `setValue`.
 */
class StringLiteralExpr final
    : public LiteralExpr
    , private ExprHelper<ExprKind::StringLiteral, StringLiteralExpr>
{

// Public Types
public:


    /// String type.
    using ValueType = String;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      value  The string literal value.
     * @param      range  Location in source.
     */
    explicit StringLiteralExpr(ValueType value, SourceRange range = {});


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns literal value.
     *
     * @return     Literal value.
     */
    const ValueType& getValue() const noexcept
    {
        return m_value;
    }


    /**
     * @brief      Change literal value.
     *
     * @param      value  The new literal value.
     */
    void setValue(ValueType value) noexcept
    {
        m_value = moveValue(value);
    }


// Public Operations
public:


    using ExprHelper<ExprKind::StringLiteral, StringLiteralExpr>::is;
    using ExprHelper<ExprKind::StringLiteral, StringLiteralExpr>::cast;
    using ExprHelper<ExprKind::StringLiteral, StringLiteralExpr>::make;


// Private Data Members
private:

    /// Literal value.
    ValueType m_value;

};

/* ************************************************************************* */

/**
 * @brief      Binary expression.
 *
 * @details    This expression is used for expressions where an operation is
 *             applied to two expressions like addition, subtraction and
 *             relation. In the source it can be identified as:
 *             `<lhs><op><rhs>`.
 */
class BinaryExpr final
    : public Expr
    , private ExprHelper<ExprKind::Binary, BinaryExpr>
{

// Public Enums
public:


    /**
     * @brief      Binary expression operation kind.
     */
    enum class OpKind
    {
        //  Equality operators
        EQ,
        NE,

        // Relational operators
        LT,
        LE,
        GT,
        GE,

        // Additive operators
        Add,
        Sub,

        // Multiplicative operators
        Mul,
        Div,
        Rem,

        // Assignment operators
        Assign,
        MulAssign,
        DivAssign,
        RemAssign,
        AddAssign,
        SubAssign
    };


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      op     Operation kind.
     * @param      lhs    Left operand expression.
     * @param      rhs    Right operand expression.
     * @param      range  Location in source.
     */
    explicit BinaryExpr(OpKind op, UniquePtr<Expr> lhs, UniquePtr<Expr> rhs, SourceRange range = {});


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns operation kind.
     *
     * @return     Operation kind.
     */
    OpKind getOpKind() const noexcept
    {
        return m_operator;
    }


    /**
     * @brief      Change operation kind.
     *
     * @param      op    The new operation kind.
     */
    void setOpKind(OpKind op) noexcept
    {
        m_operator = op;
    }


    /**
     * @brief      Returns LHS expression.
     *
     * @return     LHS expression.
     */
    ViewPtr<const Expr> getLhs() const noexcept
    {
        return makeView(m_lhs);
    }


    /**
     * @brief      Returns LHS expression.
     *
     * @return     LHS expression.
     */
    ViewPtr<Expr> getLhs() noexcept
    {
        return makeView(m_lhs);
    }


    /**
     * @brief      Change LHS expression.
     *
     * @param      lhs   The LHS expression.
     */
    void setLhs(UniquePtr<Expr> lhs) noexcept
    {
        SHARD_ASSERT(lhs);
        m_lhs = moveValue(lhs);
    }


    /**
     * @brief      Returns RHS expression.
     *
     * @return     RHS expression.
     */
    ViewPtr<const Expr> getRhs() const noexcept
    {
        return makeView(m_rhs);
    }


    /**
     * @brief      Returns RHS expression.
     *
     * @return     RHS expression.
     */
    ViewPtr<Expr> getRhs() noexcept
    {
        return makeView(m_rhs);
    }


    /**
     * @brief      Change RHS expression.
     *
     * @param      rhs   The RHS expression.
     */
    void setRhs(UniquePtr<Expr> rhs) noexcept
    {
        SHARD_ASSERT(rhs);
        m_rhs = moveValue(rhs);
    }


// Public Operations
public:


    using ExprHelper<ExprKind::Binary, BinaryExpr>::is;
    using ExprHelper<ExprKind::Binary, BinaryExpr>::cast;
    using ExprHelper<ExprKind::Binary, BinaryExpr>::make;


// Private Data Members
private:

    /// Operation kind.
    OpKind m_operator;

    /// LHS expression.
    UniquePtr<Expr> m_lhs;

    /// RHS expression.
    UniquePtr<Expr> m_rhs;
};

/* ************************************************************************* */

/**
 * @brief      Unary expression.
 *
 * @details    This expression is used for single prefix or postfix expressions
 *             to which an operation is applied like negation, increment or
 *             decrement. In the source it can be identified as: `<op><expr>` or
 *             `<expr><op>`.
 */
class UnaryExpr final
    : public Expr
    , private ExprHelper<ExprKind::Unary, UnaryExpr>
{

// Public Enums
public:


    /**
     * @brief      Unary operation kind.
     */
    enum class OpKind
    {
        PostInc,
        PostDec,
        PreInc,
        PreDec,
        Plus,
        Minus,
        Not
    };


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      op     Operation kind.
     * @param      expr   Operand expression.
     * @param      range  Location in source.
     */
    explicit UnaryExpr(OpKind op, UniquePtr<Expr> expr, SourceRange range = {});


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns operation kind.
     *
     * @return     Operation kind.
     */
    OpKind getOpKind() const noexcept
    {
        return m_operator;
    }


    /**
     * @brief      Change operation kind.
     *
     * @param      op    The new operation kind.
     */
    void setOpKind(OpKind op) noexcept
    {
        m_operator = op;
    }


    /**
     * @brief      Returns subexpression.
     *
     * @return     Subexpression.
     */
    ViewPtr<const Expr> getExpr() const noexcept
    {
        return makeView(m_expr);
    }


    /**
     * @brief      Returns subexpression.
     *
     * @return     Subexpression.
     */
    ViewPtr<Expr> getExpr() noexcept
    {
        return makeView(m_expr);
    }


    /**
     * @brief      Change subexpression.
     *
     * @param      expr  The new subexpression.
     */
    void setExpr(UniquePtr<Expr> expr) noexcept
    {
        SHARD_ASSERT(expr);
        m_expr = moveValue(expr);
    }


// Public Operations
public:


    using ExprHelper<ExprKind::Unary, UnaryExpr>::is;
    using ExprHelper<ExprKind::Unary, UnaryExpr>::cast;
    using ExprHelper<ExprKind::Unary, UnaryExpr>::make;


// Private Data Members
private:

    /// OpKind.
    OpKind m_operator;

    /// Operand.
    UniquePtr<Expr> m_expr;
};

/* ************************************************************************* */

/**
 * @brief      Ternary expression.
 *
 * @details    This expression is used for ternary operator: `<condExpr> ?
 *             <trueExpr> : <falseExpr>`.
 */
class TernaryExpr final
    : public Expr
    , private ExprHelper<ExprKind::Ternary, TernaryExpr>
{

// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      condExpr   Condition expression.
     * @param      trueExpr   Left operand expression.
     * @param      falseExpr  Right operand expression.
     * @param      range      Location in source.
     */
    explicit TernaryExpr(UniquePtr<Expr> condExpr, UniquePtr<Expr> trueExpr, UniquePtr<Expr> falseExpr, SourceRange range = {});


// Public Accessors & Mutators
public:


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
     * @brief      Returns condition expression.
     *
     * @return     Condition expression.
     */
    ViewPtr<Expr> getCondExpr() noexcept
    {
        return makeView(m_condExpr);
    }


    /**
     * @brief      Change condition expression.
     *
     * @param      expr  The new expression.
     */
    void setCondExpr(UniquePtr<Expr> expr) noexcept
    {
        SHARD_ASSERT(expr);
        m_condExpr = moveValue(expr);
    }


    /**
     * @brief      Returns true expression.
     *
     * @return     True expression.
     */
    ViewPtr<const Expr> getTrueExpr() const noexcept
    {
        return makeView(m_trueExpr);
    }


    /**
     * @brief      Returns true expression.
     *
     * @return     True expression.
     */
    ViewPtr<Expr> getTrueExpr() noexcept
    {
        return makeView(m_trueExpr);
    }


    /**
     * @brief      Change true branch expression.
     *
     * @param      expr  The new expression.
     */
    void setTrueExpr(UniquePtr<Expr> expr) noexcept
    {
        SHARD_ASSERT(expr);
        m_trueExpr = moveValue(expr);
    }


    /**
     * @brief      Returns false expression.
     *
     * @return     False expression.
     */
    ViewPtr<const Expr> getFalseExpr() const noexcept
    {
        return makeView(m_falseExpr);
    }


    /**
     * @brief      Returns false expression.
     *
     * @return     False expression.
     */
    ViewPtr<Expr> getFalseExpr() noexcept
    {
        return makeView(m_falseExpr);
    }


    /**
     * @brief      Change false branch expression.
     *
     * @param      expr  The new expression.
     */
    void setFalseExpr(UniquePtr<Expr> expr) noexcept
    {
        SHARD_ASSERT(expr);
        m_falseExpr = moveValue(expr);
    }


// Public Operations
public:


    using ExprHelper<ExprKind::Ternary, TernaryExpr>::is;
    using ExprHelper<ExprKind::Ternary, TernaryExpr>::cast;
    using ExprHelper<ExprKind::Ternary, TernaryExpr>::make;


// Private Data Members
private:

    /// Condition expression.
    UniquePtr<Expr> m_condExpr;

    /// True expression.
    UniquePtr<Expr> m_trueExpr;

    /// False expression.
    UniquePtr<Expr> m_falseExpr;
};

/* ************************************************************************* */

/**
 * @brief      Parenthesis expression.
 *
 * @details    Represents a parenthesis aroud another expression: `(<expr>)`.
 */
class ParenExpr final
    : public Expr
    , private ExprHelper<ExprKind::Paren, ParenExpr>
{


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      expr   Inner expression.
     * @param      range  Location in source.
     */
    explicit ParenExpr(UniquePtr<Expr> expr, SourceRange range = {});


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns inner expression.
     *
     * @return     Inner expression.
     */
    ViewPtr<const Expr> getExpr() const noexcept
    {
        return makeView(m_expr);
    }


    /**
     * @brief      Returns inner expression.
     *
     * @return     Inner expression.
     */
    ViewPtr<Expr> getExpr() noexcept
    {
        return makeView(m_expr);
    }


    /**
     * @brief      Change expression.
     *
     * @param      expr  The new expression.
     */
    void setExpr(UniquePtr<Expr> expr) noexcept
    {
        SHARD_ASSERT(expr);
        m_expr = moveValue(expr);
    }


// Public Operations
public:


    using ExprHelper<ExprKind::Paren, ParenExpr>::is;
    using ExprHelper<ExprKind::Paren, ParenExpr>::cast;
    using ExprHelper<ExprKind::Paren, ParenExpr>::make;


// Private Data Members
private:

    /// Inner expression.
    UniquePtr<Expr> m_expr;

};

/* ************************************************************************* */

/**
 * @brief      Identifier expression - represents usage of variable, function or
 *             anything that can be declared.
 */
class IdentifierExpr final
    : public Expr
    , private ExprHelper<ExprKind::Identifier, IdentifierExpr>
{


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      name   Identifier name.
     * @param      range  Location in source.
     */
    explicit IdentifierExpr(String name, SourceRange range = {});


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns identifier name.
     *
     * @return     Identifier name.
     */
    const String& getName() const noexcept
    {
        return m_name;
    }


    /**
     * @brief      Change identifier name.
     *
     * @param      name  The new identifier name.
     */
    void setName(String name) noexcept
    {
        SHARD_ASSERT(!name.empty());
        m_name = moveValue(name);
    }


// Public Operations
public:


    using ExprHelper<ExprKind::Identifier, IdentifierExpr>::is;
    using ExprHelper<ExprKind::Identifier, IdentifierExpr>::cast;
    using ExprHelper<ExprKind::Identifier, IdentifierExpr>::make;


// Private Data Members
private:

    /// Identifier name.
    String m_name;

};

/* ************************************************************************* */

/**
 * @brief      Member access expression.
 *
 * @details    In the source it represents following expression: `<expr>.<name>`.
 */
class MemberAccessExpr final
    : public Expr
    , private ExprHelper<ExprKind::MemberAccess, MemberAccessExpr>
{


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      expr   Evaluation context expression.
     * @param      name   Identifier name.
     * @param      range  Location in source.
     */
    explicit MemberAccessExpr(UniquePtr<Expr> expr, String name, SourceRange range = {});


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns evaluation context expression.
     *
     * @return     The evaluation context expression.
     */
    ViewPtr<const Expr> getExpr() const noexcept
    {
        return makeView(m_expr);
    }


    /**
     * @brief      Returns evaluation context expression.
     *
     * @return     The evaluation context expression.
     */
    ViewPtr<Expr> getExpr() noexcept
    {
        return makeView(m_expr);
    }


    /**
     * @brief      Change evaluation context expression.
     *
     * @param      expr  The new expression.
     */
    void setExpr(UniquePtr<Expr> expr) noexcept
    {
        SHARD_ASSERT(expr);
        m_expr = moveValue(expr);
    }


    /**
     * @brief      Returns identifier name.
     *
     * @return     Identifier name.
     */
    const String& getName() const noexcept
    {
        return m_name;
    }


    /**
     * @brief      Change identifier name.
     *
     * @param      name  The new identifier name.
     */
    void setName(String name) noexcept
    {
        SHARD_ASSERT(!name.empty());
        m_name = moveValue(name);
    }


// Public Operations
public:


    using ExprHelper<ExprKind::MemberAccess, MemberAccessExpr>::is;
    using ExprHelper<ExprKind::MemberAccess, MemberAccessExpr>::cast;
    using ExprHelper<ExprKind::MemberAccess, MemberAccessExpr>::make;


// Private Data Members
private:

    /// Left expression.
    UniquePtr<Expr> m_expr;

    /// Identifier name.
    String m_name;

};

/* ************************************************************************* */

/**
 * @brief      Function call expression.
 *
 * @details    In the source it represents following expression:
 *             `<expr>(<args>)`.
 */
class FunctionCallExpr final
    : public Expr
    , private ExprHelper<ExprKind::FunctionCall, FunctionCallExpr>
{


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      expr   Callee expression.
     * @param      args   Call arguments.
     * @param      range  Location in source.
     */
    explicit FunctionCallExpr(UniquePtr<Expr> expr, PtrDynamicArray<Expr> args, SourceRange range = {});


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns callee expression.
     *
     * @return     The callee expression.
     */
    ViewPtr<const Expr> getExpr() const noexcept
    {
        return makeView(m_expr);
    }


    /**
     * @brief      Returns callee expression.
     *
     * @return     The callee expression.
     */
    ViewPtr<Expr> getExpr() noexcept
    {
        return makeView(m_expr);
    }


    /**
     * @brief      Change expression.
     *
     * @param      expr  The new expression.
     */
    void setExpr(UniquePtr<Expr> expr) noexcept
    {
        SHARD_ASSERT(expr);
        m_expr = moveValue(expr);
    }


    /**
     * @brief      Returns call arguments.
     *
     * @return     The call arguments.
     */
    const PtrDynamicArray<Expr>& getArguments() const noexcept
    {
        return m_arguments;
    }


    /**
     * @brief      Returns call arguments.
     *
     * @return     The call arguments.
     */
    PtrDynamicArray<Expr>& getArguments() noexcept
    {
        return m_arguments;
    }


    /**
     * @brief      Change call arguments.
     *
     * @param      args  The call arguments.
     */
    void setArguments(PtrDynamicArray<Expr> args) noexcept
    {
        m_arguments = moveValue(args);
    }


// Public Operations
public:


    using ExprHelper<ExprKind::FunctionCall, FunctionCallExpr>::is;
    using ExprHelper<ExprKind::FunctionCall, FunctionCallExpr>::cast;
    using ExprHelper<ExprKind::FunctionCall, FunctionCallExpr>::make;


// Private Data Members
private:

    /// Callee expression.
    UniquePtr<Expr> m_expr;

    /// Call arguments.
    PtrDynamicArray<Expr> m_arguments;

};

/* ************************************************************************* */

/**
 * @brief      Subscript expression.
 *
 * @details    In the source it can be identified as: `<expr>[<args>]`.
 */
class SubscriptExpr final
    : public Expr
    , private ExprHelper<ExprKind::Subscript, SubscriptExpr>
{


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      expr   Callee expression.
     * @param      args   Call arguments.
     * @param      range  Location in source.
     */
    explicit SubscriptExpr(UniquePtr<Expr> expr, PtrDynamicArray<Expr> args, SourceRange range = {});


// Public Accessors & Mutators
public:


    /**
     * @brief      Returns callee expression.
     *
     * @return     The callee expression.
     */
    ViewPtr<const Expr> getExpr() const noexcept
    {
        return makeView(m_expr);
    }


    /**
     * @brief      Returns callee expression.
     *
     * @return     The callee expression.
     */
    ViewPtr<Expr> getExpr() noexcept
    {
        return makeView(m_expr);
    }


    /**
     * @brief      Change expression.
     *
     * @param      expr  The new expression.
     */
    void setExpr(UniquePtr<Expr> expr) noexcept
    {
        SHARD_ASSERT(expr);
        m_expr = moveValue(expr);
    }


    /**
     * @brief      Returns call arguments.
     *
     * @return     The call arguments.
     */
    const PtrDynamicArray<Expr>& getArguments() const noexcept
    {
        return m_arguments;
    }


    /**
     * @brief      Returns call arguments.
     *
     * @return     The call arguments.
     */
    PtrDynamicArray<Expr>& getArguments() noexcept
    {
        return m_arguments;
    }


    /**
     * @brief      Change call arguments.
     *
     * @param      args  The call arguments.
     */
    void setArguments(PtrDynamicArray<Expr> args) noexcept
    {
        m_arguments = moveValue(args);
    }


// Public Operations
public:


    using ExprHelper<ExprKind::Subscript, SubscriptExpr>::is;
    using ExprHelper<ExprKind::Subscript, SubscriptExpr>::cast;
    using ExprHelper<ExprKind::Subscript, SubscriptExpr>::make;


// Private Data Members
private:

    /// Callee expression.
    UniquePtr<Expr> m_expr;

    /// Call arguments.
    PtrDynamicArray<Expr> m_arguments;

};

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

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
#include "shard/String.hpp"
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

/**
 * @brief      Type of expression.
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
class Expr : public Node
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


// Public Operations
public:


    /**
     * @brief      Test if expression match required kind.
     *
     * @tparam     ExprType  Expression type.
     *
     * @return     Returns `true` if this is `ExprType`, `false` otherwise.
     */
    template<typename ExprType>
    bool is() const noexcept
    {
        return getKind() == ExprType::Kind;
    }


    /**
     * @brief      Cast this to required expression type.
     *
     * @tparam     ExprType  Expression type.
     *
     * @return     Reference to required expression type.
     */
    template<typename ExprType>
    ExprType& cast() noexcept
    {
        SHARD_ASSERT(is<ExprType>());
        return static_cast<ExprType&>(*this);
    }


    /**
     * @brief      Cast this to required expression type.
     *
     * @tparam     ExprType  Expression type.
     *
     * @return     Reference to required expression type.
     */
    template<typename ExprType>
    const ExprType& cast() const noexcept
    {
        SHARD_ASSERT(is<ExprType>());
        return static_cast<const ExprType&>(*this);
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
 * @brief      Base class for all literal kinds.
 *
 * @details    It expression is a literal `expr.is<LiteralExpr>()` returns true.
 */
class LiteralExpr : public Expr
{

// Public Constants
public:


    /// Expression kind
    static constexpr KindRange<ExprKind> Kind{ExprKind::Literal_First, ExprKind::Literal_Last};


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
class NullLiteralExpr final : public LiteralExpr
{

// Public Constants
public:


    /// Expression kind
    static constexpr ExprKind Kind = ExprKind::NullLiteral;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      range  Location in source.
     */
    explicit NullLiteralExpr(SourceRange range = {}) noexcept;


    /**
     * @brief      Destructor.
     */
    ~NullLiteralExpr();


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      range  Location in source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<NullLiteralExpr> make(SourceRange range = {});

};

/* ************************************************************************* */

/**
 * @brief      Boolean literal.
 *
 * @details    In the language it represents `true` or `false` keyword. The
 *             value can be accessed by calling `getValue` and changed by
 *             `setValue`.
 */
class BoolLiteralExpr final : public LiteralExpr
{

// Public Constants
public:


    /// Expression kind
    static constexpr ExprKind Kind = ExprKind::BoolLiteral;


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


    /**
     * @brief      Destructor.
     */
    ~BoolLiteralExpr();


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
    void setValue(ValueType value);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      value  The literal value, can be `true` or `false`.
     * @param      range  Location in source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<BoolLiteralExpr> make(ValueType value, SourceRange range = {});


// Private Data Members
private:

    /// Literal value.
    ValueType m_value;

};

/* ************************************************************************* */

/**
 * @brief      Base class for all number literals.
 */
class NumberLiteralExpr : public LiteralExpr
{

// Public Constants
public:


    /// Expression kind
    static constexpr KindRange<ExprKind> Kind{ExprKind::NumberLiteral_First, ExprKind::NumberLiteral_Last};


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
class IntLiteralExpr final : public NumberLiteralExpr
{

// Public Constants
public:


    /// Expression kind
    static constexpr ExprKind Kind = ExprKind::IntLiteral;


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


    /**
     * @brief      Destructor.
     */
    ~IntLiteralExpr();


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
    void setValue(ValueType value);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      value  Integer value.
     * @param      range  Location in source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<IntLiteralExpr> make(ValueType value, SourceRange range = {});


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
class FloatLiteralExpr final : public NumberLiteralExpr
{

// Public Constants
public:


    /// Expression kind
    static constexpr ExprKind Kind = ExprKind::FloatLiteral;


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


    /**
     * @brief      Destructor.
     */
    ~FloatLiteralExpr();


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
    void setValue(ValueType value);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      value  The float value.
     * @param      range  Location in source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<FloatLiteralExpr> make(ValueType value, SourceRange range = {});


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
class CharLiteralExpr final : public LiteralExpr
{

// Public Constants
public:


    /// Expression kind
    static constexpr ExprKind Kind = ExprKind::CharLiteral;


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


    /**
     * @brief      Destructor.
     */
    ~CharLiteralExpr();


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
    void setValue(ValueType value);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      value  The character UNICODE code point.
     * @param      range  Location in source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<CharLiteralExpr> make(ValueType value, SourceRange range = {});


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
class StringLiteralExpr final : public LiteralExpr
{

// Public Constants
public:


    /// Expression kind
    static constexpr ExprKind Kind = ExprKind::StringLiteral;


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


    /**
     * @brief      Destructor.
     */
    ~StringLiteralExpr();


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
    void setValue(ValueType value);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      value  The string literal value.
     * @param      range  Location in source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<StringLiteralExpr> make(ValueType value, SourceRange range = {});


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
class BinaryExpr final : public Expr
{

// Public Constants
public:


    /// Expression kind
    static constexpr ExprKind Kind = ExprKind::Binary;


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


    /**
     * @brief      Destructor.
     */
    ~BinaryExpr();


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
    void setOpKind(OpKind op);


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
    void setLhs(UniquePtr<Expr> lhs);


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
    void setRhs(UniquePtr<Expr> rhs);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      op     Operation kind.
     * @param      lhs    Left operand expression.
     * @param      rhs    Right operand expression.
     * @param      range  Location in source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<BinaryExpr> make(OpKind op, UniquePtr<Expr> lhs, UniquePtr<Expr> rhs, SourceRange range = {});


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
class UnaryExpr final : public Expr
{

// Public Constants
public:


    /// Expression kind
    static constexpr ExprKind Kind = ExprKind::Unary;


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


    /**
     * @brief      Destructor.
     */
    ~UnaryExpr();


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
    void setOpKind(OpKind op);


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
    void setExpr(UniquePtr<Expr> expr);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      op     Operation kind.
     * @param      expr   Operand expression.
     * @param      range  Location in source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<UnaryExpr> make(OpKind op, UniquePtr<Expr> expr, SourceRange range = {});


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
class TernaryExpr final : public Expr
{

// Public Constants
public:


    /// Expression kind
    static constexpr ExprKind Kind = ExprKind::Ternary;


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


    /**
     * @brief      Destructor.
     */
    ~TernaryExpr();


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
    void setCondExpr(UniquePtr<Expr> expr);


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
    void setTrueExpr(UniquePtr<Expr> expr);


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
    void setFalseExpr(UniquePtr<Expr> expr);

// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      condExpr   Condition expression.
     * @param      trueExpr   Left operand expression.
     * @param      falseExpr  Right operand expression.
     * @param      range      Location in source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<TernaryExpr> make(UniquePtr<Expr> condExpr, UniquePtr<Expr> trueExpr, UniquePtr<Expr> falseExpr, SourceRange range = {});


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
class ParenExpr final : public Expr
{

// Public Constants
public:


    /// Expression kind
    static constexpr ExprKind Kind = ExprKind::Paren;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      expr   Inner expression.
     * @param      range  Location in source.
     */
    explicit ParenExpr(UniquePtr<Expr> expr, SourceRange range = {});


    /**
     * @brief      Destructor.
     */
    ~ParenExpr();


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
    void setExpr(UniquePtr<Expr> expr);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      expr   Inner expression.
     * @param      range  Location in source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<ParenExpr> make(UniquePtr<Expr> expr, SourceRange range = {});


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
class IdentifierExpr final : public Expr
{

// Public Constants
public:


    /// Expression kind
    static constexpr ExprKind Kind = ExprKind::Identifier;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      name   Identifier name.
     * @param      range  Location in source.
     */
    explicit IdentifierExpr(String name, SourceRange range = {});


    /**
     * @brief      Destructor.
     */
    ~IdentifierExpr();


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
    void setName(String name);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      name   Identifier name.
     * @param      range  Location in source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<IdentifierExpr> make(String name, SourceRange range = {});


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
class MemberAccessExpr final : public Expr
{

// Public Constants
public:


    /// Expression kind
    static constexpr ExprKind Kind = ExprKind::MemberAccess;


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


    /**
     * @brief      Destructor.
     */
    ~MemberAccessExpr();


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
    void setExpr(UniquePtr<Expr> expr);


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
    void setName(String name);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      expr   Evaluation context expression.
     * @param      name   Identifier name.
     * @param      range  Location in source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<MemberAccessExpr> make(UniquePtr<Expr> expr, String name, SourceRange range = {});


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
class FunctionCallExpr final : public Expr
{

// Public Constants
public:


    /// Expression kind
    static constexpr ExprKind Kind = ExprKind::FunctionCall;


// Public Ctors & Dtors
public:


    /**
     * @brief      Constructor.
     *
     * @param      expr   Callee expression.
     * @param      args   Call arguments.
     * @param      range  Location in source.
     */
    explicit FunctionCallExpr(UniquePtr<Expr> expr, PtrDynamicArray<Expr> args = {}, SourceRange range = {});


    /**
     * @brief      Destructor.
     */
    ~FunctionCallExpr();


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
    void setExpr(UniquePtr<Expr> expr);


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
     * @brief      Change call arguments.
     *
     * @param      args  The call arguments.
     */
    void setArguments(PtrDynamicArray<Expr> args);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      expr   Callee expression.
     * @param      args   Call arguments.
     * @param      range  Location in source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<FunctionCallExpr> make(UniquePtr<Expr> expr, PtrDynamicArray<Expr> args = {}, SourceRange range = {});


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
class SubscriptExpr final : public Expr
{

// Public Constants
public:


    /// Expression kind
    static constexpr ExprKind Kind = ExprKind::Subscript;


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


    /**
     * @brief      Destructor.
     */
    ~SubscriptExpr();


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
    void setExpr(UniquePtr<Expr> expr);


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
     * @brief      Change call arguments.
     *
     * @param      args  The call arguments.
     */
    void setArguments(PtrDynamicArray<Expr> args);


// Public Operations
public:


    /**
     * @brief      Construct object.
     *
     * @param      expr   Callee expression.
     * @param      args   Call arguments.
     * @param      range  Location in source.
     *
     * @return     Created unique pointer.
     */
    static UniquePtr<SubscriptExpr> make(UniquePtr<Expr> expr, PtrDynamicArray<Expr> args, SourceRange range = {});


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

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
#include "shard/SourceLocation.hpp"
#include "shard/SourceRange.hpp"
#include "shard/UniquePtr.hpp"
#include "shard/ViewPtr.hpp"
#include "shard/ast/utility.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

class Decl;

/* ************************************************************************* */

/**
 * @brief Type of expression.
 */
enum class ExprKind
{
    NullLiteral = 1,
    BoolLiteral = 2,
    IntLiteral = 3,
    FloatLiteral = 4,
    CharLiteral = 5,
    StringLiteral = 6,
    Literal_First = NullLiteral,
    Literal_Last = StringLiteral,
    NumberLiteral_First = IntLiteral,
    NumberLiteral_Last = FloatLiteral,
    Binary = 7,
    PrefixUnary = 8,
    PostfixUnary = 9,
    Ternary = 10,
    Paren = 11,
    Identifier = 12
};

/* ************************************************************************* */

/**
 * @brief Base expression class.
 */
class Expr : public LocationInfo
{

// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param kind  Expression kind.
     * @param range Source range.
     */
    Expr(ExprKind kind, SourceRange range) noexcept;


    /**
     * @brief Destructor.
     */
    virtual ~Expr() = 0;


// Public Accessors & Mutators
public:


    /**
     * @brief Returns expression kind.
     * @return Expression kind.
     */
    ExprKind getKind() const noexcept
    {
        return m_kind;
    }


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
    : public TypeHelper<ExprKind, KIND, Expr>
    , public CastHelper<Expr, T>
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
    : public TypeRangeHelper<ExprKind, KIND1, KIND2, Expr>
    , public CastHelper<Expr, T>
{
    // Nothing to do
};

/* ************************************************************************* */

/**
 * @brief Base class for all literal kinds.
 */
class LiteralExpr
    : public Expr
    , private ExprRangeHelper<ExprKind::Literal_First, ExprKind::Literal_Last, LiteralExpr>
{

// Public Ctors & Dtors
public:


    using Expr::Expr;


// Public Operations
public:


    using ExprRangeHelper<ExprKind::Literal_First, ExprKind::Literal_Last, LiteralExpr>::is;
    using ExprRangeHelper<ExprKind::Literal_First, ExprKind::Literal_Last, LiteralExpr>::cast;

};

/* ************************************************************************* */

/**
 * @brief Null literal.
 */
class NullLiteralExpr final
    : public LiteralExpr
    , private ExprHelper<ExprKind::NullLiteral, NullLiteralExpr>
{

// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param range Location in source.
     */
    explicit NullLiteralExpr(SourceRange range = {}) noexcept
        : LiteralExpr(ExprKind::NullLiteral, range)
    {
        // Nothing to do
    }


// Public Operations
public:


    using ExprHelper<ExprKind::NullLiteral, NullLiteralExpr>::is;
    using ExprHelper<ExprKind::NullLiteral, NullLiteralExpr>::cast;

};

/* ************************************************************************* */

/**
 * @brief Boolean literal.
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
     * @brief Constructor.
     * @param value Value.
     * @param range Location in source.
     */
    explicit BoolLiteralExpr(ValueType value, SourceRange range = {}) noexcept
        : LiteralExpr(ExprKind::BoolLiteral, range)
        , m_value(value)
    {
        // Nothing to do
    }


// Public Accessors & Mutators
public:


    /**
     * @brief Returns literal value.
     * @return Literal value.
     */
    ValueType getValue() const noexcept
    {
        return m_value;
    }


// Public Operations
public:


    using ExprHelper<ExprKind::BoolLiteral, BoolLiteralExpr>::is;
    using ExprHelper<ExprKind::BoolLiteral, BoolLiteralExpr>::cast;


// Private Data Members
private:

    /// Literal value.
    ValueType m_value;

};

/* ************************************************************************* */

/**
 * @brief Number literal.
 */
class NumberLiteralExpr
    : public LiteralExpr
    , private ExprRangeHelper<ExprKind::NumberLiteral_First, ExprKind::NumberLiteral_Last, NumberLiteralExpr>
{

// Public Ctors & Dtors
public:


    using LiteralExpr::LiteralExpr;


// Public Operations
public:


    using ExprRangeHelper<ExprKind::NumberLiteral_First, ExprKind::NumberLiteral_Last, NumberLiteralExpr>::is;
    using ExprRangeHelper<ExprKind::NumberLiteral_First, ExprKind::NumberLiteral_Last, NumberLiteralExpr>::cast;


};

/* ************************************************************************* */

/**
 * @brief Integer literal.
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
     * @brief Constructor.
     * @param value Value.
     * @param range Location in source.
     */
    explicit IntLiteralExpr(ValueType value, SourceRange range = {}) noexcept
        : NumberLiteralExpr(ExprKind::IntLiteral, range)
        , m_value(value)
    {
        // Nothing to do
    }


// Public Accessors & Mutators
public:


    /**
     * @brief Returns literal value.
     * @return Literal value.
     */
    ValueType getValue() const noexcept
    {
        return m_value;
    }


// Public Operations
public:


    using ExprHelper<ExprKind::IntLiteral, IntLiteralExpr>::is;
    using ExprHelper<ExprKind::IntLiteral, IntLiteralExpr>::cast;


// Private Data Members
private:

    /// Literal value.
    ValueType m_value;

};

/* ************************************************************************* */

/**
 * @brief Float literal.
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
     * @brief Constructor.
     * @param value Value.
     * @param range Location in source.
     */
    explicit FloatLiteralExpr(ValueType value, SourceRange range = {}) noexcept
        : NumberLiteralExpr(ExprKind::FloatLiteral, range)
        , m_value(value)
    {
        // Nothing to do
    }


// Public Accessors & Mutators
public:


    /**
     * @brief Returns literal value.
     * @return Literal value.
     */
    ValueType getValue() const noexcept
    {
        return m_value;
    }


// Public Operations
public:


    using ExprHelper<ExprKind::FloatLiteral, FloatLiteralExpr>::is;
    using ExprHelper<ExprKind::FloatLiteral, FloatLiteralExpr>::cast;


// Private Data Members
private:

    /// Literal value.
    ValueType m_value;

};

/* ************************************************************************* */

/**
 * @brief Character literal.
 */
class CharLiteralExpr final
    : public LiteralExpr
    , private ExprHelper<ExprKind::CharLiteral, CharLiteralExpr>
{

// Public Types
public:


    /// Character type (UTF-8 can have 4 bytes).
    using ValueType = char32_t;


// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param value Value.
     * @param range Location in source.
     */
    explicit CharLiteralExpr(ValueType value, SourceRange range = {}) noexcept
        : LiteralExpr(ExprKind::CharLiteral, range)
        , m_value(value)
    {
        // Nothing to do
    }


// Public Accessors & Mutators
public:


    /**
     * @brief Returns literal value.
     * @return Literal value.
     */
    ValueType getValue() const noexcept
    {
        return m_value;
    }


// Public Operations
public:


    using ExprHelper<ExprKind::CharLiteral, CharLiteralExpr>::is;
    using ExprHelper<ExprKind::CharLiteral, CharLiteralExpr>::cast;


// Private Data Members
private:

    /// Literal value.
    ValueType m_value;

};

/* ************************************************************************* */

/**
 * @brief String literal.
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
     * @brief Constructor.
     * @param range Location in source.
     * @param value Value.
     */
    explicit StringLiteralExpr(ValueType value, SourceRange range = {}) noexcept
        : LiteralExpr(ExprKind::StringLiteral, range)
        , m_value(moveValue(value))
    {
        // Nothing to do
    }


// Public Accessors & Mutators
public:


    /**
     * @brief Returns literal value.
     * @return Literal value.
     */
    const ValueType& getValue() const noexcept
    {
        return m_value;
    }


// Public Operations
public:


    using ExprHelper<ExprKind::StringLiteral, StringLiteralExpr>::is;
    using ExprHelper<ExprKind::StringLiteral, StringLiteralExpr>::cast;


// Private Data Members
private:

    /// Literal value.
    ValueType m_value;

};

/* ************************************************************************* */

/**
 * @brief Binary expression.
 */
class BinaryExpr final
    : public Expr
    , private ExprHelper<ExprKind::Binary, BinaryExpr>
{

// Public Enums
public:


    /**
     * @brief Binary expression operator.
     */
    enum class Operator
    {
        Equal,
        NotEqual,
        Less,
        LessEqual,
        Greater,
        GreaterEqual,
        Add,
        Subtract,
        Multiply,
        Divide,
        Modulo
    };


// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param lhs   Left operand.
     * @param rhs   Right operand.
     * @param op    Operator type.
     * @param range Location in source.
     */
    explicit BinaryExpr(Operator op, UniquePtr<Expr> lhs, UniquePtr<Expr> rhs, SourceRange range = {}) noexcept
        : Expr(ExprKind::Binary, range)
        , m_operator(op)
        , m_lhs(moveValue(lhs))
        , m_rhs(moveValue(rhs))
    {
        // Nothing to do
    }


// Public Accessors & Mutators
public:


    /**
     * @brief Returns left operand.
     * @return Left operand.
     */
    ViewPtr<const Expr> getLeftOperand() const noexcept
    {
        return m_lhs.get();
    }


    /**
     * @brief Returns right operand.
     * @return Right operand.
     */
    ViewPtr<const Expr> getRightOperand() const noexcept
    {
        return m_rhs.get();
    }


    /**
     * @brief Returns operator.
     * @return Operator.
     */
    Operator getOperator() const noexcept
    {
        return m_operator;
    }


// Public Operations
public:


    using ExprHelper<ExprKind::Binary, BinaryExpr>::is;
    using ExprHelper<ExprKind::Binary, BinaryExpr>::cast;


// Private Data Members
private:

    /// Operator.
    Operator m_operator;

    /// Left operand.
    UniquePtr<Expr> m_lhs;

    /// Right operand.
    UniquePtr<Expr> m_rhs;
};

/* ************************************************************************* */

/**
 * @brief Prefix unary expression.
 */
class PrefixUnaryExpr final
    : public Expr
    , private ExprHelper<ExprKind::PrefixUnary, PrefixUnaryExpr>
{

// Public Enums
public:


    /**
     * @brief Binary expression operator.
     */
    enum class Operator
    {
        Increment,
        Decrement,
        Plus,
        Minus,
        Negate
    };


// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param op    Operator type.
     * @param expr  Operand.
     * @param range Location in source.
     */
    explicit PrefixUnaryExpr(Operator op, UniquePtr<Expr> expr, SourceRange range = {}) noexcept
        : Expr(ExprKind::PrefixUnary, range)
        , m_operator(op)
        , m_expr(moveValue(expr))
    {
        // Nothing to do
    }


// Public Accessors & Mutators
public:


    /**
     * @brief Returns operand.
     * @return Operand.
     */
    ViewPtr<const Expr> getOperand() const noexcept
    {
        return m_expr.get();
    }


    /**
     * @brief Returns operator.
     * @return Operator.
     */
    Operator getOperator() const noexcept
    {
        return m_operator;
    }


// Public Operations
public:


    using ExprHelper<ExprKind::PrefixUnary, PrefixUnaryExpr>::is;
    using ExprHelper<ExprKind::PrefixUnary, PrefixUnaryExpr>::cast;


// Private Data Members
private:

    /// Operator.
    Operator m_operator;

    /// Operand.
    UniquePtr<Expr> m_expr;
};

/* ************************************************************************* */

/**
 * @brief Postfix unary expression.
 */
class PostfixUnaryExpr final
    : public Expr
    , private ExprHelper<ExprKind::PostfixUnary, PostfixUnaryExpr>
{

// Public Enums
public:


    /**
     * @brief Binary expression operator.
     */
    enum class Operator
    {
        Increment,
        Decrement
    };


// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param expr  Operand.
     * @param op    Operator type.
     * @param range Location in source.
     */
    explicit PostfixUnaryExpr(Operator op, UniquePtr<Expr> expr, SourceRange range = {}) noexcept
        : Expr(ExprKind::PostfixUnary, range)
        , m_operator(op)
        , m_expr(moveValue(expr))
    {
        // Nothing to do
    }


// Public Accessors & Mutators
public:


    /**
     * @brief Returns operand.
     * @return Operand.
     */
    ViewPtr<const Expr> getOperand() const noexcept
    {
        return m_expr.get();
    }


    /**
     * @brief Returns operator.
     * @return Operator.
     */
    Operator getOperator() const noexcept
    {
        return m_operator;
    }


// Public Operations
public:


    using ExprHelper<ExprKind::PostfixUnary, PostfixUnaryExpr>::is;
    using ExprHelper<ExprKind::PostfixUnary, PostfixUnaryExpr>::cast;


// Private Data Members
private:

    /// Operator.
    Operator m_operator;

    /// Operand.
    UniquePtr<Expr> m_expr;

};

/* ************************************************************************* */

/**
 * @brief Ternary expression.
 */
class TernaryExpr final
    : public Expr
    , private ExprHelper<ExprKind::Ternary, TernaryExpr>
{

// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param condExpr  Condition expression.
     * @param trueExpr  Left operand.
     * @param falseExpr Right operand.
     * @param range     Location in source.
     */
    explicit TernaryExpr(UniquePtr<Expr> condExpr, UniquePtr<Expr> trueExpr, UniquePtr<Expr> falseExpr, SourceRange range = {}) noexcept
        : Expr(ExprKind::Ternary, range)
        , m_condExpr(moveValue(condExpr))
        , m_trueExpr(moveValue(trueExpr))
        , m_falseExpr(moveValue(falseExpr))
    {
        // Nothing to do
    }


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
     * @brief Returns true expression.
     * @return True expression.
     */
    ViewPtr<const Expr> getTrueExpr() const noexcept
    {
        return m_trueExpr.get();
    }


    /**
     * @brief Returns false expression.
     * @return False expression.
     */
    ViewPtr<const Expr> getFalseExpr() const noexcept
    {
        return m_falseExpr.get();
    }


// Public Operations
public:


    using ExprHelper<ExprKind::Ternary, TernaryExpr>::is;
    using ExprHelper<ExprKind::Ternary, TernaryExpr>::cast;


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
 * @brief Parenthesis expression: '(expr)'.
 */
class ParenExpr final
    : public Expr
    , private ExprHelper<ExprKind::Paren, ParenExpr>
{


// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param expr  Inner expression.
     * @param range Location in source.
     */
    explicit ParenExpr(UniquePtr<Expr> expr, SourceRange range = {}) noexcept
        : Expr(ExprKind::Paren, range)
        , m_expr(moveValue(expr))
    {
        SHARD_ASSERT(m_expr);
    }


// Public Accessors & Mutators
public:


    /**
     * @brief Returns inner expression.
     * @return Inner expression.
     */
    ViewPtr<const Expr> getExpr() const noexcept
    {
        return m_expr.get();
    }


// Public Operations
public:


    using ExprHelper<ExprKind::Paren, ParenExpr>::is;
    using ExprHelper<ExprKind::Paren, ParenExpr>::cast;


// Private Data Members
private:

    /// Inner expression.
    UniquePtr<Expr> m_expr;

};

/* ************************************************************************* */

/**
 * @brief Identifier expression - represents usage of variable, function or anything
 * that can be declared.
 */
class IdentifierExpr final
    : public Expr
    , private ExprHelper<ExprKind::Identifier, IdentifierExpr>
{


// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param range Location in source.
     * @param name  Identifier name.
     */
    explicit IdentifierExpr(String name, SourceRange range = {}) noexcept
        : Expr(ExprKind::Identifier, range)
        , m_name(moveValue(name))
    {
        SHARD_ASSERT(!m_name.empty());
    }


// Public Accessors & Mutators
public:


    /**
     * @brief Returns identifier name.
     * @return Identifier name.
     */
    const String& getName() const noexcept
    {
        return m_name;
    }


// Public Operations
public:


    using ExprHelper<ExprKind::Identifier, IdentifierExpr>::is;
    using ExprHelper<ExprKind::Identifier, IdentifierExpr>::cast;


// Private Data Members
private:

    /// Identifier name.
    String m_name;

};

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

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

// C++
#include <functional>

// Shard
#include "shard/Map.hpp"
#include "shard/Set.hpp"
#include "shard/UniquePtr.hpp"
#include "shard/ast/Decls.hpp"
#include "shard/ast/Exprs.hpp"
#include "shard/ast/Source.hpp"
#include "shard/ast/Stmts.hpp"
#include "shard/parser/exceptions.hpp"
#include "shard/tokenizer/TokenFilterIterator.hpp"
#include "shard/tokenizer/Tokenizer.hpp"

/* ************************************************************************* */

namespace shard::parser {

/* ************************************************************************* */

/**
 * @brief      Shard syntax analyzer.
 */
class Parser
{
public:
    // Types

    /// Parser extension for statements.
    using StmtHandler = std::function<ast::StmtPtr(Parser&)>;

public:
    // Ctors & Dtors

    /**
     * @brief      Create a parser.
     *
     * @param      begin  The begin iterator.
     * @param      end    The end iterator.
     *
     * @tparam     IT     Iterator type.
     */
    template<typename IT>
    explicit Parser(IT begin, IT end)
        : m_current(begin)
        , m_end(end)
    {
        // Nothing to do
    }

    /**
     * @brief      Create a parser.
     *
     * @param      tokenizer  The tokenizer.
     */
    explicit Parser(tokenizer::Tokenizer& tokenizer)
        : Parser(tokenizer.begin(), tokenizer.end())
    {
        // Nothing to do
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns supported prefix operators.
     *
     * @return     The operators.
     */
    const Set<String>& prefixOperators() const noexcept
    {
        return m_prefixOperators;
    }

    /**
     * @brief      Add a prefix operator.
     *
     * @param      op    The operator.
     */
    void addPrefixOperator(String op)
    {
        m_prefixOperators.insert(std::move(op));
    }

    /**
     * @brief      Returns supported suffix operators.
     *
     * @return     The operators.
     */
    const Set<String>& postfixOperators() const noexcept
    {
        return m_postfixOperators;
    }

    /**
     * @brief      Add a postfix operator.
     *
     * @param      op    The operator.
     */
    void addPostfixOperator(String op)
    {
        m_postfixOperators.insert(std::move(op));
    }

    /**
     * @brief      Returns supported binary operators.
     *
     * @return     The operators.
     */
    const Set<String>& binaryOperators() const noexcept
    {
        return m_binaryOperators;
    }

    /**
     * @brief      Add a binary operator.
     *
     * @param      op    The operator.
     */
    void addBinaryOperator(String op)
    {
        m_binaryOperators.insert(std::move(op));
    }

    /**
     * @brief      Register statement parser.
     *
     * @param      start    The start token.
     * @param      handler  The handler.
     */
    void addStmtParser(String start, StmtHandler handler)
    {
        m_stmtParsers.emplace(std::move(start), std::move(handler));
    }

    /**
     * @brief      Returns current token.
     *
     * @return     Current token.
     *
     * @pre        `!isEmpty()`.
     */
    const tokenizer::Token& token() const noexcept
    {
        return *m_current;
    }

    /**
     * @brief      Advance to next token.
     *
     * @return     Current token.
     *
     * @pre        `!isEmpty()`.
     */
    const tokenizer::Token& next()
    {
        ++m_current;
        return token();
    }

    /**
     * @brief      If there is no more tokens.
     *
     * @return     True if tokenizer is empty, False otherwise.
     */
    bool isEmpty() const noexcept
    {
        return m_current == m_end;
    }

    /**
     * @brief      Test if current token is required type of token.
     *
     * @param      type  The token type.
     *
     * @return     If token type matches.
     *
     * @pre        `!isEmpty()`.
     */
    bool is(tokenizer::TokenType type) const noexcept
    {
        return token().type() == type;
    }

    /**
     * @brief      Test if current token is required type of token and value.
     *
     * @param      type   The token type.
     * @param      value  The value.
     *
     * @return     If token type matches.
     *
     * @pre        `!isEmpty()`.
     */
    bool is(tokenizer::TokenType type, const String& value) const noexcept
    {
        return token().type() == type && token().value() == value;
    }

    /**
     * @brief      Test if current token is number type.
     *
     * @return     If current token matches.
     *
     * @pre        `!isEmpty()`.
     */
    bool isNumber() const noexcept
    {
        return is(tokenizer::TokenType::NumberLiteral);
    }

    /**
     * @brief      Test if current token is string type.
     *
     * @return     If current token matches.
     *
     * @pre        `!isEmpty()`.
     */
    bool isString() const noexcept
    {
        return is(tokenizer::TokenType::NumberLiteral);
    }

    /**
     * @brief      Test if current token is character type.
     *
     * @return     If current token matches.
     *
     * @pre        `!isEmpty()`.
     */
    bool isCharacter() const noexcept
    {
        return is(tokenizer::TokenType::NumberLiteral);
    }

    /**
     * @brief      Test if current token is identifier type of token.
     *
     * @return     If token values matches.
     *
     * @pre        `!isEmpty()`.
     */
    bool isIdentifier() const noexcept
    {
        return is(tokenizer::TokenType::Identifier);
    }

    /**
     * @brief      Test if current token is identifier type of token and value.
     *
     * @param      value  The value.
     *
     * @return     If token values matches.
     *
     * @pre        `!isEmpty()`.
     */
    bool isIdentifier(const String& value) const noexcept
    {
        return is(tokenizer::TokenType::Identifier, value);
    }

    /**
     * @brief      Test if current token is other type of token and value.
     *
     * @param      value  The value.
     *
     * @return     If token values matches.
     *
     * @pre        `!isEmpty()`.
     */
    bool isOther(const String& value) const noexcept
    {
        return is(tokenizer::TokenType::Other, value);
    }

public:
    // Operations

    /**
     * @brief      Parse a integer literal from current state.
     *
     * @return     The parsed expr.
     *
     * @throws     ParserError  In case of parsing error.
     */
    ast::IntLiteralExpr parseIntLiteralExpr();

    /**
     * @brief      Parse an identifier expression from current state.
     *
     * @return     The parsed expr.
     *
     * @throws     ParserError  In case of parsing error.
     */
    ast::IdentifierExpr parseIdentifierExpr();

    /**
     * @brief      Parse a parenthesis expression from current state.
     *
     * @return     The parsed expr.
     *
     * @throws     ParserError  In case of parsing error.
     */
    ast::ParenExpr parseParenExpr();

    /**
     * @brief      Parse a primary expression from current state.
     *
     * @return     The parsed expr.
     *
     * @throws     ParserError  In case of parsing error.
     */
    ast::ExprPtr parsePrimaryExpr();

    /**
     * @brief      Parse a prefix expression from current state.
     *
     * @return     The parsed expr.
     *
     * @throws     ParserError  In case of parsing error.
     */
    ast::ExprPtr parsePrefixExpr();

    /**
     * @brief      Parse a postfix expression from current state.
     *
     * @return     The parsed expr.
     *
     * @throws     ParserError  In case of parsing error.
     */
    ast::ExprPtr parsePostfixExpr();

    /**
     * @brief      Parse a binary expression from current state.
     *
     * @return     The parsed expr.
     *
     * @throws     ParserError  In case of parsing error.
     */
    ast::ExprPtr parseBinaryExpr();

    /**
     * @brief      Parse an expression from current state.
     *
     * @return     The parsed expr.
     *
     * @throws     ParserError  In case of parsing error.
     */
    ast::ExprPtr parseExpr();

    /**
     * @brief      Parse a source from current state.
     *
     * @return     The result source.
     *
     * @throws     ParserError  In case of parsing error.
     */
    ast::Source parseSource();

    /**
     * @brief      Parse a statement from current state.
     *
     * @return     The parsed statement.
     *
     * @throws     ParserError  In case of parsing error.
     */
    ast::StmtPtr parseStmt();

    /**
     * @brief      Test if current token is required type and advance if is
     *             true.
     *
     * @param      type  The token type.
     *
     * @return     If current token matches.
     *
     * @pre        `!isEmpty()`.
     */
    bool match(tokenizer::TokenType type)
    {
        return match(is(type));
    }

    /**
     * @brief      Test if current token is required type and value and advance
     *             if is true.
     *
     * @param      type   The token type.
     * @param      value  The value.
     *
     * @return     If token type matches.
     *
     * @pre        `!isEmpty()`.
     */
    bool match(tokenizer::TokenType type, const String& value)
    {
        return match(is(type, value));
    }

    /**
     * @brief      Test if current token is number type and advance if is true.
     *
     * @return     If current token matches.
     *
     * @pre        `!isEmpty()`.
     */
    bool matchNumber()
    {
        return match(isNumber());
    }

    /**
     * @brief      Test if current token is string type and advance if is true.
     *
     * @return     If current token matches.
     *
     * @pre        `!isEmpty()`.
     */
    bool matchString()
    {
        return match(isString());
    }

    /**
     * @brief      Test if current token is character type and advance if is
     *             true.
     *
     * @return     If current token matches.
     *
     * @pre        `!isEmpty()`.
     */
    bool matchCharacter()
    {
        return match(isCharacter());
    }

    /**
     * @brief      Test if current token is identifier type and value and
     *             advance if is true.
     *
     * @return     If current token matches.
     *
     * @pre        `!isEmpty()`.
     */
    bool matchIdentifier()
    {
        return match(isIdentifier());
    }

    /**
     * @brief      Test if current token is identifier type and value and
     *             advance if is true.
     *
     * @param      value  The value.
     *
     * @return     If current token matches.
     *
     * @pre        `!isEmpty()`.
     */
    bool matchIdentifier(const String& value)
    {
        return match(isIdentifier(value));
    }

    /**
     * @brief      Test if current token is other type of token and value and
     *             advance if is true.
     *
     * @param      value  The value.
     *
     * @return     If token values matches.
     *
     * @pre        `!isEmpty()`.
     */
    bool matchOther(const String& value)
    {
        return match(isOther(value));
    }

    /**
     * @brief      Check if source is not empty.
     *
     * @throws     ParseError  If source is empty.
     */
    void checkEol()
    {
        if (isEmpty())
            throw ParseError("unexpected EOL", {});
    }

    /**
     * @brief      Check specified token and throw if token is not found.
     *
     * @param      type  The token type.
     *
     * @throws     ParseError  If current token doesn't match requirements.
     */
    void check(tokenizer::TokenType type)
    {
        check(is(type));
    }

    /**
     * @brief      Check specified token and throw if token is not found.
     *
     * @param      type   The token type.
     * @param      value  The value.
     *
     * @throws     ParseError  If current token doesn't match requirements.
     */
    void check(tokenizer::TokenType type, const String& value)
    {
        check(is(type, value));
    }

    /**
     * @brief      Check specified token and throw if token is not found.
     *
     * @throws     ParseError  If current token doesn't match requirements.
     */
    void checkNumber()
    {
        check(isNumber());
    }

    /**
     * @brief      Check specified token and throw if token is not found.
     *
     * @throws     ParseError  If current token doesn't match requirements.
     */
    void checkString()
    {
        check(isString());
    }

    /**
     * @brief      Check specified token and throw if token is not found.
     *
     * @throws     ParseError  If current token doesn't match requirements.
     */
    void checkCharacter()
    {
        check(isCharacter());
    }

    /**
     * @brief      Check specified token and throw if token is not found.
     *
     * @throws     ParseError  If current token doesn't match requirements.
     */
    void checkIdentifier()
    {
        check(isIdentifier());
    }

    /**
     * @brief      Check specified token and throw if token is not found.
     *
     * @param      value  The value.
     *
     * @throws     ParseError  If current token doesn't match requirements.
     */
    void checkIdentifier(const String& value)
    {
        check(isIdentifier(value));
    }

    /**
     * @brief      Check specified token and throw if token is not found.
     *
     * @param      value  The value.
     *
     * @throws     ParseError  If current token doesn't match requirements.
     */
    void checkOther(const String& value)
    {
        check(!isOther(value));
    }

    /**
     * @brief      Require specified token and throw if token is not found and
     *             advance if is true.
     *
     * @param      type  The token type.
     *
     * @throws     ParseError  If current token doesn't match requirements.
     */
    void require(tokenizer::TokenType type)
    {
        check(match(type));
    }

    /**
     * @brief      Require specified token and throw if token is not found and
     *             advance if is true.
     *
     * @param      type   The token type.
     * @param      value  The value.
     *
     * @throws     ParseError  If current token doesn't match requirements.
     */
    void require(tokenizer::TokenType type, const String& value)
    {
        check(match(type, value));
    }

    /**
     * @brief      Require specified token and throw if token is not found and
     *             advance if is true.
     *
     * @throws     ParseError  If current token doesn't match requirements.
     */
    void requireNumber()
    {
        check(matchNumber());
    }

    /**
     * @brief      Require specified token and throw if token is not found and
     *             advance if is true.
     *
     * @throws     ParseError  If current token doesn't match requirements.
     */
    void requireString()
    {
        check(matchString());
    }

    /**
     * @brief      Require specified token and throw if token is not found and
     *             advance if is true.
     *
     * @throws     ParseError  If current token doesn't match requirements.
     */
    void requireCharacter()
    {
        check(matchCharacter());
    }

    /**
     * @brief      Require specified token and throw if token is not found and
     *             advance if is true.
     *
     * @throws     ParseError  If current token doesn't match requirements.
     */
    void requireIdentifier()
    {
        check(matchIdentifier());
    }

    /**
     * @brief      Require specified token and throw if token is not found and
     *             advance if is true.
     *
     * @param      value  The value.
     *
     * @throws     ParseError  If current token doesn't match requirements.
     */
    void requireIdentifier(const String& value)
    {
        check(matchIdentifier(value));
    }

    /**
     * @brief      Require specified token and throw if token is not found and
     *             advance if is true.
     *
     * @param      value  The value.
     *
     * @throws     ParseError  If current token doesn't match requirements.
     */
    void requireOther(const String& value)
    {
        check(matchOther(value));
    }

    /**
     * @brief      Check if current token is prefix operator.
     *
     * @return     True if prefix operator, False otherwise.
     */
    bool isPrefixOperator() const noexcept
    {
        return m_prefixOperators.count(m_current->value()) > 0;
    }

    /**
     * @brief      Check if current token is postfix operator.
     *
     * @return     True if postfix operator, False otherwise.
     */
    bool isPostfixOperator() const noexcept
    {
        return m_postfixOperators.count(m_current->value()) > 0;
    }

    /**
     * @brief      Check if current token is binary operator.
     *
     * @return     True if binary operator, False otherwise.
     */
    bool isBinaryOperator() const noexcept
    {
        return m_binaryOperators.count(m_current->value()) > 0;
    }

private:
    // Operations

    /**
     * @brief      Advance or not depending on given value.
     *
     * @param      check  The check if parser should advance or not.
     *
     * @return     `check`.
     *
     * @pre        `!isEmpty()`.
     */
    bool match(bool check)
    {
        if (check)
            next();

        return check;
    }

    /**
     * @brief      Check specified token and throw if token doesn't match.
     *
     * @param      check  The check if function should not throw.
     *
     * @throws     ParseError  If current token doesn't match requirements.
     */
    void check(bool check)
    {
        if (!check)
        {
            throw ParseError(
                "unexpected token '" + m_current->value() + "'",
                m_current->location());
        }
    }

private:
    // Types

    /// Internal iterator
    using Iterator = tokenizer::TokenFilterIterator<
        tokenizer::TokenType::Comment,
        tokenizer::TokenType::WhiteSpace>;

private:
    // Data Members

    /// Current position
    Iterator m_current;

    /// End position
    Iterator m_end;

    /// A set of prefix operators.
    Set<String> m_prefixOperators;

    /// A set of postfix operators.
    Set<String> m_postfixOperators;

    /// A set of binary operators.
    Set<String> m_binaryOperators;

    /// Statement handlers.
    Map<String, StmtHandler> m_stmtParsers;
};

/* ************************************************************************* */

} // namespace shard::parser

/* ************************************************************************* */
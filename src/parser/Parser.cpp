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

#include "shard/parser/Parser.hpp"

/* ************************************************************************* */

namespace shard::parser {

/* ************************************************************************* */

namespace {

/* ************************************************************************* */

/**
 * @brief      Calculate node end location from start location and token value.
 *
 * @param      start  The start location.
 * @param      value  The token value.
 *
 * @return     End location.
 */
SourceLocation endLocation(const SourceLocation& start, const String& value)
{
    return {start.line(), start.column() + int(value.size())};
}

/* ************************************************************************* */

} // namespace

/* ************************************************************************* */

ast::IntLiteralExpr Parser::parseIntLiteralExpr()
{
    checkEol();

    // Must be number
    check(tokenizer::TokenType::NumberLiteral);

    auto value = std::stoi(token().value());
    auto start = token().location();
    auto end   = endLocation(start, token().value());

    next();

    return ast::IntLiteralExpr{value, {start, end}};
}

/* ************************************************************************* */

ast::IdentifierExpr Parser::parseIdentifierExpr()
{
    checkEol();

    // Must be identifier
    check(tokenizer::TokenType::Identifier);

    auto value = token().value();
    auto start = token().location();
    auto end   = endLocation(start, token().value());

    next();

    return ast::IdentifierExpr{value, {start, end}};
}

/* ************************************************************************* */

ast::ParenExpr Parser::parseParenExpr()
{
    checkEol();

    // "(", EXPRESSION, ")"

    auto start = token().location();

    requireOther("(");

    // Parse expression
    auto expr = parseExpr();

    requireOther(")");

    auto cur = token().location();
    auto end = endLocation(cur, token().value());

    return ast::ParenExpr{std::move(expr), {start, end}};
}

/* ************************************************************************* */

ast::ExprPtr Parser::parsePrimaryExpr()
{
    checkEol();

    // IDENTIFIER_EXPRESSION
    if (is(tokenizer::TokenType::Identifier))
    {
        return make<ast::IdentifierExpr>(parseIdentifierExpr());
    }
    // LITERAL_EXPRESSION
    else if (is(tokenizer::TokenType::NumberLiteral))
    {
        return make<ast::IntLiteralExpr>(parseIntLiteralExpr());
    }
    // PAREN_EXPRESSION
    else if (isOther("("))
    {
        return make<ast::ParenExpr>(parseParenExpr());
    }
    // Unknown
    else
    {
        throw ParseError("unsupported expression", token().location());
    }
}

/* ************************************************************************* */

ast::ExprPtr Parser::parsePrefixExpr()
{
    checkEol();

    auto start = token().location();

    if (!isPrefixOperator())
        return parsePostfixExpr();

    auto op = token().value();
    next();

    // Parse another expression
    auto expr = parsePrefixExpr();

    auto cur = token().location();
    auto end = endLocation(cur, token().value());

    return make<ast::PrefixUnaryExpr>(
        std::move(op), std::move(expr), SourceRange{start, end});
}

/* ************************************************************************* */

ast::ExprPtr Parser::parsePostfixExpr()
{
    checkEol();

    auto start = token().location();

    // Primary expression
    ast::ExprPtr expr = parsePrimaryExpr();

    // Additinal postfix operators
    while (!isEmpty() && isPostfixOperator())
    {
        auto op  = token().value();
        auto cur = token().location();
        auto end = endLocation(cur, token().value());

        next();

        expr = make<ast::PostfixUnaryExpr>(
            std::move(expr), std::move(op), SourceRange{start, end});
    }

    // Function call
    if (matchOther("("))
    {
        // Create function call
        expr = make<ast::FunctionCallExpr>(std::move(expr), parseExprList(")"));
    }
    else if (matchOther("["))
    {
        expr = make<ast::SubscriptExpr>(std::move(expr), parseExprList("]"));
    }

    return expr;
}

/* ************************************************************************* */

ast::ExprPtr Parser::parseBinaryExpr()
{
    checkEol();

    auto start = token().location();

    // Parse prefix operator
    auto expr1 = parsePrefixExpr();

    if (isBinaryOperator())
    {
        auto op = token().value();
        next();

        auto expr2 = parseBinaryExpr();

        auto end = expr2->sourceRange().end();

        return make<ast::BinaryExpr>(
            std::move(op),
            std::move(expr1),
            std::move(expr2),
            SourceRange{start, end});
    }
    else
    {
        return expr1;
    }
}

/* ************************************************************************* */

ast::ExprPtr Parser::parseExpr()
{
    return parseBinaryExpr();
}

/* ************************************************************************* */

ast::Source Parser::parseSource()
{
    ast::StmtPtrVector stmts;

    while (!isEmpty())
        stmts.push_back(parseStmt());

    return ast::Source{std::move(stmts)};
}

/* ************************************************************************* */

ast::StmtPtr Parser::parseStmt()
{
    checkEol();

    // Find handler
    auto it = m_stmtParsers.find(token().value());

    if (it != m_stmtParsers.end())
    {
        return it->second(*this);
    }
    else
    {
        // Parse expression
        auto expr = parseExpr();

        // Must be terminated by semicolon
        requireOther(";");

        return make<ast::ExprStmt>(std::move(expr));
    }
}

/* ************************************************************************* */

ast::ExprPtrVector Parser::parseExprList(const String& term)
{
    // Parse arguments
    return parseList(
        [this] { return parseExpr(); },
        [this, &term] { return isOther(term); },
        [this] { requireOther(","); });
}

/* ************************************************************************* */

} // namespace shard::parser

/* ************************************************************************* */

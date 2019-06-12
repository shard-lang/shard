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

// Google test
#include "gtest/gtest.h"

// Shard
#include "shard/parser/Parser.hpp"
#include "shard/parser/exceptions.hpp"

/* ************************************************************************* */

using namespace shard;
using namespace shard::ast;
using namespace shard::parser;

/* ************************************************************************ */

namespace shard {

/* ************************************************************************ */

::std::ostream& operator<<(::std::ostream& os, const SourceLocation& loc)
{
    return os << loc.line() << ":" << loc.column();
}

/* ************************************************************************ */

} // namespace shard

/* ************************************************************************* */

TEST(Parser, intLiteral)
{
    {
        tokenizer::Source source("0");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        auto literal = parser.parseIntLiteralExpr();
        EXPECT_EQ(literal.value(), 0);
        EXPECT_EQ(literal.sourceRange().start(), (SourceLocation{1, 1}));
        EXPECT_EQ(literal.sourceRange().end(), (SourceLocation{1, 2}));

        EXPECT_TRUE(parser.isEmpty());
    }

    {
        tokenizer::Source source("1246479");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        auto literal = parser.parseIntLiteralExpr();
        EXPECT_EQ(literal.value(), 1246479);
        EXPECT_EQ(literal.sourceRange().start(), (SourceLocation{1, 1}));
        EXPECT_EQ(literal.sourceRange().end(), (SourceLocation{1, 8}));

        EXPECT_TRUE(parser.isEmpty());
    }

    // Empty
    {
        tokenizer::Source source("");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        EXPECT_THROW(parser.parseIntLiteralExpr(), ParseError);
    }

    // Other
    {
        tokenizer::Source source("hello");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        EXPECT_THROW(parser.parseIntLiteralExpr(), ParseError);
    }
}

/* ************************************************************************* */

TEST(Parser, identifier)
{
    {
        tokenizer::Source source("val");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        auto literal = parser.parseIdentifierExpr();
        EXPECT_EQ(literal.name(), "val");
        EXPECT_EQ(literal.sourceRange().start(), (SourceLocation{1, 1}));
        EXPECT_EQ(literal.sourceRange().end(), (SourceLocation{1, 4}));

        EXPECT_TRUE(parser.isEmpty());
    }

    {
        tokenizer::Source source("hello");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        auto literal = parser.parseIdentifierExpr();
        EXPECT_EQ(literal.name(), "hello");
        EXPECT_EQ(literal.sourceRange().start(), (SourceLocation{1, 1}));
        EXPECT_EQ(literal.sourceRange().end(), (SourceLocation{1, 6}));

        EXPECT_TRUE(parser.isEmpty());
    }

    // Empty
    {
        tokenizer::Source source("");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        EXPECT_THROW(parser.parseIdentifierExpr(), ParseError);
    }

    // Other
    {
        tokenizer::Source source("0124");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        EXPECT_THROW(parser.parseIdentifierExpr(), ParseError);
    }
}

/* ************************************************************************* */

TEST(Parser, parenExpr)
{
    {
        tokenizer::Source source("(0)");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        auto expr = parser.parseParenExpr();
        EXPECT_EQ(expr.sourceRange().start(), (SourceLocation{1, 1}));
        EXPECT_EQ(expr.sourceRange().end(), (SourceLocation{1, 4}));

        EXPECT_TRUE(parser.isEmpty());
    }

    // Different
    {
        tokenizer::Source source("{0}");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        EXPECT_THROW(parser.parseParenExpr(), ParseError);
    }

    // Mismatch
    {
        tokenizer::Source source("(0}");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        EXPECT_THROW(parser.parseParenExpr(), ParseError);
    }

    // Unclosed
    {
        tokenizer::Source source("(0");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        EXPECT_THROW(parser.parseParenExpr(), ParseError);
    }

    // Empty
    {
        tokenizer::Source source("");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        EXPECT_THROW(parser.parseParenExpr(), ParseError);
    }

    // Invalid
    {
        tokenizer::Source source("0");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        EXPECT_THROW(parser.parseParenExpr(), ParseError);
    }
}

/* ************************************************************************* */

TEST(Parser, primaryExpr)
{
    // Identifier
    {
        tokenizer::Source source("variable");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        auto expr = parser.parsePrimaryExpr();
        EXPECT_EQ(expr->sourceRange().start(), (SourceLocation{1, 1}));
        EXPECT_EQ(expr->sourceRange().end(), (SourceLocation{1, 9}));

        ASSERT_TRUE(expr->is<ast::IdentifierExpr>());

        auto& identifier = expr->cast<ast::IdentifierExpr>();
        EXPECT_EQ(identifier.name(), "variable");

        EXPECT_TRUE(parser.isEmpty());
    }

    // IntLiteral
    {
        tokenizer::Source source("305");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        auto expr = parser.parsePrimaryExpr();
        EXPECT_EQ(expr->sourceRange().start(), (SourceLocation{1, 1}));
        EXPECT_EQ(expr->sourceRange().end(), (SourceLocation{1, 4}));

        ASSERT_TRUE(expr->is<ast::IntLiteralExpr>());

        auto& integer = expr->cast<ast::IntLiteralExpr>();
        EXPECT_EQ(integer.value(), 305);

        EXPECT_TRUE(parser.isEmpty());
    }

    // Parent
    {
        tokenizer::Source source("(0)");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        auto expr = parser.parsePrimaryExpr();
        EXPECT_EQ(expr->sourceRange().start(), (SourceLocation{1, 1}));
        EXPECT_EQ(expr->sourceRange().end(), (SourceLocation{1, 4}));

        ASSERT_TRUE(expr->is<ast::ParenExpr>());
        auto& paren = expr->cast<ast::ParenExpr>();

        auto& child = paren.expr();
        ASSERT_TRUE(child->is<ast::IntLiteralExpr>());
        EXPECT_EQ(child->sourceRange().start(), (SourceLocation{1, 2}));
        EXPECT_EQ(child->sourceRange().end(), (SourceLocation{1, 3}));

        auto& integer = child->cast<ast::IntLiteralExpr>();
        EXPECT_EQ(integer.value(), 0);

        EXPECT_TRUE(parser.isEmpty());
    }

    // Empty
    {
        tokenizer::Source source("");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        EXPECT_THROW(parser.parsePrimaryExpr(), ParseError);
    }

    // Unsupported
    {
        tokenizer::Source source("{}");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        EXPECT_THROW(parser.parsePrimaryExpr(), ParseError);
    }
}

/* ************************************************************************* */

TEST(Parser, prefixExpr)
{
    // None
    {
        tokenizer::Source source("305");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        auto expr = parser.parsePrefixExpr();
        EXPECT_EQ(expr->sourceRange().start(), (SourceLocation{1, 1}));
        EXPECT_EQ(expr->sourceRange().end(), (SourceLocation{1, 4}));

        ASSERT_TRUE(expr->is<ast::IntLiteralExpr>());

        auto& integer = expr->cast<ast::IntLiteralExpr>();
        EXPECT_EQ(integer.value(), 305);

        EXPECT_TRUE(parser.isEmpty());
    }

    // Single
    {
        tokenizer::Source source("!1");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        // Not operator
        parser.addPrefixOperator("!");

        auto expr = parser.parsePrefixExpr();
        EXPECT_EQ(expr->sourceRange().start(), (SourceLocation{1, 1}));
        EXPECT_EQ(expr->sourceRange().end(), (SourceLocation{1, 3}));

        ASSERT_TRUE(expr->is<ast::PrefixUnaryExpr>());
        auto& unary = expr->cast<ast::PrefixUnaryExpr>();

        EXPECT_EQ(unary.op(), "!");

        ASSERT_TRUE(unary.expr()->is<ast::IntLiteralExpr>());
        auto& integer = unary.expr()->cast<ast::IntLiteralExpr>();
        EXPECT_EQ(integer.sourceRange().start(), (SourceLocation{1, 2}));
        EXPECT_EQ(integer.sourceRange().end(), (SourceLocation{1, 3}));

        EXPECT_EQ(integer.value(), 1);

        EXPECT_TRUE(parser.isEmpty());
    }

    // Multiple
    {
        tokenizer::Source source("?!1");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        // Operators
        parser.addPrefixOperator("!");
        parser.addPrefixOperator("?");

        auto expr = parser.parsePrefixExpr();
        EXPECT_EQ(expr->sourceRange().start(), (SourceLocation{1, 1}));
        EXPECT_EQ(expr->sourceRange().end(), (SourceLocation{1, 4}));

        ASSERT_TRUE(expr->is<ast::PrefixUnaryExpr>());
        auto& unary1 = expr->cast<ast::PrefixUnaryExpr>();

        EXPECT_EQ(unary1.op(), "?");

        ASSERT_TRUE(unary1.expr()->is<ast::PrefixUnaryExpr>());
        auto& unary2 = unary1.expr()->cast<ast::PrefixUnaryExpr>();
        EXPECT_EQ(unary2.sourceRange().start(), (SourceLocation{1, 2}));
        EXPECT_EQ(unary2.sourceRange().end(), (SourceLocation{1, 4}));

        EXPECT_EQ(unary2.op(), "!");

        ASSERT_TRUE(unary2.expr()->is<ast::IntLiteralExpr>());
        auto& integer = unary2.expr()->cast<ast::IntLiteralExpr>();
        EXPECT_EQ(integer.sourceRange().start(), (SourceLocation{1, 3}));
        EXPECT_EQ(integer.sourceRange().end(), (SourceLocation{1, 4}));

        EXPECT_EQ(integer.value(), 1);

        EXPECT_TRUE(parser.isEmpty());
    }

    // Empty
    {
        tokenizer::Source source("");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        EXPECT_THROW(parser.parsePrefixExpr(), ParseError);
    }

    // Unsupported
    {
        tokenizer::Source source("{}");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        EXPECT_THROW(parser.parsePrefixExpr(), ParseError);
    }
}

/* ************************************************************************* */

TEST(Parser, postfixExpr)
{
    // None
    {
        tokenizer::Source source("305");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        auto expr = parser.parsePostfixExpr();
        EXPECT_EQ(expr->sourceRange().start(), (SourceLocation{1, 1}));
        EXPECT_EQ(expr->sourceRange().end(), (SourceLocation{1, 4}));

        ASSERT_TRUE(expr->is<ast::IntLiteralExpr>());

        auto& integer = expr->cast<ast::IntLiteralExpr>();
        EXPECT_EQ(integer.value(), 305);

        EXPECT_TRUE(parser.isEmpty());
    }

    // Single
    {
        tokenizer::Source source("1?");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        // Increment operator
        parser.addPostfixOperator("?");

        auto expr = parser.parsePostfixExpr();
        EXPECT_EQ(expr->sourceRange().start(), (SourceLocation{1, 1}));
        EXPECT_EQ(expr->sourceRange().end(), (SourceLocation{1, 3}));

        ASSERT_TRUE(expr->is<ast::PostfixUnaryExpr>());
        auto& unary = expr->cast<ast::PostfixUnaryExpr>();

        EXPECT_EQ(unary.op(), "?");

        ASSERT_TRUE(unary.expr()->is<ast::IntLiteralExpr>());
        auto& integer = unary.expr()->cast<ast::IntLiteralExpr>();
        EXPECT_EQ(integer.sourceRange().start(), (SourceLocation{1, 1}));
        EXPECT_EQ(integer.sourceRange().end(), (SourceLocation{1, 2}));

        EXPECT_EQ(integer.value(), 1);

        EXPECT_TRUE(parser.isEmpty());
    }

    // Multiple
    {
        tokenizer::Source source("1?!");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        // Operators
        parser.addPostfixOperator("?");
        parser.addPostfixOperator("!");

        auto expr = parser.parsePostfixExpr();
        EXPECT_EQ(expr->sourceRange().start(), (SourceLocation{1, 1}));
        EXPECT_EQ(expr->sourceRange().end(), (SourceLocation{1, 4}));

        ASSERT_TRUE(expr->is<ast::PostfixUnaryExpr>());
        auto& unary1 = expr->cast<ast::PostfixUnaryExpr>();

        EXPECT_EQ(unary1.op(), "!");

        ASSERT_TRUE(unary1.expr()->is<ast::PostfixUnaryExpr>());
        auto& unary2 = unary1.expr()->cast<ast::PostfixUnaryExpr>();
        EXPECT_EQ(unary2.sourceRange().start(), (SourceLocation{1, 1}));
        EXPECT_EQ(unary2.sourceRange().end(), (SourceLocation{1, 3}));

        EXPECT_EQ(unary2.op(), "?");

        ASSERT_TRUE(unary2.expr()->is<ast::IntLiteralExpr>());
        auto& integer = unary2.expr()->cast<ast::IntLiteralExpr>();
        EXPECT_EQ(integer.sourceRange().start(), (SourceLocation{1, 1}));
        EXPECT_EQ(integer.sourceRange().end(), (SourceLocation{1, 2}));

        EXPECT_EQ(integer.value(), 1);

        EXPECT_TRUE(parser.isEmpty());
    }

    // Empty
    {
        tokenizer::Source source("");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        EXPECT_THROW(parser.parsePostfixExpr(), ParseError);
    }

    // Unsupported
    {
        tokenizer::Source source("{}");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        EXPECT_THROW(parser.parsePostfixExpr(), ParseError);
    }
}

/* ************************************************************************* */

TEST(Parser, binaryExpr)
{
    // None
    {
        tokenizer::Source source("305");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        auto expr = parser.parseBinaryExpr();
        EXPECT_EQ(expr->sourceRange().start(), (SourceLocation{1, 1}));
        EXPECT_EQ(expr->sourceRange().end(), (SourceLocation{1, 4}));

        ASSERT_TRUE(expr->is<ast::IntLiteralExpr>());

        auto& integer = expr->cast<ast::IntLiteralExpr>();
        EXPECT_EQ(integer.value(), 305);

        EXPECT_TRUE(parser.isEmpty());
    }

    // Single
    {
        tokenizer::Source source("1 + 2");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        // Add operator
        parser.addBinaryOperator("+");

        auto expr = parser.parseBinaryExpr();
        EXPECT_EQ(expr->sourceRange().start(), (SourceLocation{1, 1}));
        EXPECT_EQ(expr->sourceRange().end(), (SourceLocation{1, 6}));

        ASSERT_TRUE(expr->is<ast::BinaryExpr>());
        auto& binary = expr->cast<ast::BinaryExpr>();

        EXPECT_EQ(binary.op(), "+");

        ASSERT_TRUE(binary.lhs()->is<ast::IntLiteralExpr>());
        auto& integer1 = binary.lhs()->cast<ast::IntLiteralExpr>();
        EXPECT_EQ(integer1.sourceRange().start(), (SourceLocation{1, 1}));
        EXPECT_EQ(integer1.sourceRange().end(), (SourceLocation{1, 2}));
        EXPECT_EQ(integer1.value(), 1);

        ASSERT_TRUE(binary.rhs()->is<ast::IntLiteralExpr>());
        auto& integer2 = binary.rhs()->cast<ast::IntLiteralExpr>();
        EXPECT_EQ(integer2.sourceRange().start(), (SourceLocation{1, 5}));
        EXPECT_EQ(integer2.sourceRange().end(), (SourceLocation{1, 6}));
        EXPECT_EQ(integer2.value(), 2);

        EXPECT_TRUE(parser.isEmpty());
    }

    // Single
    {
        tokenizer::Source source("val = 5 + 2 * 3");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        // Operators
        parser.addBinaryOperator("+");
        parser.addBinaryOperator("*");
        parser.addBinaryOperator("=");

        auto expr = parser.parseBinaryExpr();
        EXPECT_EQ(expr->sourceRange().start(), (SourceLocation{1, 1}));
        EXPECT_EQ(expr->sourceRange().end(), (SourceLocation{1, 16}));

        ASSERT_TRUE(expr->is<ast::BinaryExpr>());
        auto& binary1 = expr->cast<ast::BinaryExpr>();

        EXPECT_EQ(binary1.op(), "=");

        ASSERT_TRUE(binary1.lhs()->is<ast::IdentifierExpr>());
        auto& id1 = binary1.lhs()->cast<ast::IdentifierExpr>();
        EXPECT_EQ(id1.sourceRange().start(), (SourceLocation{1, 1}));
        EXPECT_EQ(id1.sourceRange().end(), (SourceLocation{1, 4}));
        EXPECT_EQ(id1.name(), "val");

        ASSERT_TRUE(binary1.rhs()->is<ast::BinaryExpr>());
        auto& binary2 = binary1.rhs()->cast<ast::BinaryExpr>();

        EXPECT_EQ(binary2.op(), "+");

        ASSERT_TRUE(binary2.lhs()->is<ast::IntLiteralExpr>());
        auto& integer1 = binary2.lhs()->cast<ast::IntLiteralExpr>();
        EXPECT_EQ(integer1.sourceRange().start(), (SourceLocation{1, 7}));
        EXPECT_EQ(integer1.sourceRange().end(), (SourceLocation{1, 8}));
        EXPECT_EQ(integer1.value(), 5);

        ASSERT_TRUE(binary2.rhs()->is<ast::BinaryExpr>());
        auto& binary3 = binary2.rhs()->cast<ast::BinaryExpr>();

        EXPECT_EQ(binary3.op(), "*");

        ASSERT_TRUE(binary3.lhs()->is<ast::IntLiteralExpr>());
        auto& integer2 = binary3.lhs()->cast<ast::IntLiteralExpr>();
        EXPECT_EQ(integer2.sourceRange().start(), (SourceLocation{1, 11}));
        EXPECT_EQ(integer2.sourceRange().end(), (SourceLocation{1, 12}));
        EXPECT_EQ(integer2.value(), 2);

        ASSERT_TRUE(binary3.rhs()->is<ast::IntLiteralExpr>());
        auto& integer3 = binary3.rhs()->cast<ast::IntLiteralExpr>();
        EXPECT_EQ(integer3.sourceRange().start(), (SourceLocation{1, 15}));
        EXPECT_EQ(integer3.sourceRange().end(), (SourceLocation{1, 16}));
        EXPECT_EQ(integer3.value(), 3);

        EXPECT_TRUE(parser.isEmpty());
    }

    // Empty
    {
        tokenizer::Source source("");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        EXPECT_THROW(parser.parseBinaryExpr(), ParseError);
    }

    // Unsupported
    {
        tokenizer::Source source("{}");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        EXPECT_THROW(parser.parseBinaryExpr(), ParseError);
    }
}

/* ************************************************************************* */

TEST(Parser, expr)
{
    // Identifier
    {
        tokenizer::Source source("variable");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        auto expr = parser.parseExpr();
        EXPECT_EQ(expr->sourceRange().start(), (SourceLocation{1, 1}));
        EXPECT_EQ(expr->sourceRange().end(), (SourceLocation{1, 9}));

        ASSERT_TRUE(expr->is<ast::IdentifierExpr>());

        auto& identifier = expr->cast<ast::IdentifierExpr>();
        EXPECT_EQ(identifier.name(), "variable");

        EXPECT_TRUE(parser.isEmpty());
    }

    // IntLiteral
    {
        tokenizer::Source source("305");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        auto expr = parser.parseExpr();
        EXPECT_EQ(expr->sourceRange().start(), (SourceLocation{1, 1}));
        EXPECT_EQ(expr->sourceRange().end(), (SourceLocation{1, 4}));

        ASSERT_TRUE(expr->is<ast::IntLiteralExpr>());

        auto& integer = expr->cast<ast::IntLiteralExpr>();
        EXPECT_EQ(integer.value(), 305);

        EXPECT_TRUE(parser.isEmpty());
    }

    // Parent
    {
        tokenizer::Source source("(0)");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        auto expr = parser.parseExpr();
        EXPECT_EQ(expr->sourceRange().start(), (SourceLocation{1, 1}));
        EXPECT_EQ(expr->sourceRange().end(), (SourceLocation{1, 4}));

        EXPECT_TRUE(parser.isEmpty());
    }

    // Prefix
    {
        tokenizer::Source source("!1");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        // Not operator
        parser.addPrefixOperator("!");

        auto expr = parser.parseExpr();
        EXPECT_EQ(expr->sourceRange().start(), (SourceLocation{1, 1}));
        EXPECT_EQ(expr->sourceRange().end(), (SourceLocation{1, 3}));

        ASSERT_TRUE(expr->is<ast::PrefixUnaryExpr>());
        auto& unary = expr->cast<ast::PrefixUnaryExpr>();

        EXPECT_EQ(unary.op(), "!");

        ASSERT_TRUE(unary.expr()->is<ast::IntLiteralExpr>());
        auto& integer = unary.expr()->cast<ast::IntLiteralExpr>();

        EXPECT_EQ(integer.value(), 1);

        EXPECT_TRUE(parser.isEmpty());
    }

    // Postfix
    {
        tokenizer::Source source("1?");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        // Increment operator
        parser.addPostfixOperator("?");

        auto expr = parser.parseExpr();
        EXPECT_EQ(expr->sourceRange().start(), (SourceLocation{1, 1}));
        EXPECT_EQ(expr->sourceRange().end(), (SourceLocation{1, 3}));

        ASSERT_TRUE(expr->is<ast::PostfixUnaryExpr>());
        auto& unary = expr->cast<ast::PostfixUnaryExpr>();

        EXPECT_EQ(unary.op(), "?");

        ASSERT_TRUE(unary.expr()->is<ast::IntLiteralExpr>());
        auto& integer = unary.expr()->cast<ast::IntLiteralExpr>();
        EXPECT_EQ(integer.sourceRange().start(), (SourceLocation{1, 1}));
        EXPECT_EQ(integer.sourceRange().end(), (SourceLocation{1, 2}));

        EXPECT_EQ(integer.value(), 1);

        EXPECT_TRUE(parser.isEmpty());
    }

    // Binary
    {
        tokenizer::Source source("1 + 2");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        // Add operator
        parser.addBinaryOperator("+");

        auto expr = parser.parseExpr();
        EXPECT_EQ(expr->sourceRange().start(), (SourceLocation{1, 1}));
        EXPECT_EQ(expr->sourceRange().end(), (SourceLocation{1, 6}));

        ASSERT_TRUE(expr->is<ast::BinaryExpr>());
        auto& binary = expr->cast<ast::BinaryExpr>();

        EXPECT_EQ(binary.op(), "+");

        ASSERT_TRUE(binary.lhs()->is<ast::IntLiteralExpr>());
        auto& integer1 = binary.lhs()->cast<ast::IntLiteralExpr>();
        EXPECT_EQ(integer1.value(), 1);

        ASSERT_TRUE(binary.rhs()->is<ast::IntLiteralExpr>());
        auto& integer2 = binary.rhs()->cast<ast::IntLiteralExpr>();
        EXPECT_EQ(integer2.value(), 2);

        EXPECT_TRUE(parser.isEmpty());
    }

    // Empty
    {
        tokenizer::Source source("");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        EXPECT_THROW(parser.parseExpr(), ParseError);
    }

    // Unsupported
    {
        tokenizer::Source source("{}");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        EXPECT_THROW(parser.parseExpr(), ParseError);
    }
}

/* ************************************************************************* */

TEST(Parser, stmt)
{
    // Expression
    {
        tokenizer::Source source("5 + 2;");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        parser.addBinaryOperator("+");

        auto stmt = parser.parseStmt();

        ASSERT_TRUE(stmt->is<ast::ExprStmt>());
        auto& exprStmt = stmt->cast<ast::ExprStmt>();

        EXPECT_TRUE(exprStmt.expr()->is<ast::BinaryExpr>());

        EXPECT_TRUE(parser.isEmpty());
    }

    // Compound
    {
        tokenizer::Source source("{}");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        parser.addStmtParser("{", [](auto& parser) {
            parser.requireOther("{");

            ast::StmtPtrVector stmts;

            while (!parser.isEmpty() && !parser.isOther("}"))
                stmts.push_back(parser.parseStmt());

            parser.requireOther("}");

            return makeUnique<ast::CompoundStmt>(std::move(stmts));
        });

        auto stmt = parser.parseStmt();

        ASSERT_TRUE(stmt->is<ast::CompoundStmt>());
        auto& compound = stmt->cast<ast::CompoundStmt>();

        EXPECT_TRUE(compound.stmts().empty());

        EXPECT_TRUE(parser.isEmpty());
    }

    // Multiple
    {
        tokenizer::Source source("{ var i = 10; }");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        parser.addStmtParser("{", [](auto& parser) {
            parser.requireOther("{");

            ast::StmtPtrVector stmts;

            while (!parser.isEmpty() && !parser.isOther("}"))
                stmts.push_back(parser.parseStmt());

            parser.requireOther("}");

            return makeUnique<ast::CompoundStmt>(std::move(stmts));
        });

        // Variable declaration
        parser.addStmtParser("var", [](auto& parser) {
            parser.requireIdentifier("var");
            parser.checkIdentifier();

            auto name = parser.token().value();

            parser.next();
            parser.requireOther("=");

            // Initializer
            auto expr = parser.parseExpr();

            parser.requireOther(";");

            auto decl = makeUnique<ast::VariableDecl>("Any", std::move(name));

            return makeUnique<ast::DeclStmt>(std::move(decl));
        });

        auto stmt = parser.parseStmt();

        ASSERT_TRUE(stmt->is<ast::CompoundStmt>());
        const auto& compound = stmt->cast<ast::CompoundStmt>();

        ASSERT_EQ(compound.stmts().size(), 1);
        const auto& stmts = compound.stmts();

        ASSERT_TRUE(stmts[0]->is<ast::DeclStmt>());
        const auto& declStmt = stmts[0]->cast<ast::DeclStmt>();

        EXPECT_EQ(declStmt.decl()->name(), "i");

        EXPECT_TRUE(parser.isEmpty());
    }

    // Empty
    {
        tokenizer::Source source("");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        EXPECT_THROW(parser.parseStmt(), ParseError);
    }
}

/* ************************************************************************* */

TEST(Parser, source)
{
    // Expression
    {
        tokenizer::Source source("5 + 2; 2 * 9;");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        parser.addBinaryOperator("+");
        parser.addBinaryOperator("*");

        auto stmt = parser.parseSource();

        EXPECT_EQ(stmt.stmts().size(), 2);

        EXPECT_TRUE(parser.isEmpty());
    }

    // Empty
    {
        tokenizer::Source source("");
        tokenizer::Tokenizer tokenizer(source);
        Parser parser(tokenizer);

        auto src = parser.parseSource();

        EXPECT_TRUE(src.stmts().empty());

        EXPECT_TRUE(parser.isEmpty());
    }
}

/* ************************************************************************* */

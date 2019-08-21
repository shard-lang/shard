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

#include "shard/builtin/Parser.hpp"

/* ************************************************************************* */

namespace shard::builtin {

/* ************************************************************************* */

namespace {

/* ************************************************************************* */

/**
 * @brief      Parse compound statement.
 *
 * @param      parser  The parser.
 *
 * @return     Parsed statement.
 */
ast::CompoundStmtPtr parseCompoundStmt(parser::Parser& parser)
{
    auto start = parser.location();
    parser.requireOther("{");

    ast::StmtPtrVector stmts;

    while (!parser.isEmpty() && !parser.isOther("}"))
        stmts.push_back(parser.parseStmt());

    auto end = parser.location();
    parser.requireOther("}");

    return makeUnique<ast::CompoundStmt>(
        std::move(stmts), SourceRange{start, end});
}

/* ************************************************************************* */

/**
 * @brief      Parse declaration.
 *
 * @param      parser  The parser.
 *
 * @return     Parsed statement.
 */
UniquePtr<ast::VariableDecl> parseVariableDecl(parser::Parser& parser)
{
    auto start = parser.location();

    parser.checkIdentifier();
    auto name = parser.token().value();
    parser.next();

    auto end = parser.location();

    return makeUnique<ast::VariableDecl>(
        "Any", std::move(name), nullptr, SourceRange{start, end});
}

/* ************************************************************************* */

} // namespace

/* ************************************************************************* */

ast::StmtPtr parseFunction(parser::Parser& parser)
{
    auto start = parser.location();

    // Prefix
    parser.requireIdentifier("func");

    // Name
    parser.checkIdentifier();
    auto name = parser.token().value();
    parser.next();

    parser.requireOther("(");

    // Parse list of arguments
    PtrVector<ast::VariableDecl> args = parser.parseList([&] {
        return parseVariableDecl(parser);
    }, [&] {
        return parser.isOther(")");
    }, [&] {
        parser.requireOther(",");
    });

    auto body = parseCompoundStmt(parser);
    auto end  = parser.location();

    auto decl = makeUnique<ast::FunctionDecl>(
        "Any", name, std::move(body), std::move(args), SourceRange{start, end});

    return makeUnique<ast::DeclStmt>(std::move(decl), SourceRange{start, end});
}

/* ************************************************************************* */

ast::StmtPtr parseReturn(parser::Parser& parser)
{
    auto start = parser.location();

    parser.requireIdentifier("return");

    ast::ExprPtr expr = nullptr;

    // Return expression
    if (!parser.matchOther(";"))
    {
        expr = parser.parseExpr();
        parser.requireOther(";");
    }

    auto end = parser.location();

    return parser.make<ast::ReturnStmt>(
        std::move(expr), SourceRange{start, end});
}

/* ************************************************************************* */

void extendParser(parser::Parser& parser)
{
    // Statements
    parser.addStmtParser("func", &parseFunction);
    parser.addStmtParser("return", &parseReturn);

    // Operators
    parser.addBinaryOperator("+");
    parser.addBinaryOperator("-");
}

/* ************************************************************************* */

} // namespace shard::builtin

/* ************************************************************************* */

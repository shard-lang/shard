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

// C++
#include <algorithm>
#include <fstream>
#include <ios>
#include <iostream>
#include <iterator>
#include <stdexcept>

// Shard
#include "shard/Exception.hpp"
#include "shard/ast/Decls.hpp"
#include "shard/ast/Exprs.hpp"
#include "shard/ast/Stmts.hpp"
#include "shard/parser/Parser.hpp"
#include "shard/tokenizer/Source.hpp"
#include "shard/tokenizer/TokenFilterIterator.hpp"
#include "shard/tokenizer/Tokenizer.hpp"

/* ************************************************************************* */

using namespace shard;

/* ************************************************************************* */

namespace {

/* ************************************************************************* */

int printError(const char* msg) noexcept
{
    std::cerr << "\033[31mERROR\033[0m: " << msg << std::endl;
    return -1;
}

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

/**
 * @brief      Parse function.
 *
 * @param      parser  The parser.
 *
 * @return     Function statement.
 */
ast::StmtPtr parseFunc(parser::Parser& parser)
{
    auto start = parser.location();

    // Prefix
    parser.requireIdentifier("func");

    // Name
    parser.checkIdentifier();
    auto name = parser.token().value();
    parser.next();

    parser.requireOther("(");

    PtrVector<ast::VariableDecl> args;

    while (!parser.isEmpty() && !parser.isOther(")"))
    {
        args.push_back(parseVariableDecl(parser));

         if (parser.isOther(")"))
            break;

        parser.requireOther(",");
    }

    parser.requireOther(")");

    auto body = parseCompoundStmt(parser);
    auto end  = parser.location();

    auto decl = makeUnique<ast::FunctionDecl>(
        "Any", name, std::move(body), std::move(args), SourceRange{start, end});

    return makeUnique<ast::DeclStmt>(std::move(decl), SourceRange{start, end});
}

/* ************************************************************************* */

/**
 * @brief      Parse return statement.
 *
 * @param      parser  The parser.
 *
 * @return     Return statement.
 */
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

    return makeUnique<ast::ReturnStmt>(
        std::move(expr), SourceRange{start, end});
}

/* ************************************************************************* */

} // namespace

/* ************************************************************************* */

/**
 * @brief      Entry function.
 *
 * @param      argc  Number of argument.
 * @param      argv  Arguments.
 *
 * @return     Result code.
 */
int main(int argc, char** argv)
{
    if (argc < 2)
        return printError("no input file");

    try
    {
        std::ifstream file(argv[1]);

        if (!file.is_open())
            return printError("unable to open file");

        auto code = std::string{std::istreambuf_iterator<char>{file},
                                std::istreambuf_iterator<char>{}};

        using TokenFilter =
            tokenizer::TokenFilterIterator<tokenizer::TokenType::EndOfLine>;

        auto source    = tokenizer::Source{code};
        auto tokenizer = tokenizer::Tokenizer{source};
        auto parser    = parser::Parser{tokenizer};

        //
        // Extend parser
        //

        // Statements
        parser.addStmtParser("func", &parseFunc);
        parser.addStmtParser("return", &parseReturn);

        // Operators
        parser.addBinaryOperator("+");
        parser.addBinaryOperator("-");

        // Parse source
        auto ast = parser.parseSource();

        ast.dump(std::cout);
    }
    catch (const std::exception& e)
    {
        return printError(e.what());
    }
}

/* ************************************************************************* */

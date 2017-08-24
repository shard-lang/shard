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
#include "shard/UniquePtr.hpp"
#include "shard/PtrDynamicArray.hpp"
#include "shard/tokenizer/Tokenizer.hpp"
#include "shard/tokenizer/TokenType.hpp"
#include "shard/ast/Unit.hpp"
#include "shard/ast/Stmts.hpp"
#include "shard/ast/Exprs.hpp"
#include "shard/ast/Decls.hpp"
#include "shard/ast/Type.hpp"
#include "shard/parser/ParserException.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace parser {

/* ************************************************************************* */

/**
 * @brief Shard syntax analyzer.
 */
class Parser
{

private:

	tokenizer::Tokenizer m_tokenizer;

/* ************************************************************************* */

public:

    /**
     * @brief Constructs Parser which reads from file.
     * @param path    path to file
     */
    explicit Parser(const Path& path): m_tokenizer(path, false){}

    /**
     * @brief Constructs Parser which reads from String.
     * @param path    source as string
     */
    explicit Parser(const String& source): m_tokenizer(source, false){}

/* ************************************************************************* */

public:

    /**
     * @brief initiates syntax analysis on given source.
     */
	UniquePtr<ast::Unit> parseUnit();

/* ************************************************************************* */

private:

    /**
     * @brief parse declaration.
     */
    PtrDynamicArray<ast::Decl> parseDeclList();

    /**
     * @brief parse class declaration.
     */
    UniquePtr<ast::ClassDecl> parseClassDecl();

    /**
     * @brief parse function declaration.
     */
    UniquePtr<ast::FunctionDecl> parseFunctionDecl();

    /**
     * @brief parse variable declaration.
     */
    UniquePtr<ast::VariableDecl> parseVariableDecl();

/* ************************************************************************* */

private:

    /**
     * @brief parse type for declaration of function/variable
     */
    ast::Type parseDeclType();

    /**
     * @brief parse list of expresions.
     */
    PtrDynamicArray<ast::Expr> parseExprArray();

/* ************************************************************************* */

private:

    /**
     * @brief parse statement.
     */
    UniquePtr<ast::Stmt> parseStmt();

    /**
     * @brief parse If statement.
     */
    UniquePtr<ast::IfStmt> parseIfStmt();
    
    /**
     * @brief parse For statement.
     */
    UniquePtr<ast::ForStmt> parseForStmt();
    
    /**
     * @brief parse While statement.
     */
    UniquePtr<ast::WhileStmt> parseWhileStmt();
    
    /**
     * @brief parse Switch statement.
     */
    UniquePtr<ast::SwitchStmt> parseSwitchStmt();

    /**
     * @brief parse case list.
     */
    PtrDynamicArray<ast::Stmt> parseCaseList();
    
    /**
     * @brief parse statement list for cases.
     */
    PtrDynamicArray<ast::Stmt> parseCaseStmtList();

    /**
     * @brief parse Do-While statement.
     */
    UniquePtr<ast::DoWhileStmt> parseDoWhileStmt();
    
    /**
     * @brief parse Compound statement.
     */
    UniquePtr<ast::CompoundStmt> parseCompoundStmt();

    /**
     * @brief parse TryCatch statement.
     */
    UniquePtr<ast::CompoundStmt> parseTryCatchStmt();

/* ************************************************************************* */

private:

    /**
     * @brief parse expression.
     */
    UniquePtr<ast::Expr> parseExpr();

    /**
     * @brief parse relational expression.
     */
    UniquePtr<ast::Expr> parseRelationalExpr();

    /**
     * @brief parse additive expression.
     */
    UniquePtr<ast::Expr> parseAdditiveExpr();

    /**
     * @brief parse multiplicative expression.
     */
    UniquePtr<ast::Expr> parseMultiplicativeExpr();

    /**
     * @brief parse bitwise expression.
     */
    UniquePtr<ast::Expr> parseBitwiseExpr();

    /**
     * @brief parse prefix unary expression.
     */
    UniquePtr<ast::Expr> parsePrefixUnaryExpr();

    /**
     * @brief parse postfix unary expression.
     */
    UniquePtr<ast::Expr> parsePostfixUnaryExpr();

    /**
     * @brief parse primary expression.
     */
    UniquePtr<ast::Expr> parsePrimaryExpr();

    /**
     * @brief parse parenthesis expression.
     */
    UniquePtr<ast::Expr> parseParenExpr();

/* ************************************************************************* */

private:

    /**
     * @brief returns if current TokenType is tested TokenType.
     */
    inline bool is(tokenizer::TokenType type) const noexcept
    {
        return m_tokenizer.get().getType() == type;
    }

    /**
     * @brief returns if current TokenType is one of tested TokenTypes.
     */
    template<typename T, typename... Types>
    inline bool is(T option, Types... options) const noexcept
    {
        T types[] {option, options...};
        for (const T x : types)
        {
            if (is(x))
            {
                return true;
            }
        }
        return false;
    }

    /**
     * @brief returns if current TokenType is tested TokenType.
     * If so, moves to next token.
     */
    inline bool match(tokenizer::TokenType type) noexcept
    {
        if (is(type))
        {
            m_tokenizer.toss();
            return true;
        }
        return false;
    }

    /**
     * @brief returns if current TokenType is one of tested TokenTypes.
     * If so, moves to next token.
     */
    template<typename T, typename... Types>
    inline bool match(T option, Types... options) noexcept
    {
        T types[] {option, options...};
        for (const T option : types)
        {
            if (is(option))
            {
                m_tokenizer.toss();
                return true;
            }
        }
        return false;
    }

/* ************************************************************************* */

private:

    /**
     * @brief returns tokens value if token is identifier
     */
    inline String getIdentifier() const
    {
        if (!is(tokenizer::TokenType::Identifier))
        {
            throw ExpectedIdentifierException();
        }

        return m_tokenizer.get().getValue<String>();
    }

};

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */
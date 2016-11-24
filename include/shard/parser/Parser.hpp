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
#include "shard/ast/Module.hpp"
#include "shard/ast/Stmt.hpp"
#include "shard/ast/Expr.hpp"
#include "shard/ast/Decl.hpp"
#include "shard/ast/Type.hpp"
#include "shard/parser/ParserException.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace parser {

using namespace tokenizer;
using namespace ast;

/* ************************************************************************* */

/**
 * @brief Shard syntax analyzer.
 */
class Parser
{

private:

	Tokenizer m_tokenizer;

/* ************************************************************************* */

public:

    /**
     * @brief constructs Parser which reads from file.
     */
    explicit Parser(const Path& path): m_tokenizer(path){}

    /**
     * @brief constructs Parser which reads from String.
     */
    explicit Parser(const String& source): m_tokenizer(source){}

/* ************************************************************************* */

public:

    /**
     * @brief initiates syntax analysis on given source.
     */
	UniquePtr<Module> parseModule();

/* ************************************************************************* */

private:

    /**
     * @brief parse declaration.
     */
    PtrDynamicArray<Decl> parseDeclList();

    /**
     * @brief parse class declaration.
     */
    UniquePtr<ClassDecl> parseClassDecl();

    /**
     * @brief parse variable declaration.
     */
    UniquePtr<VariableDecl> parseVariableDecl(const TypeInfo type);

    /**
     * @brief parse fucntion or variable declaration.
     */
    UniquePtr<Decl> parseFunctionOrVariableDecl(const TypeInfo type);

/* ************************************************************************* */

private:

    /**
     * @brief parse variables init expr.
     */
    UniquePtr<Expr> parseVariableInit();

    /**
     * @brief parse function parameter pack.
     */
    PtrDynamicArray<VariableDecl> parseDeclArray();

    /**
     * @brief parse list of extressions.
     */
    PtrDynamicArray<Expr> parseExprArray();

/* ************************************************************************* */

private:

    /**
     * @brief parse statement.
     */
    UniquePtr<Stmt> parseStmt();

    /**
     * @brief parse If statement.
     */
    UniquePtr<IfStmt> parseIfStmt();
    
    /**
     * @brief parse For statement.
     */
    UniquePtr<ForStmt> parseForStmt();
    
    /**
     * @brief parse While statement.
     */
    UniquePtr<WhileStmt> parseWhileStmt();
    
    /**
     * @brief parse Switch statement.
     */
    UniquePtr<SwitchStmt> parseSwitchStmt();

    /**
     * @brief parse case list.
     */
    PtrDynamicArray<Stmt> parseCaseList();
    
    /**
     * @brief parse statement list for cases.
     */
    PtrDynamicArray<Stmt> parseCaseStmtList();

    /**
     * @brief parse Do-While statement.
     */
    UniquePtr<DoWhileStmt> parseDoWhileStmt();
    
    /**
     * @brief parse Compound statement.
     */
    UniquePtr<CompoundStmt> parseCompoundStmt();

    /**
     * @brief parse TryCatch statement.
     */
    UniquePtr<CompoundStmt> parseTryCatchStmt();

/* ************************************************************************* */

private:

    /**
     * @brief parse expression.
     */
    UniquePtr<Expr> parseExpr();

    /**
     * @brief parse relational expression.
     */
    UniquePtr<Expr> parseRelationalExpr();

    /**
     * @brief parse additive expression.
     */
    UniquePtr<Expr> parseAdditiveExpr();

    /**
     * @brief parse multiplicative expression.
     */
    UniquePtr<Expr> parseMultiplicativeExpr();

    /**
     * @brief parse prefix unary expression.
     */
    UniquePtr<Expr> parsePrefixUnaryExpr();

    /**
     * @brief parse postfix unary expression.
     */
    UniquePtr<Expr> parsePostfixUnaryExpr();

    /**
     * @brief parse primary expression.
     */
    UniquePtr<Expr> parsePrimaryExpr();

    /**
     * @brief parse parenthesis expression.
     */
    UniquePtr<Expr> parseParenExpr();

/* ************************************************************************* */

private:

    /*
     * @brief returns if current TokenType is tested TokenType.
     */
    inline bool is(TokenType type) const noexcept
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
    inline bool match(TokenType type) noexcept
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

    inline String getIdentifier() const
    {
        if (!is(TokenType::Identifier))
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
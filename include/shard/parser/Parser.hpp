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
     * @brief parse declaration.
     */
    UniquePtr<Decl> parseDecl();

    /**
     * @brief parse variable declaration of type auto.
     */
    UniquePtr<VariableDecl> parseVariableDeclAuto();

    /**
     * @brief parse variable declaration of type var.
     */
    UniquePtr<VariableDecl> parseVariableDeclVar();

    /**
     * @brief parse variable declaration of type int.
     */
    UniquePtr<VariableDecl> parseVariableDeclInt();

    /**
     * @brief parse variable declaration of type char.
     */
    UniquePtr<VariableDecl> parseVariableDeclChar();

    /**
     * @brief parse variable declaration of type bool.
     */
    UniquePtr<VariableDecl> parseVariableDeclBool();

    /**
     * @brief parse variable declaration of type float.
     */
    UniquePtr<VariableDecl> parseVariableDeclFloat();

    /**
     * @brief parse variable declaration of type string.
     */
    UniquePtr<VariableDecl> parseVariableDeclString();

/* ************************************************************************* */

private:

    /**
     * @brief parse parameter pack.
     */
    PtrDynamicArray<Expr> parseParameters();

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

    /*
     * @brief returns if current TokenType is Keyword with tested KeywordType.
     */
    inline bool is(KeywordType type) const noexcept
    {
        return is(TokenType::Keyword) && m_tokenizer.get().getKeywordType() == type;
    }

    /**
     * @brief returns if current TokenType is one of tested TokenTypes.
     */
    template<typename... Types>
    inline bool is(Types... options) const noexcept
    {
        TokenType types[] {options...};
        for (const TokenType option : types)
        {
            if (is(option))
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

    /*
     * @brief returns if current TokenType is Keyword with tested KeywordType.
     * If so, moves to next token.
     */
    inline bool match(KeywordType type) noexcept
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
    template<typename... Types>
    inline bool match(Types... options) noexcept
    {
        TokenType types[] {options...};
        for (const TokenType option : types)
        {
            if (is(option))
            {
                m_tokenizer.toss();
                return true;
            }
        }
        return false;
    }

};

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */
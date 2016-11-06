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
#include "shard/tokenizer/Tokenizer.hpp"
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

	UniquePtr<Module> parseModule();

private:

    UniquePtr<Stmt> parseStmt();

    UniquePtr<IfStmt> parseIfStmt();
    UniquePtr<ForStmt> parseForStmt();
    UniquePtr<WhileStmt> parseWhileStmt();
    UniquePtr<SwitchStmt> parseSwitchStmt();
    UniquePtr<DoWhileStmt> parseDoWhileStmt();
    UniquePtr<CompoundStmt> parseCompoundStmt();

    UniquePtr<Decl> parseDecl();

    UniquePtr<Module> parseVariableDecl();
    UniquePtr<Module> parseFunctionDecl();
    UniquePtr<Module> parseClassDecl();

    UniquePtr<Expr> parseExpr();

    UniquePtr<Module> parseConditionalExpr();
    UniquePtr<Module> parseAssignmentExpr();

};

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */
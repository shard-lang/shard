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

#include "shard/UniquePtr.hpp"
#include "shard/tokenizer/Tokenizer.hpp"
#include "shard/tokenizer/TokenType.hpp"
#include "shard/ast/Module.hpp"
#include "shard/ast/Stmt.hpp"
#include "shard/ast/Expr.hpp"
#include "shard/ast/Decl.hpp"
#include "shard/parser/ParserException.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace parser {

/* ************************************************************************* */

UniquePtr<Module> Parser::parseModule()
{

}

UniquePtr<Stmt> Parser::parseStmt()
{

}

UniquePtr<IfStmt> Parser::parseIfStmt()
{

}

UniquePtr<ForStmt> Parser::parseForStmt()
{

}

UniquePtr<WhileStmt> Parser::parseWhileStmt()
{

}

UniquePtr<SwitchStmt> Parser::parseSwitchStmt()
{

}

UniquePtr<DoWhileStmt> Parser::parseDoWhileStmt()
{

}

UniquePtr<CompoundStmt> Parser::parseCompoundStmt()
{

}

UniquePtr<Decl> Parser::parseDecl()
{

}

UniquePtr<VariableDecl> Parser::parseVariableDecl()
{

}

UniquePtr<FunctionDecl> Parser::parseFunctionDecl()
{

}

UniquePtr<ClassDecl> Parser::parseClassDecl()
{

}

UniquePtr<Expr> Parser::parseExpr()
{
	auto temp = parseRelationalExpr();

	if (match(TokenType::Question))
	{
		auto trueExpr = parseExpr();

		if (!match(TokenType::Colon))
		{
			throw ExcpectedColonException();
		}

		return makeUnique<TernaryExpr>(std::move(temp), std::move(trueExpr), parseExpr());
	}

	switch (m_tokenizer.get().getType())
	{
		case TokenType::Equal:
		case TokenType::PlusEqual:
		case TokenType::MinusEqual:
		case TokenType::StarEqual:
		case TokenType::SlashEqual:
		case TokenType::PercentEqual:
		{

		}
		default: return std::move(temp);
	}
}

UniquePtr<Expr> Parser::parseRelationalExpr()
{
	auto temp = parseAdditiveExpr();

	switch (m_tokenizer.get().getType())
	{
		case TokenType::EqualEqual:
		case TokenType::ExclaimEqual:
		case TokenType::Less:
		case TokenType::Greater:
		case TokenType::LessEqual:
		case TokenType::GreaterEqual:

		default: return std::move(temp);
	}
}

UniquePtr<Expr> Parser::parseAdditiveExpr()
{
	auto temp = parseMultiplicativeExpr();

	switch (m_tokenizer.get().getType())
	{
		case TokenType::Plus:
		case TokenType::Minus:

		default: return std::move(temp);
	}
}

UniquePtr<Expr> Parser::parseMultiplicativeExpr()
{
	auto temp = parsePrefixUnaryExpr();

	switch (m_tokenizer.get().getType())
	{
		case TokenType::Star:
		case TokenType::Slash:
		case TokenType::Percent:

		default: return std::move(temp);
	}
}

UniquePtr<Expr> Parser::parsePrefixUnaryExpr()
{
	switch (m_tokenizer.get().getType())
	{
		case TokenType::PlusPlus:
		case TokenType::MinusMinus:
		case TokenType::Plus:
		case TokenType::Minus:
		case TokenType::Exclaim:

		default: return parsePostfixUnaryExpr();
	}
}

UniquePtr<Expr> Parser::parsePostfixUnaryExpr()
{
	auto temp = parsePrimaryExpr();

	switch (m_tokenizer.get().getType())
	{
		case TokenType::PlusPlus:	return makeUnique<PostfixUnaryExpr>(PostfixUnaryExpr::Operator::Increment, std::move(temp));
		case TokenType::MinusMinus:	return makeUnique<PostfixUnaryExpr>(PostfixUnaryExpr::Operator::Decrement, std::move(temp));
		case TokenType::Period:
		case TokenType::ParenO:

		default: return std::move(temp);
	}
}

UniquePtr<Expr> Parser::parsePrimaryExpr()
{
	switch (m_tokenizer.get().getType())
	{
		case TokenType::Identifier: return makeUnique<IdentifierExpr>(m_tokenizer.get().getStringValue());
		case TokenType::String:     return makeUnique<StringLiteralExpr>(m_tokenizer.get().getStringValue());
		case TokenType::Float: 	    return makeUnique<FloatLiteralExpr>(m_tokenizer.get().getFloatValue());
		case TokenType::Char: 	    return makeUnique<CharLiteralExpr>(m_tokenizer.get().getCharValue());
		case TokenType::Int: 	    return makeUnique<IntLiteralExpr>(m_tokenizer.get().getIntValue());
		case TokenType::ParenO:	    return parseParenExpr();
		case TokenType::Keyword:
		{	
			switch (m_tokenizer.get().getKeywordType())
			{
				case KeywordType::Null:	    return makeUnique<NullLiteralExpr>();
				case KeywordType::True:	    return makeUnique<BoolLiteralExpr>(true);
				case KeywordType::False:    return makeUnique<BoolLiteralExpr>(false);
				default: break;
			}
		}

		default: throw ExpectedPrimaryExprException();
	}
}

UniquePtr<Expr> Parser::parseParenExpr()
{
	auto temp = parseExpr();

	if (match(TokenType::ParenC))
	{
		return makeUnique<ParenExpr>(std::move(temp));
	}

	throw ExpectedClosingParenException();
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

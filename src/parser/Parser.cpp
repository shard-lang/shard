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

namespace shard {
inline namespace v1 {
namespace parser {

/* ************************************************************************* */

UniquePtr<Unit> Parser::parseUnit()
{
	auto unit = makeUnique<Unit>(parseDeclList());

	if (!m_tokenizer.empty())
	{
		throw ExpectedDeclException();
	}

	return std::move(unit);
}

/* ************************************************************************* */

PtrDynamicArray<Decl> Parser::parseDeclList()
{
	PtrDynamicArray<Decl> list;

	while (!m_tokenizer.empty())
	{
		switch (m_tokenizer.get().getType())
		{
			case TokenType::Class:
				m_tokenizer.toss();  
				list.push_back(parseClassDecl());
				continue;
			case TokenType::Auto:
				m_tokenizer.toss();
				list.push_back(parseFunctionOrVariableDecl(Type(TypeKind::Auto)));
				continue;
			case TokenType::Var:
				m_tokenizer.toss();
				list.push_back(parseFunctionOrVariableDecl(Type(TypeKind::Var)));
				continue;
			case TokenType::Int:
				m_tokenizer.toss();
				list.push_back(parseFunctionOrVariableDecl(Type(TypeKind::Int)));
				continue;
			case TokenType::Bool:
				m_tokenizer.toss();
				list.push_back(parseFunctionOrVariableDecl(Type(TypeKind::Bool)));
				continue;
			case TokenType::Char:
				m_tokenizer.toss();
				list.push_back(parseFunctionOrVariableDecl(Type(TypeKind::Char)));
				continue;
			case TokenType::Float:
				m_tokenizer.toss();
				list.push_back(parseFunctionOrVariableDecl(Type(TypeKind::Float)));
				continue;
			case TokenType::String:
				m_tokenizer.toss();
				list.push_back(parseFunctionOrVariableDecl(Type(TypeKind::String)));
				continue;
			case TokenType::Identifier:
			{
				const Type type(nullptr); // TODO
				m_tokenizer.toss();
				list.push_back(parseFunctionOrVariableDecl(type));
				continue;
			}

			default:
				return std::move(list);
		}
	}

	return std::move(list);
}

/* ************************************************************************* */

UniquePtr<ClassDecl> Parser::parseClassDecl()
{
	String name = getIdentifier();
	m_tokenizer.toss();

	if (!match(TokenType::BraceO))
	{
		throw ExpectedBraceException();
	}

	auto decls = parseDeclList();

	if (!match(TokenType::BraceC))
	{
		throw ExpectedClosingBraceException();
	}

	return makeUnique<ClassDecl>(name, std::move(decls));
}

/* ************************************************************************* */

UniquePtr<VariableDecl> Parser::parseVariableDecl(const Type type)
{
	String name = getIdentifier();
	m_tokenizer.toss();

	return makeUnique<VariableDecl>(type, name, parseVariableInit());
}

/* ************************************************************************* */

UniquePtr<Decl> Parser::parseFunctionOrVariableDecl(const Type type)
{
	String name = getIdentifier();
	m_tokenizer.toss();
	
	if (match(TokenType::ParenO))
	{
		PtrDynamicArray<VariableDecl> params;

		if (!match(TokenType::ParenC))
		{
			auto params = parseDeclArray();

			if (!match(TokenType::ParenC))
			{
				throw ExpectedClosingParenException();
			}
		}

		if (!match(TokenType::BraceO))
		{
			throw ExpectedBraceException();
		}

		return makeUnique<FunctionDecl>(type, name, parseCompoundStmt(), std::move(params));
	}

	auto init = parseVariableInit();

	if (!match(TokenType::Semicolon))
	{
		throw ExpectedSemicolonException();
	}

	return makeUnique<VariableDecl>(type, name, std::move(init));
}

/* ************************************************************************* */

UniquePtr<Expr> Parser::parseVariableInit()
{
	UniquePtr<Expr> init = nullptr;

	if (match(TokenType::Equal))
	{
		init = parseExpr();
	}

	return std::move(init);
}

/* ************************************************************************* */

PtrDynamicArray<VariableDecl> Parser::parseDeclArray()
{
	PtrDynamicArray<VariableDecl> temp;

	do
	{
		switch (m_tokenizer.get().getType())
		{
			case TokenType::Auto:
				m_tokenizer.toss();
				temp.push_back(parseVariableDecl(Type(TypeKind::Auto)));
				break;
			case TokenType::Var:
				m_tokenizer.toss();
				temp.push_back(parseVariableDecl(Type(TypeKind::Var)));
				break;
			case TokenType::Int:
				m_tokenizer.toss();
				temp.push_back(parseVariableDecl(Type(TypeKind::Int)));
				break;
			case TokenType::Bool:
				m_tokenizer.toss();
				temp.push_back(parseVariableDecl(Type(TypeKind::Bool)));
				break;
			case TokenType::Char:
				m_tokenizer.toss();
				temp.push_back(parseVariableDecl(Type(TypeKind::Char)));
				break;
			case TokenType::Float:
				m_tokenizer.toss();
				temp.push_back(parseVariableDecl(Type(TypeKind::Float)));
				break;
			case TokenType::String:
				m_tokenizer.toss();
				temp.push_back(parseVariableDecl(Type(TypeKind::String)));
				break;
			case TokenType::Identifier:
			{
				const Type type(nullptr); // TODO custom Type
				m_tokenizer.toss();
				temp.push_back(parseVariableDecl(type));
				break;
			}
			default:
				throw ExpectedDeclException();
		}
	}
	while (match(TokenType::Comma));

	return std::move(temp);
}

/* ************************************************************************* */

PtrDynamicArray<Expr> Parser::parseExprArray()
{
	PtrDynamicArray<Expr> temp;

	do
	{
		temp.push_back(parseExpr());
	}
	while (match(TokenType::Comma));

	return std::move(temp);
}

/* ************************************************************************* */

UniquePtr<Stmt> Parser::parseStmt()
{
	UniquePtr<Stmt> temp;

	switch (m_tokenizer.get().getType())
	{
		case TokenType::Semicolon:
			m_tokenizer.toss();
			return nullptr;
		case TokenType::BraceO:
			m_tokenizer.toss();
			return parseCompoundStmt();
		case TokenType::Return:
			m_tokenizer.toss();
			if (match(TokenType::Semicolon))
			{
				return makeUnique<ReturnStmt>(nullptr);
			}
			temp = makeUnique<ReturnStmt>(parseExpr());
			break;
		case TokenType::Break:
			m_tokenizer.toss();
			temp = makeUnique<BreakStmt>();
			break;
		case TokenType::Continue: 
			m_tokenizer.toss();
			temp = makeUnique<ContinueStmt>();
			break;
		case TokenType::Throw: 
			m_tokenizer.toss();
			temp = makeUnique<ReturnStmt>(parseExpr());
			break;
		case TokenType::Do:
			m_tokenizer.toss();
			temp = parseDoWhileStmt();
			break;
		case TokenType::If:
			m_tokenizer.toss();
			return parseIfStmt();
		case TokenType::For: 
			m_tokenizer.toss();
			return parseForStmt();
		case TokenType::While: 
			m_tokenizer.toss();
			return parseWhileStmt();
		case TokenType::Switch:
			m_tokenizer.toss();
			return parseSwitchStmt();
		case TokenType::Try:
			m_tokenizer.toss();
			return parseTryCatchStmt();
		case TokenType::Auto:
			m_tokenizer.toss();
			temp = makeUnique<DeclStmt>(parseVariableDecl(Type(TypeKind::Auto)));
			break;
		case TokenType::Var:
			m_tokenizer.toss();
			temp = makeUnique<DeclStmt>(parseVariableDecl(Type(TypeKind::Var)));
			break;
		case TokenType::Int:
			m_tokenizer.toss();
			temp = makeUnique<DeclStmt>(parseVariableDecl(Type(TypeKind::Int)));
			break;
		case TokenType::Bool:
			m_tokenizer.toss();
			temp = makeUnique<DeclStmt>(parseVariableDecl(Type(TypeKind::Bool)));
			break;
		case TokenType::Char:
			m_tokenizer.toss();
			temp = makeUnique<DeclStmt>(parseVariableDecl(Type(TypeKind::Char)));
			break;
		case TokenType::Float:
			m_tokenizer.toss();
			temp = makeUnique<DeclStmt>(parseVariableDecl(Type(TypeKind::Float)));
			break;
		case TokenType::String:
			m_tokenizer.toss();
			temp = makeUnique<DeclStmt>(parseVariableDecl(Type(TypeKind::String)));
			break;
		case TokenType::Identifier:
			// TODO decision making

		default:
			temp = makeUnique<ExprStmt>(parseExpr());
	}

	if (!match(TokenType::Semicolon))
	{
		throw ExpectedSemicolonException();
	}

	return std::move(temp);
}

/* ************************************************************************* */

UniquePtr<IfStmt> Parser::parseIfStmt()
{
	if (!match(TokenType::ParenO))
	{
		throw ExpectedParenException();
	}

	auto cond = parseExpr();

	if (!match(TokenType::ParenC))
	{
		throw ExpectedClosingParenException();
	}

	auto thanStmt = parseStmt();

	UniquePtr<Stmt> elseStmt = nullptr;

	if (match(TokenType::Else))
	{
		elseStmt = parseStmt();
	}

	return makeUnique<IfStmt>(std::move(cond), std::move(thanStmt), std::move(elseStmt));
}

/* ************************************************************************* */

UniquePtr<ForStmt> Parser::parseForStmt()
{
	if (!match(TokenType::ParenO))
	{
		throw ExpectedParenException();
	}

	auto init = parseStmt();

	UniquePtr<Expr> cond = nullptr;

	if (!match(TokenType::Semicolon))
	{
		cond = parseExpr();

		if (!match(TokenType::Semicolon))
		{
			throw ExpectedSemicolonException();
		}
	}

	UniquePtr<Expr> incr = nullptr;

	if (!match(TokenType::ParenC))
	{
		incr = parseExpr();

		if (!match(TokenType::ParenC))
		{
			throw ExpectedClosingParenException();
		}
	}

	return makeUnique<ForStmt>(std::move(init), std::move(cond), std::move(incr), parseStmt());
}

/* ************************************************************************* */

UniquePtr<WhileStmt> Parser::parseWhileStmt()
{
	if (!match(TokenType::ParenO))
	{
		throw ExpectedParenException();
	}

	auto cond = parseExpr();

	if (!match(TokenType::ParenC))
	{
		throw ExpectedClosingParenException();
	}

	return makeUnique<WhileStmt>(std::move(cond), parseStmt());
}

/* ************************************************************************* */

UniquePtr<SwitchStmt> Parser::parseSwitchStmt()
{
	if (!match(TokenType::ParenO))
	{
		throw ExpectedParenException();
	}

	auto cond = parseExpr();

	if (!match(TokenType::ParenC))
	{
		throw ExpectedClosingParenException();
	}

	if (!match(TokenType::BraceO))
	{
		throw ExpectedBraceException();
	}

	auto body = makeUnique<CompoundStmt>(parseCaseList());

	if (!match(TokenType::BraceC))
	{
		throw ExpectedClosingBraceException();
	}

	return makeUnique<SwitchStmt>(std::move(cond), std::move(body));
}

/* ************************************************************************* */

PtrDynamicArray<Stmt> Parser::parseCaseList()
{
	PtrDynamicArray<Stmt> temp;

	while (true)
	{
		if (match(TokenType::Case))
		{
			auto cond = parseExpr();

			if (!match(TokenType::Colon))
			{
				throw ExpectedColonException();
			}

			temp.push_back(makeUnique<CaseStmt>(std::move(cond), parseCaseStmtList()));
			continue;
		}
		else if (match(TokenType::Default))
		{
			if (!match(TokenType::Colon))
			{
				throw ExpectedColonException();
			}

			temp.push_back(makeUnique<DefaultStmt>(parseCaseStmtList()));
			continue;
		}

		break;
	}

	return std::move(temp);
}

/* ************************************************************************* */

PtrDynamicArray<Stmt> Parser::parseCaseStmtList()
{
	PtrDynamicArray<Stmt> temp;

	while (!is(TokenType::BraceC, TokenType::Case, TokenType::Default))
	{
		temp.push_back(parseStmt());
	}

	return std::move(temp);
}

/* ************************************************************************* */

UniquePtr<DoWhileStmt> Parser::parseDoWhileStmt()
{
	if (!match(TokenType::BraceO))
	{
		throw ExpectedWhileException();
	}

	auto body = parseCompoundStmt();

	if (!match(TokenType::While))
	{
		throw ExpectedWhileException();
	}

	if (!match(TokenType::ParenO))
	{
		throw ExpectedParenException();
	}

	auto cond = parseExpr();

	if (!match(TokenType::ParenC))
	{
		throw ExpectedClosingParenException();
	}

	return makeUnique<DoWhileStmt>(std::move(cond), std::move(body));
}

/* ************************************************************************* */

UniquePtr<CompoundStmt> Parser::parseCompoundStmt()
{
	PtrDynamicArray<Stmt> temp;

	while (!match(TokenType::BraceC))
	{
		temp.push_back(parseStmt());
	}

	return makeUnique<CompoundStmt>(std::move(temp));
}

/* ************************************************************************* */

UniquePtr<CompoundStmt> Parser::parseTryCatchStmt()
{
	// TODO
	return nullptr;
}

/* ************************************************************************* */

UniquePtr<Expr> Parser::parseExpr()
{
	auto temp = parseRelationalExpr();

	if (match(TokenType::Question))
	{
		auto trueExpr = parseExpr();

		if (!match(TokenType::Colon))
		{
			throw ExpectedColonException();
		}

		return makeUnique<TernaryExpr>(std::move(temp), std::move(trueExpr), parseExpr());
	}

	switch (m_tokenizer.get().getType())
	{
		case TokenType::Equal:
			m_tokenizer.toss();
			return makeUnique<BinaryExpr>(BinaryExpr::OpKind::Assign, std::move(temp), parseExpr());
		case TokenType::PlusEqual:
			m_tokenizer.toss();
			return makeUnique<BinaryExpr>(BinaryExpr::OpKind::AddAssign, std::move(temp), parseExpr());
		case TokenType::MinusEqual:
			m_tokenizer.toss();
			return makeUnique<BinaryExpr>(BinaryExpr::OpKind::SubAssign, std::move(temp), parseExpr());
		case TokenType::StarEqual:
			m_tokenizer.toss();
			return makeUnique<BinaryExpr>(BinaryExpr::OpKind::MulAssign, std::move(temp), parseExpr());
		case TokenType::SlashEqual:
			m_tokenizer.toss();
			return makeUnique<BinaryExpr>(BinaryExpr::OpKind::DivAssign, std::move(temp), parseExpr());
		case TokenType::PercentEqual:
			m_tokenizer.toss();
			return makeUnique<BinaryExpr>(BinaryExpr::OpKind::RemAssign, std::move(temp), parseExpr());

		default:
			return std::move(temp);
	}
}

/* ************************************************************************* */

UniquePtr<Expr> Parser::parseRelationalExpr()
{
	auto temp = parseAdditiveExpr();

	switch (m_tokenizer.get().getType())
	{
		case TokenType::EqualEqual:
			m_tokenizer.toss();
			return makeUnique<BinaryExpr>(BinaryExpr::OpKind::EQ, std::move(temp), parseExpr());
		case TokenType::ExclaimEqual:
			m_tokenizer.toss();
			return makeUnique<BinaryExpr>(BinaryExpr::OpKind::NE, std::move(temp), parseExpr());
		case TokenType::Less:
			m_tokenizer.toss();
			return makeUnique<BinaryExpr>(BinaryExpr::OpKind::LT, std::move(temp), parseExpr());
		case TokenType::Greater:
			m_tokenizer.toss();
			return makeUnique<BinaryExpr>(BinaryExpr::OpKind::GT, std::move(temp), parseExpr());
		case TokenType::LessEqual:
			m_tokenizer.toss();
			return makeUnique<BinaryExpr>(BinaryExpr::OpKind::LE, std::move(temp), parseExpr());
		case TokenType::GreaterEqual:
			m_tokenizer.toss();
			return makeUnique<BinaryExpr>(BinaryExpr::OpKind::GE, std::move(temp), parseExpr());

		default: return std::move(temp);
	}
}

/* ************************************************************************* */

UniquePtr<Expr> Parser::parseAdditiveExpr()
{
	auto temp = parseMultiplicativeExpr();

	switch (m_tokenizer.get().getType())
	{
		case TokenType::Plus:
			m_tokenizer.toss();
			return makeUnique<BinaryExpr>(BinaryExpr::OpKind::Add, std::move(temp), parseExpr());
		case TokenType::Minus:
			m_tokenizer.toss();
			return makeUnique<BinaryExpr>(BinaryExpr::OpKind::Sub, std::move(temp), parseExpr());

		default:
			return std::move(temp);
	}
}

/* ************************************************************************* */

UniquePtr<Expr> Parser::parseMultiplicativeExpr()
{
	auto temp = parsePrefixUnaryExpr();

	switch (m_tokenizer.get().getType())
	{
		case TokenType::Star:
			m_tokenizer.toss();
			return makeUnique<BinaryExpr>(BinaryExpr::OpKind::Mul, std::move(temp), parseExpr());
		case TokenType::Slash:
			m_tokenizer.toss();
			return makeUnique<BinaryExpr>(BinaryExpr::OpKind::Div, std::move(temp), parseExpr());
		case TokenType::Percent:
			m_tokenizer.toss();
			return makeUnique<BinaryExpr>(BinaryExpr::OpKind::Rem, std::move(temp), parseExpr());

		default:
			return std::move(temp);
	}
}

/* ************************************************************************* */

UniquePtr<Expr> Parser::parsePrefixUnaryExpr()
{
	switch (m_tokenizer.get().getType())
	{
		case TokenType::PlusPlus:
			m_tokenizer.toss();
			return makeUnique<UnaryExpr>(UnaryExpr::OpKind::PreInc, parsePrefixUnaryExpr());
		case TokenType::MinusMinus: 
			m_tokenizer.toss();
			return makeUnique<UnaryExpr>(UnaryExpr::OpKind::PreDec, parsePrefixUnaryExpr());
		case TokenType::Plus:       
			m_tokenizer.toss();
			return makeUnique<UnaryExpr>(UnaryExpr::OpKind::Plus, parsePrefixUnaryExpr());
		case TokenType::Minus:
			m_tokenizer.toss();
			return makeUnique<UnaryExpr>(UnaryExpr::OpKind::Minus, parsePrefixUnaryExpr());
		case TokenType::Exclaim:
			m_tokenizer.toss();
			return makeUnique<UnaryExpr>(UnaryExpr::OpKind::Not, parsePrefixUnaryExpr());

		default:
			return parsePostfixUnaryExpr();
	}
}

/* ************************************************************************* */

UniquePtr<Expr> Parser::parsePostfixUnaryExpr()
{
	auto temp = parsePrimaryExpr();

	while (true)
	{
		switch (m_tokenizer.get().getType())
		{
			case TokenType::PlusPlus:
				temp = makeUnique<UnaryExpr>(UnaryExpr::OpKind::PostInc, std::move(temp));
				break;
			case TokenType::MinusMinus:
				temp = makeUnique<UnaryExpr>(UnaryExpr::OpKind::PostDec, std::move(temp));
				break;
			case TokenType::Period:
				m_tokenizer.toss();
				temp = makeUnique<MemberAccessExpr>(std::move(temp), getIdentifier());
				break;
			case TokenType::ParenO:
				m_tokenizer.toss();
				if (is(TokenType::ParenC))
				{
					temp = makeUnique<FunctionCallExpr>(std::move(temp));
				}
				else
				{
					temp = makeUnique<FunctionCallExpr>(std::move(temp), parseExprArray());
					if (!is(TokenType::ParenC))
					{
						throw ExpectedClosingParenException();
					}
				}
				break;      
			case TokenType::SquareO:
				m_tokenizer.toss();
				temp = makeUnique<SubscriptExpr>(std::move(temp), parseExprArray());
				if (!is(TokenType::SquareC))
				{
					throw ExpectedClosingSquareException();
				}
				break;  

			default:
				return std::move(temp);
		}
		m_tokenizer.toss();
	}
}

/* ************************************************************************* */

UniquePtr<Expr> Parser::parsePrimaryExpr()
{
	auto token = m_tokenizer.extract();

	switch (token.getType())
	{
		case TokenType::Identifier:
			return makeUnique<IdentifierExpr>(token.getValue<String>());
		case TokenType::StringLiteral:
			return makeUnique<StringLiteralExpr>(token.getValue<String>());
		case TokenType::FloatLiteral:
			return makeUnique<FloatLiteralExpr>(token.getValue<Token::FloatType>());
		case TokenType::CharLiteral:
			return makeUnique<CharLiteralExpr>(token.getValue<Token::CharType>());
		case TokenType::IntLiteral:
			return makeUnique<IntLiteralExpr>(token.getValue<Token::IntType>());
		case TokenType::ParenO:
			return parseParenExpr();
		case TokenType::Null:     
			return makeUnique<NullLiteralExpr>();
		case TokenType::True:   
			return makeUnique<BoolLiteralExpr>(true);
		case TokenType::False: 
			return makeUnique<BoolLiteralExpr>(false);

		default:
			throw ExpectedExprException();
	}
}

/* ************************************************************************* */

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

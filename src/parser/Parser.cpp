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

using namespace ast;
using namespace tokenizer;

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
            case TokenType::Function:
                m_tokenizer.toss();
                list.push_back(parseFunctionDecl());
                continue;
            case TokenType::Variable:
                m_tokenizer.toss();
                list.push_back(parseVariableDecl());
                if (!match(TokenType::Semicolon))
                {
                    throw ExpectedSemicolonException();
                }
                continue;
			default:
				throw ExpectedDeclException();
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

	auto declList = parseDeclList();

	if (!match(TokenType::BraceC))
	{
		throw ExpectedClosingBraceException();
	}

	return ClassDecl::make(name, std::move(declList));
}

/* ************************************************************************* */

UniquePtr<FunctionDecl> Parser::parseFunctionDecl()
{
    Type type = parseDeclType();
    m_tokenizer.toss();

    String name = getIdentifier();
    m_tokenizer.toss();

    if (!match(TokenType::ParenO))
    {
        throw ExpectedParenException();
    }

    PtrDynamicArray<VariableDecl> params;

	while (!match(TokenType::ParenC))
	{
		if (!match(TokenType::Variable))
		{
			throw ExpectedDeclException();
		}

		params.push_back(parseVariableDecl());
	}

    if (!match(TokenType::BraceO))
    {
        throw ExpectedBraceException();
    }

    return FunctionDecl::make(type, name, parseCompoundStmt(), std::move(params));
}

/* ************************************************************************* */

UniquePtr<VariableDecl> Parser::parseVariableDecl()
{
    Type type = parseDeclType();
    m_tokenizer.toss();

	String name = getIdentifier();
	m_tokenizer.toss();

    UniquePtr<Expr> init = nullptr;

    if (match(TokenType::Equal))
    {
        init = parseExpr();
    }

    return VariableDecl::make(type, name, std::move(init));
}

/* ************************************************************************* */

Type Parser::parseDeclType()
{
    switch (m_tokenizer.get().getType())
    {
        case TokenType::Auto:
            return Type(TypeKind::Auto);
        case TokenType::Any:
            return Type(TypeKind::Any);
        case TokenType::Int:
            return Type(TypeKind::Int);
        case TokenType::Bool:
            return Type(TypeKind::Bool);
        case TokenType::Char:
            return Type(TypeKind::Char);
        case TokenType::Float:
            return Type(TypeKind::Float);
        case TokenType::String:
            return Type(TypeKind::String);
        case TokenType::Identifier:
            return Type(getIdentifier());
        default:
            throw ExpectedDeclException();
    }
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
				return ReturnStmt::make(nullptr);
			}
			temp = ReturnStmt::make(parseExpr());
			break;
		case TokenType::Break:
			m_tokenizer.toss();
			temp = BreakStmt::make();
			break;
		case TokenType::Continue: 
			m_tokenizer.toss();
			temp = ContinueStmt::make();
			break;
		case TokenType::Throw: 
			m_tokenizer.toss();
			temp = ReturnStmt::make(parseExpr());
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
		case TokenType::Variable:
			m_tokenizer.toss();
			temp = DeclStmt::make(parseVariableDecl());
			break;
		default:
			temp = ExprStmt::make(parseExpr());
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

	return IfStmt::make(std::move(cond), std::move(thanStmt), std::move(elseStmt));
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

	return ForStmt::make(std::move(init), std::move(cond), std::move(incr), parseStmt());
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

	return WhileStmt::make(std::move(cond), parseStmt());
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

	auto body = CompoundStmt::make(parseCaseList());

	if (!match(TokenType::BraceC))
	{
		throw ExpectedClosingBraceException();
	}

	return SwitchStmt::make(std::move(cond), std::move(body));
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

			temp.push_back(CaseStmt::make(std::move(cond), parseCaseStmtList()));
			continue;
		}
		else if (match(TokenType::Default))
		{
			if (!match(TokenType::Colon))
			{
				throw ExpectedColonException();
			}

			temp.push_back(DefaultStmt::make(parseCaseStmtList()));
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

	return DoWhileStmt::make(std::move(cond), std::move(body));
}

/* ************************************************************************* */

UniquePtr<CompoundStmt> Parser::parseCompoundStmt()
{
	PtrDynamicArray<Stmt> temp;

	while (!match(TokenType::BraceC))
	{
		temp.push_back(parseStmt());
	}

	return CompoundStmt::make(std::move(temp));
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

		return TernaryExpr::make(std::move(temp), std::move(trueExpr), parseExpr());
	}

	switch (m_tokenizer.get().getType())
	{
		case TokenType::Equal:
			m_tokenizer.toss();
			return BinaryExpr::make(BinaryExpr::OpKind::Assign, std::move(temp), parseExpr());
		case TokenType::PlusEqual:
			m_tokenizer.toss();
			return BinaryExpr::make(BinaryExpr::OpKind::AddAssign, std::move(temp), parseExpr());
		case TokenType::MinusEqual:
			m_tokenizer.toss();
			return BinaryExpr::make(BinaryExpr::OpKind::SubAssign, std::move(temp), parseExpr());
		case TokenType::StarEqual:
			m_tokenizer.toss();
			return BinaryExpr::make(BinaryExpr::OpKind::MulAssign, std::move(temp), parseExpr());
		case TokenType::SlashEqual:
			m_tokenizer.toss();
			return BinaryExpr::make(BinaryExpr::OpKind::DivAssign, std::move(temp), parseExpr());
		case TokenType::PercentEqual:
			m_tokenizer.toss();
			return BinaryExpr::make(BinaryExpr::OpKind::RemAssign, std::move(temp), parseExpr());
        case TokenType::AmpEqual:
            m_tokenizer.toss();
            return BinaryExpr::make(BinaryExpr::OpKind::BwAndAssign, std::move(temp), parseExpr());
        case TokenType::AmpAmpEqual:
            m_tokenizer.toss();
            return BinaryExpr::make(BinaryExpr::OpKind::AndAssign, std::move(temp), parseExpr());
        case TokenType::PipeEqual:
            m_tokenizer.toss();
            return BinaryExpr::make(BinaryExpr::OpKind::BwOrAssign, std::move(temp), parseExpr());
        case TokenType::PipePipeEqual:
            m_tokenizer.toss();
            return BinaryExpr::make(BinaryExpr::OpKind::OrAssign, std::move(temp), parseExpr());
        case TokenType::CaretEqual:
            m_tokenizer.toss();
            return BinaryExpr::make(BinaryExpr::OpKind::BwXorAssign, std::move(temp), parseExpr());
        case TokenType::LessLessEqual:
            m_tokenizer.toss();
            return BinaryExpr::make(BinaryExpr::OpKind::LShiftAssign, std::move(temp), parseExpr());
        case TokenType::GreaterGreaterEqual:
            m_tokenizer.toss();
            return BinaryExpr::make(BinaryExpr::OpKind::RShiftAssign, std::move(temp), parseExpr());

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
			return BinaryExpr::make(BinaryExpr::OpKind::EQ, std::move(temp), parseExpr());
		case TokenType::ExclaimEqual:
			m_tokenizer.toss();
			return BinaryExpr::make(BinaryExpr::OpKind::NE, std::move(temp), parseExpr());
		case TokenType::Less:
			m_tokenizer.toss();
			return BinaryExpr::make(BinaryExpr::OpKind::LT, std::move(temp), parseExpr());
		case TokenType::Greater:
			m_tokenizer.toss();
			return BinaryExpr::make(BinaryExpr::OpKind::GT, std::move(temp), parseExpr());
		case TokenType::LessEqual:
			m_tokenizer.toss();
			return BinaryExpr::make(BinaryExpr::OpKind::LE, std::move(temp), parseExpr());
		case TokenType::GreaterEqual:
			m_tokenizer.toss();
			return BinaryExpr::make(BinaryExpr::OpKind::GE, std::move(temp), parseExpr());

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
			return BinaryExpr::make(BinaryExpr::OpKind::Add, std::move(temp), parseExpr());
		case TokenType::Minus:
			m_tokenizer.toss();
			return BinaryExpr::make(BinaryExpr::OpKind::Sub, std::move(temp), parseExpr());

		default:
			return std::move(temp);
	}
}

/* ************************************************************************* */

UniquePtr<Expr> Parser::parseMultiplicativeExpr()
{
	auto temp = parseBitwiseExpr();

	switch (m_tokenizer.get().getType())
	{
		case TokenType::Star:
			m_tokenizer.toss();
			return BinaryExpr::make(BinaryExpr::OpKind::Mul, std::move(temp), parseExpr());
		case TokenType::Slash:
			m_tokenizer.toss();
			return BinaryExpr::make(BinaryExpr::OpKind::Div, std::move(temp), parseExpr());
		case TokenType::Percent:
			m_tokenizer.toss();
			return BinaryExpr::make(BinaryExpr::OpKind::Rem, std::move(temp), parseExpr());

		default:
			return std::move(temp);
	}
}

/* ************************************************************************* */

UniquePtr<Expr> Parser::parseBitwiseExpr()
{
    auto temp = parsePrefixUnaryExpr();

    switch (m_tokenizer.get().getType())
    {
        case TokenType::Amp:
            m_tokenizer.toss();
            return BinaryExpr::make(BinaryExpr::OpKind::Mul, std::move(temp), parseExpr());
        case TokenType::Pipe:
            m_tokenizer.toss();
            return BinaryExpr::make(BinaryExpr::OpKind::Div, std::move(temp), parseExpr());
        case TokenType::Caret:
            m_tokenizer.toss();
            return BinaryExpr::make(BinaryExpr::OpKind::Rem, std::move(temp), parseExpr());

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
			return UnaryExpr::make(UnaryExpr::OpKind::PreInc, parsePrefixUnaryExpr());
		case TokenType::MinusMinus: 
			m_tokenizer.toss();
			return UnaryExpr::make(UnaryExpr::OpKind::PreDec, parsePrefixUnaryExpr());
		case TokenType::Plus:       
			m_tokenizer.toss();
			return UnaryExpr::make(UnaryExpr::OpKind::Plus, parsePrefixUnaryExpr());
		case TokenType::Minus:
			m_tokenizer.toss();
			return UnaryExpr::make(UnaryExpr::OpKind::Minus, parsePrefixUnaryExpr());
		case TokenType::Exclaim:
			m_tokenizer.toss();
			return UnaryExpr::make(UnaryExpr::OpKind::Not, parsePrefixUnaryExpr());

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
				temp = UnaryExpr::make(UnaryExpr::OpKind::PostInc, std::move(temp));
				break;
			case TokenType::MinusMinus:
				temp = UnaryExpr::make(UnaryExpr::OpKind::PostDec, std::move(temp));
				break;
			case TokenType::Period:
				m_tokenizer.toss();
				temp = MemberAccessExpr::make(std::move(temp), getIdentifier());
				break;
			case TokenType::ParenO:
				m_tokenizer.toss();
				if (is(TokenType::ParenC))
				{
					temp = FunctionCallExpr::make(std::move(temp));
				}
				else
				{
					temp = FunctionCallExpr::make(std::move(temp), parseExprArray());
					if (!is(TokenType::ParenC))
					{
						throw ExpectedClosingParenException();
					}
				}
				break;      
			case TokenType::SquareO:
				m_tokenizer.toss();
				temp = SubscriptExpr::make(std::move(temp), parseExprArray());
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
			return IdentifierExpr::make(token.getValue<String>());
		case TokenType::StringLiteral:
			return StringLiteralExpr::make(token.getValue<String>());
		case TokenType::FloatLiteral:
			return FloatLiteralExpr::make(token.getValue<Token::FloatType>());
		case TokenType::CharLiteral:
			return CharLiteralExpr::make(token.getValue<Token::CharType>());
		case TokenType::IntLiteral:
			return IntLiteralExpr::make(token.getValue<Token::IntType>());
		case TokenType::ParenO:
			return parseParenExpr();
		case TokenType::Null:
			return NullLiteralExpr::make();
		case TokenType::True:   
			return BoolLiteralExpr::make(true);
		case TokenType::False: 
			return BoolLiteralExpr::make(false);

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
		return ParenExpr::make(std::move(temp));
	}

	throw ExpectedClosingParenException();
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

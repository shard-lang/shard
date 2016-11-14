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
#include "shard/PtrDynamicArray.hpp"
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
    auto module = makeUnique<Module>();

    while (!m_tokenizer.empty())
    {
        module->addDeclaration(parseDecl());
    }

    return std::move(module);
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
    if (is(KeywordType::Class))
    {

    }

    


    throw ExpectedDeclException();
}

PtrDynamicArray<Expr> Parser::parseParameters()
{
	PtrDynamicArray<Expr> temp;

	do
	{
		temp.push_back(parseExpr());
	}
	while (is(TokenType::Comma));

	return std::move(temp);
}

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
            // TODO
        case TokenType::PlusEqual:
            m_tokenizer.toss();
            // TODO
        case TokenType::MinusEqual:
            m_tokenizer.toss();
            // TODO
        case TokenType::StarEqual:
            m_tokenizer.toss();
            // TODO
        case TokenType::SlashEqual:
            m_tokenizer.toss();
            // TODO
        case TokenType::PercentEqual:
            m_tokenizer.toss();
            // TODO

        default:
            return std::move(temp);
    }
}

UniquePtr<Expr> Parser::parseRelationalExpr()
{
    auto temp = parseAdditiveExpr();

    switch (m_tokenizer.get().getType())
    {
        case TokenType::EqualEqual:
            m_tokenizer.toss();
            return makeUnique<BinaryExpr>(BinaryExpr::Operator::Equal, std::move(temp), parseExpr());
        case TokenType::ExclaimEqual:
            m_tokenizer.toss();
            return makeUnique<BinaryExpr>(BinaryExpr::Operator::NotEqual, std::move(temp), parseExpr());
        case TokenType::Less:
            m_tokenizer.toss();
            return makeUnique<BinaryExpr>(BinaryExpr::Operator::Less, std::move(temp), parseExpr());
        case TokenType::Greater:
            m_tokenizer.toss();
            return makeUnique<BinaryExpr>(BinaryExpr::Operator::Greater, std::move(temp), parseExpr());
        case TokenType::LessEqual:
            m_tokenizer.toss();
            return makeUnique<BinaryExpr>(BinaryExpr::Operator::LessEqual, std::move(temp), parseExpr());
        case TokenType::GreaterEqual:
            m_tokenizer.toss();
            return makeUnique<BinaryExpr>(BinaryExpr::Operator::GreaterEqual, std::move(temp), parseExpr());

        default: return std::move(temp);
    }
}

UniquePtr<Expr> Parser::parseAdditiveExpr()
{
    auto temp = parseMultiplicativeExpr();

    switch (m_tokenizer.get().getType())
    {
        case TokenType::Plus:
            m_tokenizer.toss();
            return makeUnique<BinaryExpr>(BinaryExpr::Operator::Add, std::move(temp), parseExpr());
        case TokenType::Minus:
            m_tokenizer.toss();
            return makeUnique<BinaryExpr>(BinaryExpr::Operator::Subtract, std::move(temp), parseExpr());

        default:
            return std::move(temp);
    }
}

UniquePtr<Expr> Parser::parseMultiplicativeExpr()
{
    auto temp = parsePrefixUnaryExpr();

    switch (m_tokenizer.get().getType())
    {
        case TokenType::Star:
            m_tokenizer.toss();
            return makeUnique<BinaryExpr>(BinaryExpr::Operator::Multiply, std::move(temp), parseExpr());
        case TokenType::Slash:
            m_tokenizer.toss();
            return makeUnique<BinaryExpr>(BinaryExpr::Operator::Divide, std::move(temp), parseExpr());
        case TokenType::Percent:
            m_tokenizer.toss();
            return makeUnique<BinaryExpr>(BinaryExpr::Operator::Modulo, std::move(temp), parseExpr());

        default:
            return std::move(temp);
    }
}

UniquePtr<Expr> Parser::parsePrefixUnaryExpr()
{
    switch (m_tokenizer.get().getType())
    {
        case TokenType::PlusPlus:
            m_tokenizer.toss();
            return makeUnique<PrefixUnaryExpr>(PrefixUnaryExpr::Operator::Increment, parsePrefixUnaryExpr());
        case TokenType::MinusMinus: 
            m_tokenizer.toss();
            return makeUnique<PrefixUnaryExpr>(PrefixUnaryExpr::Operator::Decrement, parsePrefixUnaryExpr());
        case TokenType::Plus:       
            m_tokenizer.toss();
            return makeUnique<PrefixUnaryExpr>(PrefixUnaryExpr::Operator::Plus, parsePrefixUnaryExpr());
        case TokenType::Minus:
            m_tokenizer.toss();
            return makeUnique<PrefixUnaryExpr>(PrefixUnaryExpr::Operator::Minus, parsePrefixUnaryExpr());
        case TokenType::Exclaim:
            m_tokenizer.toss();
            return makeUnique<PrefixUnaryExpr>(PrefixUnaryExpr::Operator::Negate, parsePrefixUnaryExpr());

        default:
            return parsePostfixUnaryExpr();
    }
}

UniquePtr<Expr> Parser::parsePostfixUnaryExpr()
{
    auto temp = parsePrimaryExpr();

    while (true)
    {
        switch (m_tokenizer.get().getType())
        {
            case TokenType::PlusPlus:
                temp = makeUnique<PostfixUnaryExpr>(PostfixUnaryExpr::Operator::Increment, std::move(temp));
                break;
            case TokenType::MinusMinus:
                temp = makeUnique<PostfixUnaryExpr>(PostfixUnaryExpr::Operator::Decrement, std::move(temp));
                break;
            case TokenType::Period:
                m_tokenizer.toss();
                if (!is(TokenType::Identifier))
                {
                	throw ExpectedIdentifierException();
                }
                temp = makeUnique<MemberAccessExpr>(std::move(temp), m_tokenizer.get().getStringValue());
                break;
            case TokenType::ParenO:
            	m_tokenizer.toss();
                temp = makeUnique<FunctionCallExpr>(std::move(temp), parseParameters());
                if (!is(TokenType::ParenC))
                {
                	throw ExpectedClosingParenException();
                }
                break;      
            case TokenType::SquareO:
            	m_tokenizer.toss();
                temp = makeUnique<SubscriptExpr>(std::move(temp), parseParameters());
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

UniquePtr<Expr> Parser::parsePrimaryExpr()
{
    auto token = m_tokenizer.extract();

    switch (token.getType())
    {
        case TokenType::Identifier:
            return makeUnique<IdentifierExpr>(token.getStringValue());
        case TokenType::String:
            return makeUnique<StringLiteralExpr>(token.getStringValue());
        case TokenType::Float:
            return makeUnique<FloatLiteralExpr>(token.getFloatValue());
        case TokenType::Char:
            return makeUnique<CharLiteralExpr>(token.getCharValue());
        case TokenType::Int:
            return makeUnique<IntLiteralExpr>(token.getIntValue());
        case TokenType::ParenO:
            return parseParenExpr();
        case TokenType::Keyword:
            switch (token.getKeywordType())
            {
                case KeywordType::Null:     return makeUnique<NullLiteralExpr>();
                case KeywordType::True:     return makeUnique<BoolLiteralExpr>(true);
                case KeywordType::False:    return makeUnique<BoolLiteralExpr>(false);
                default: break;
            }

        default:
            throw ExpectedPrimaryExprException();
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

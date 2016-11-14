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

/* ************************************************************************* */

UniquePtr<Stmt> Parser::parseStmt()
{
    switch (m_tokenizer.get().getType())
    {
        case TokenType::Semicolon:
            m_tokenizer.toss();
            return nullptr;
        case TokenType::BraceO:
            m_tokenizer.toss();
            return parseCompoundStmt();
        case TokenType::Keyword:
            switch (m_tokenizer.get().getKeywordType())
            {
                case KeywordType::Return:
                    m_tokenizer.toss();
                    return makeUnique<ReturnStmt>(parseExpr());
                case KeywordType::Break:
                    m_tokenizer.toss();
                    return makeUnique<BreakStmt>();
                case KeywordType::Continue: 
                    m_tokenizer.toss();
                    return makeUnique<ContinueStmt>();
                case KeywordType::Throw: 
                    m_tokenizer.toss();
                    // TODO
                case KeywordType::If:
                    m_tokenizer.toss();
                    return parseIfStmt();
                case KeywordType::Do: 
                    m_tokenizer.toss();
                    return parseDoWhileStmt();
                case KeywordType::For: 
                    m_tokenizer.toss();
                    return parseForStmt();
                case KeywordType::While: 
                    m_tokenizer.toss();
                    return parseWhileStmt();
                case KeywordType::Switch:
                    m_tokenizer.toss();
                    return parseSwitchStmt();
                case KeywordType::Try: 
                    m_tokenizer.toss();
                    // TODO
            }
        case TokenType::Identifier:
            break;

        default:
            return makeUnique<ExprStmt>(parseExpr());
    }
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

    if (match(KeywordType::Else))
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

    if (!is(TokenType::Semicolon))
    {
        cond = parseExpr();

        if (!match(TokenType::Semicolon))
        {
            throw ExpectedSemicolonException();
        }
    }

    UniquePtr<Expr> incr = nullptr;

    if (!is(TokenType::ParenC))
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

PtrDynamicArray<Stmt> Parser::parseCaseList()
{
    PtrDynamicArray<Stmt> temp;

    while (true)
    {
        if (match(KeywordType::Case))
        {
            if (!match(TokenType::Colon))
            {
                throw ExpectedColonException();
            }

            auto cond = parseExpr();
            temp.push_back(makeUnique<CaseStmt>(std::move(cond), parseStmt()));
            continue;
        }
        else if (match(KeywordType::Default))
        {
            if (!match(TokenType::Colon))
            {
                throw ExpectedColonException();
            }

            temp.push_back(makeUnique<DefaultStmt>(parseStmt()));
            continue;
        }

        break;
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

    if (!match(KeywordType::While))
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

    if (!match(TokenType::Semicolon))
    {
        throw ExpectedSemicolonException();
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

UniquePtr<Decl> Parser::parseDecl()
{
    if (is(KeywordType::Class))
    {

    }

    


    throw ExpectedDeclException();
}

/* ************************************************************************* */

PtrDynamicArray<Expr> Parser::parseParameters()
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

/* ************************************************************************* */

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

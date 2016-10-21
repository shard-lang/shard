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

#include "shard/tokenizer/Tokenizer.hpp"

/* ************************************************************************* */

// C++
#include <algorithm>
#include <cmath>

// Shard
#include "shard/StaticArray.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace tokenizer {

/* ************************************************************************* */

namespace
{
    static const StaticArray<std::pair<String, KeywordType>, 22> g_keywordMap
    {{
    #define KEYWORD(name, str) { str, KeywordType::name },
    #include "shard/tokenizer/Token.def"
    }};

    static char getEscaped(const char value)
    {
        switch (value)
        {
            case '0': return '\0';
            case 'a': return '\a';
            case 'b': return '\b';
            case 'f': return '\f';
            case 'n': return '\n';
            case 'r': return '\r';
            case 't': return '\t';
            case 'v': return '\v';
            case '\\': return '\\';
            case '"': return '"';
            case '\'': return '\'';
            default: throw InvalidEscapeSequenceException();
        }
    }
}

/* ************************************************************************* */

void Tokenizer::tokenizeNumber()
{
    bool floatFlag = false;
    int digitSize = 0;
    
    const auto readNumber = [&]() -> Token::IntType
    {
        digitSize = 0;
        if (!isDigit())
        {
            throw ExpectedNumberException();
        }
        Token::IntType res = 0;
        do
        {
            res = res * 10 + (m_src.extract() - '0');
            ++digitSize;
        }
        while (isDigit());
        return res;
    };

    Token::IntType base = readNumber();
    
    Token::FloatType decimal = 0;
    if (match('.'))
    {
        floatFlag = true;
        decimal = readNumber();
        decimal = decimal / std::pow(10.0, digitSize);
    }

    Token::FloatType exp = 1;
    if (match('e', 'E'))
    {
        floatFlag = true;
        bool negativeExp = false;
        switch (m_src.get())
        {
            case '-': negativeExp = true;
            case '+': m_src.extract();
            default: break;
        }
        exp = std::pow(10.0, readNumber());
        exp = negativeExp ? (1 / exp) : exp;
    }

    Token::FloatType value = (static_cast<Token::FloatType>(base) + decimal) * exp;

    m_current = floatFlag ? Token(value) : Token(base);
}

void Tokenizer::tokenizeString()
{
    String value;

    while (!match(string_literal_border))
    {
        if (empty())
        {
            throw StringWithoutEndException();
        }
        if (match('\\'))
        {
            if (empty())
            {
                throw StringWithoutEndException();
            }
            value += getEscaped(m_src.extract());
        }
        else
        {
            value += m_src.extract();
        }
    }
    
    m_current = Token(TokenType::String, value);
}

void Tokenizer::tokenizeChar()
{
    char value;

    switch (char local = m_src.extract())
    {
        case '\\':
        {
            if (empty())
            {
                throw CharWithoutEndException();
            }
            value = getEscaped(m_src.extract());
            break;
        }
        case char_literal_border:
        {
            throw EmptyCharLiteralException();
        }
        default:
        {
            value = local;
        }
    }
    if (!match(char_literal_border))
    {
        throw CharWithoutEndException();
    }
    
    m_current = Token(value);
}

void Tokenizer::tokenizeIdentifier() noexcept
{
    String value;
    
    do
    {
        value += m_src.extract();
    }
    while (isIdentifier());
    auto search = std::find_if(
        g_keywordMap.begin(), g_keywordMap.end(),
        [&](const std::pair<String, KeywordType>& test){ return test.first == value; }
    );
    if (search != g_keywordMap.end())
    {
        m_current = Token(search->second);
    }
    else
    {
        m_current = Token(value);
    }
}

void Tokenizer::tokenizeOperator()
{
    switch (char local = m_src.extract())
    {
        case '.': m_current = Token(TokenType::Period); break;
        case ',': m_current = Token(TokenType::Comma); break;
        case ':': m_current = Token(TokenType::Colon); break;
        case ';': m_current = Token(TokenType::Semicolon); break;
        case '{': m_current = Token(TokenType::CBracketO); break;
        case '}': m_current = Token(TokenType::CBracketC); break;
        case '[': m_current = Token(TokenType::SBracketO); break;
        case ']': m_current = Token(TokenType::SBracketC); break;
        case '(': m_current = Token(TokenType::BracketO); break;
        case ')': m_current = Token(TokenType::BracketC); break;
        case '+': m_current = Token(TokenType::Plus); break;
        case '-': m_current = Token(TokenType::Minus); break;
        case '*': m_current = Token(TokenType::Star); break;
        case '/': m_current = Token(TokenType::Slash); break;
        case '\\': m_current = Token(TokenType::Backslash); break;
        case '^': m_current = Token(TokenType::Caret); break;
        case '~': m_current = Token(TokenType::Tilde); break;
        case '%': m_current = Token(TokenType::Percent); break;
        case '&': m_current = Token(TokenType::Ampersand); break;
        case '?': m_current = Token(TokenType::QMark); break;
        case '!': m_current = Token(TokenType::EMark); break;
        case '=': m_current = Token(TokenType::Equal); break;
        case '<': m_current = Token(TokenType::Less); break;
        case '>': m_current = Token(TokenType::Greater); break;
        case '#': m_current = Token(TokenType::Hash); break;
        default: throw UnknownOperatorException(local);
    }
}

void Tokenizer::next()
{
    skipWhitespace();

    if (empty())
    {
        m_current = Token(TokenType::End);
    }
    else if (match(string_literal_border))
    {
        tokenizeString();
    }
    else if (match(char_literal_border))
    {
        tokenizeChar();
    }
    else if (isDigit())
    {
        tokenizeNumber();
    }
    else if (isIdentifier())
    {
        tokenizeIdentifier();
    }
    else
    {
        tokenizeOperator();
    }
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */


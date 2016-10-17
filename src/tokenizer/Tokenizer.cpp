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

// Shard
#include "shard/Map.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace tokenizer {

/* ************************************************************************* */

namespace {

/* ************************************************************************* */

static const Map<String, KeywordType> g_keywordMap {{
#define KEYWORD(name, str) { # str, KeywordType::name }
    KEYWORDS
#undef KEYWORD
}};

static const Map<char, char> g_escapeMap {
    {'0', '\0'},
    {'a', '\a'},
    {'b', '\b'},
    {'f', '\f'},
    {'n', '\n'},
    {'r', '\r'},
    {'t', '\t'},
    {'v', '\v'},
    {'\\', '\\'},
    {'"', '"'}
};

/* ************************************************************************* */

}

/* ************************************************************************* */

const Token& TokenizerIterator::operator*() const
{
    return m_tokenizer->get();
}

TokenizerIterator& TokenizerIterator::operator++()
{
    m_tokenizer->next();
    return *this;
}

TokenizerIterator TokenizerIterator::operator++(int)
{
    TokenizerIterator tmp(*this);
    operator++();
    return tmp;
}

/* ************************************************************************* */

void Tokenizer::tokenizeNumber()
{
    String buf;
    bool floatFlag = false;
    
    const auto readNumber = [this, &buf]()
    {
        if (!isDigit())
        {
            throw ExpectedNumberException();
        }
        do
        {
            buf += m_src.extract();
        }
        while (isDigit());
    };

    readNumber();
    if (is('.'))
    {
        floatFlag = true;
        buf += m_src.extract();
        readNumber();
    }
    if (is('e', 'E'))
    {
        floatFlag = true;
        buf += m_src.extract();
        if (is('-', '+'))
        {
            buf += m_src.extract();
        }
        readNumber();
    }
    
    std::istringstream istr(buf);
    istr.imbue(std::locale("C"));
    
    if (floatFlag)
    {
        Token::FloatType value = 0.0f;
        istr >> value;
        m_current = Token(value);
    }
    else
    {
        Token::IntType value = 0;
        istr >> value;
        m_current = Token(value);
    }
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
            auto search = g_escapeMap.find(m_src.extract());
            if (search != g_escapeMap.end())
            {
                value += search->second;
            }
            else
            {
                throw InvalidEscapeSequenceException();
            }
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
            auto search = g_escapeMap.find(m_src.extract());
            if (search != g_escapeMap.end())
            {
                value = search->second;
            }
            else
            {
                throw InvalidEscapeSequenceException();
            }
            break;
        }
        case char_literal_border:
        {
            throw InvalidCharLiteralException();
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
    String buf;
    
    do
    {
        buf += m_src.extract();
    }
    while (isIdentifier());

    auto search = g_keywordMap.find(buf);
    if (search != g_keywordMap.end())
    {
        m_current = Token(search->second);
    }
    else
    {
        m_current = Token(buf);
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


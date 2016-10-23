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
#include <iostream>

// Shard
#include "shard/StaticArray.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace tokenizer {

/* ************************************************************************* */

namespace
{
    static const StaticArray<std::pair<String, KeywordType>, KeywordTypeCount> g_keywordMap
    {{
    #define KEYWORD(name, str) { str, KeywordType::name },
    #include "shard/tokenizer/Token.def"
    }};

    /**
     * @brief returns escaped char value.
     */
    static char getEscaped(const char value)
    {
        switch (value)
        {
            case '"': return '"';
            case '\'': return '\'';
            case '?': return '\?';
            case '\\': return '\\';
            case '0': return '\0';
            case 'a': return '\a';
            case 'b': return '\b';
            case 'f': return '\f';
            case 'n': return '\n';
            case 'r': return '\r';
            case 't': return '\t';
            case 'v': return '\v';
            default: throw InvalidEscapeSequenceException();
        }
    }
}

/* ************************************************************************* */

void Tokenizer::tokenizeNumber()
{
    bool floatFlag = false;
    int digitSize = 0;
    
    const auto readNumber = [&](int base = 10) -> Token::IntType
    {
        digitSize = 0;
        Token::IntType res = 0;
        if (base == 16)
        {
            if (!isHexDigit())
            {
                throw ExpectedNumberException();
            }
            do
            {
                auto value = m_src.extract();
                switch (value)
                {
                    case 'A':
                    case 'B':
                    case 'C':
                    case 'D':
                    case 'E':
                    case 'F': value -= 'A' - 10; break;
                    case 'a':
                    case 'b':
                    case 'c':
                    case 'd':
                    case 'e':
                    case 'f': value -= 'a' - 10; break;
                    default: value -= '0'; break;
                }
                res = res * base + value;
                ++digitSize;
            }
            while (isHexDigit());
        }
        else
        {
            if (!isDigit())
            {
                throw ExpectedNumberException();
            }
            do
            {
                res = res * base + (m_src.extract() - '0');
                ++digitSize;
            }
            while (isDigit());
        }
        return res;
    };

    if (is('0'))
    {
        switch(m_src.getNext())
        {
            case 'b':
            case 'B': m_src.toss(); m_current = Token(readNumber(2)); return;
            case 'x':
            case 'X': m_src.toss(); m_current = Token(readNumber(16)); return;
            case 'o':
            case 'O': m_src.toss(); m_current = Token(readNumber(8)); return;
            default: m_src.unget(); break;
        }
    }

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
    Token::CharType value = m_src.extract();
    if (value >= 0x80)
    {
        char additionalBytes;
        if (value >= 0xF0)
        {
            additionalBytes = 3;
        }
        else if (value >= 0xE0)
        {
            additionalBytes = 2;
        }
        else if (value >= 0xC0)
        {
            additionalBytes = 1;
        }
        for (char i = 0; i < additionalBytes; ++i)
        {
            value = (value << 8)|(m_src.extract());
        }
    }
    else
    {
        switch (value)
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
            default: break;
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
        case '{': m_current = Token(TokenType::BraceO); break;
        case '}': m_current = Token(TokenType::BraceC); break;
        case '[': m_current = Token(TokenType::SquareO); break;
        case ']': m_current = Token(TokenType::SquareC); break;
        case '(': m_current = Token(TokenType::ParenO); break;
        case ')': m_current = Token(TokenType::ParenC); break;
        case '?': m_current = Token(TokenType::QMark); break;
        case '~': m_current = Token(TokenType::Tilde); break;
        case '#': m_current = Token(TokenType::Hash); break;
        case '\\': m_current = Token(TokenType::Backslash); break;
        case '=':
        {
            switch (m_src.get())
            {
                case '=': m_current = Token(TokenType::EqualEqual); m_src.extract(); break;
                default: m_current = Token(TokenType::Equal); break;
            } break;
        }
        case '!':
        {
            switch (m_src.get())
            {
                case '=': m_current = Token(TokenType::EMarkEqual); m_src.extract(); break;
                default: m_current = Token(TokenType::EMark); break;
            } break;
        }
        case '+':
        {
            switch (m_src.get())
            {
                case '+': m_current = Token(TokenType::PlusPlus); m_src.extract(); break;
                case '=': m_current = Token(TokenType::PlusEqual); m_src.extract(); break;
                default: m_current = Token(TokenType::Plus); break;
            } break;
        }
        case '-':
        {
            switch (m_src.get())
            {
                case '-': m_current = Token(TokenType::MinusMinus); m_src.extract(); break;
                case '=': m_current = Token(TokenType::MinusEqual); m_src.extract(); break;
                default: m_current = Token(TokenType::Minus); break;
            } break;
        }
        case '*':
        {
            switch (m_src.get())
            {
                case '=': m_current = Token(TokenType::StarEqual); m_src.extract(); break;
                default: m_current = Token(TokenType::Star); break;
            } break;
        }
        case '/':
        {
            switch (m_src.get())
            {
                case '=': m_current = Token(TokenType::SlashEqual); m_src.extract(); break;
                default: m_current = Token(TokenType::Slash); break;
            } break;
        }
        case '^':
        {
            switch (m_src.get())
            {
                case '=': m_current = Token(TokenType::CaretEqual); m_src.extract(); break;
                default: m_current = Token(TokenType::Caret); break;
            } break;
        }
        case '%': 
        {
            switch (m_src.get())
            {
                case '=': m_current = Token(TokenType::PercentEqual); m_src.extract(); break;
                default: m_current = Token(TokenType::Equal); break;
            } break;
        }
        case '&':
        {
            switch (m_src.get())
            {
                case '&':
                {
                    switch (m_src.getNext())
                    {
                        case '=': m_current = Token(TokenType::AmpAmpEqual); m_src.extract(); break;
                        default: m_current = Token(TokenType::AmpAmp); break;
                    } break;
                }
                case '=': m_current = Token(TokenType::AmpEqual); m_src.extract(); break;
                default: m_current = Token(TokenType::Amp); break;
            } break;
        }
        case '|':
        {
            switch (m_src.get())
            {
                case '|':
                {
                    switch (m_src.getNext())
                    {
                        case '=': m_current = Token(TokenType::PipePipeEqual); m_src.extract(); break;
                        default: m_current = Token(TokenType::PipePipe); break;
                    } break;
                }
                case '=': m_current = Token(TokenType::PipeEqual); m_src.extract(); break;
                default: m_current = Token(TokenType::Pipe); break;
            } break;
        }
        case '<':
        {
            switch (m_src.get())
            {
                case '<':
                {
                    switch (m_src.getNext())
                    {
                        case '=': m_current = Token(TokenType::LessLessEqual); m_src.extract(); break;
                        default: m_current = Token(TokenType::LessLess); break;
                    } break;
                }
                case '=': m_current = Token(TokenType::LessEqual); m_src.extract(); break;
                default: m_current = Token(TokenType::Less); break;
            } break;
        }
        case '>':
        {
            switch (m_src.get())
            {
                case '>':
                {
                    switch (m_src.getNext())
                    {
                        case '=': m_current = Token(TokenType::GreaterGreaterEqual); m_src.extract(); break;
                        default: m_current = Token(TokenType::GreaterGreater); break;
                    } break;
                }
                case '=': m_current = Token(TokenType::GreaterEqual); m_src.extract(); break;
                default: m_current = Token(TokenType::Greater); break;
            } break;
        }
        default: throw UnknownOperatorException(local);
    }
}

void Tokenizer::next()
{
    skipWhitespace();
    skipComments();
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


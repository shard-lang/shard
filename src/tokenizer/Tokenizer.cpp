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

    /**
     * @brief returns numeric value of character in hexadecimal base.
     */
    static Token::IntType getNumericValue(char value)
    {
        if (value >= 'A' && value <= 'F')
        {
            return value - 'A' + 10;
        }
        if (value >= 'a' && value <= 'f')
        {
            return value - 'a' + 10;
        }
        return value - '0';
    }
}

/* ************************************************************************* */

void Tokenizer::tokenizeNumber()
{
    bool floatFlag = false;
    int digitSize = 0;
    int base = 10;
    
    const auto readNumber = [&]() -> Token::IntType
    {
        digitSize = 0;
        if (!isDigit(base))
        {
            throw ExpectedNumberException();
        }

        Token::IntType res = 0;
        do
        {
            res = res * base + getNumericValue(m_src.extract());
            ++digitSize;
        }
        while (isDigit(base));
        return res;
    };

    Token::IntType integer = readNumber();

    if (integer == 0)
    {
        switch(m_src.get())
        {
            case 'x':
            case 'X': base = 16; m_src.toss(); m_current = Token(readNumber()); return;
            case 'o':
            case 'O': base = 8; m_src.toss(); m_current = Token(readNumber()); return;
            case 'b':
            case 'B': base = 2; m_src.toss(); m_current = Token(readNumber()); return;
            default: break;
        }
    }
    
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
            case '+': m_src.toss();
            default: break;
        }
        exp = std::pow(10.0, readNumber());
        exp = negativeExp ? (1 / exp) : exp;
    }

    Token::FloatType value = (static_cast<Token::FloatType>(integer) + decimal) * exp;

    m_current = floatFlag ? Token(value) : Token(integer);
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
            value &= 0x07;
            additionalBytes = 3;
        }
        else if (value >= 0xE0)
        {
            value &= 0x0F;
            additionalBytes = 2;
        }
        else if (value >= 0xC0)
        {
            value &= 0x1F;
            additionalBytes = 1;
        }
        for (char i = 0; i < additionalBytes; ++i)
        {
            value = (value << 6)|(m_src.extract() & 0x3F);
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
            case '\n':
            case '\r': throw NewlineInCharLiteralException();
            case char_literal_border: throw EmptyCharLiteralException();
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
        case '.': m_current = Token(TokenType::Period); return;
        case ',': m_current = Token(TokenType::Comma); return;
        case ':': m_current = Token(TokenType::Colon); return;
        case ';': m_current = Token(TokenType::Semicolon); return;
        case '{': m_current = Token(TokenType::BraceO); return;
        case '}': m_current = Token(TokenType::BraceC); return;
        case '[': m_current = Token(TokenType::SquareO); return;
        case ']': m_current = Token(TokenType::SquareC); return;
        case '(': m_current = Token(TokenType::ParenO); return;
        case ')': m_current = Token(TokenType::ParenC); return;
        case '?': m_current = Token(TokenType::Question); return;
        case '~': m_current = Token(TokenType::Tilde); return;
        case '#': m_current = Token(TokenType::Hash); return;
        case '\\': m_current = Token(TokenType::Backslash); return;
        case '=':
        {
            switch (m_src.get())
            {
                case '=': m_current = Token(TokenType::EqualEqual); m_src.toss(); return;
                default: m_current = Token(TokenType::Equal); return;
            }
        }
        case '!':
        {
            switch (m_src.get())
            {
                case '=': m_current = Token(TokenType::ExclaimEqual); m_src.toss(); return;
                default: m_current = Token(TokenType::Exclaim); return;
            }
        }
        case '+':
        {
            switch (m_src.get())
            {
                case '+': m_current = Token(TokenType::PlusPlus); m_src.toss(); return;
                case '=': m_current = Token(TokenType::PlusEqual); m_src.toss(); return;
                default: m_current = Token(TokenType::Plus); return;
            }
        }
        case '-':
        {
            switch (m_src.get())
            {
                case '-': m_current = Token(TokenType::MinusMinus); m_src.toss(); return;
                case '=': m_current = Token(TokenType::MinusEqual); m_src.toss(); return;
                default: m_current = Token(TokenType::Minus); return;
            }
        }
        case '*':
        {
            switch (m_src.get())
            {
                case '=': m_current = Token(TokenType::StarEqual); m_src.toss(); return;
                default: m_current = Token(TokenType::Star); return;
            }
        }
        case '/':
        {
            switch (m_src.get())
            {
                case '=': m_current = Token(TokenType::SlashEqual); m_src.toss(); return;
                case '/':
                {
                    m_src.toss();
                    String buf;
                    while (!match('\n', '\r'))
                    {
                        buf += m_src.extract();
                    }
                    m_current = Token(TokenType::CommentInline, buf);
                    return;
                }
                case '*':
                {
                    m_src.toss();
                    String buf;
                    while (true)
                    {
                        if (is('*'))
                        {
                            if (m_src.getNext() == '/')
                            {
                                m_src.toss();
                                break;
                            }
                            buf += '*';
                        }
                        buf += m_src.extract();
                    }
                    m_current = Token(TokenType::CommentBlock, buf);
                    return;
                }
                default: m_current = Token(TokenType::Slash); return;
            }
        }
        case '^':
        {
            switch (m_src.get())
            {
                case '=': m_current = Token(TokenType::CaretEqual); m_src.toss(); return;
                default: m_current = Token(TokenType::Caret); return;
            }
        }
        case '%': 
        {
            switch (m_src.get())
            {
                case '=': m_current = Token(TokenType::PercentEqual); m_src.toss(); return;
                default: m_current = Token(TokenType::Equal); return;
            }
        }
        case '&':
        {
            switch (m_src.get())
            {
                case '&':
                {
                    switch (m_src.getNext())
                    {
                        case '=': m_current = Token(TokenType::AmpAmpEqual); m_src.toss(); return;
                        default: m_current = Token(TokenType::AmpAmp); return;
                    }
                }
                case '=': m_current = Token(TokenType::AmpEqual); m_src.toss(); return;
                default: m_current = Token(TokenType::Amp); return;
            }
        }
        case '|':
        {
            switch (m_src.get())
            {
                case '|':
                {
                    switch (m_src.getNext())
                    {
                        case '=': m_current = Token(TokenType::PipePipeEqual); m_src.toss(); return;
                        default: m_current = Token(TokenType::PipePipe); return;
                    }
                }
                case '=': m_current = Token(TokenType::PipeEqual); m_src.toss(); return;
                default: m_current = Token(TokenType::Pipe); return;
            }
        }
        case '<':
        {
            switch (m_src.get())
            {
                case '<':
                {
                    switch (m_src.getNext())
                    {
                        case '=': m_current = Token(TokenType::LessLessEqual); m_src.toss(); return;
                        default: m_current = Token(TokenType::LessLess); return;
                    }
                }
                case '=': m_current = Token(TokenType::LessEqual); m_src.toss(); return;
                default: m_current = Token(TokenType::Less); return;
            }
        }
        case '>':
        {
            switch (m_src.get())
            {
                case '>':
                {
                    switch (m_src.getNext())
                    {
                        case '=': m_current = Token(TokenType::GreaterGreaterEqual); m_src.toss(); return;
                        default: m_current = Token(TokenType::GreaterGreater); return;
                    }
                }
                case '=': m_current = Token(TokenType::GreaterEqual); m_src.toss(); return;
                default: m_current = Token(TokenType::Greater); return;
            }
        }
        default: throw UnknownOperatorException(local);
    }
}

void Tokenizer::tokenize()
{
    skipWhitespace();

    auto start = m_loc;

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

    auto end = m_loc;

    m_current.setLocation(start, end);
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

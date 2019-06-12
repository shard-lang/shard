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

// Shard
#include "shard/Assert.hpp"
#include "shard/tokenizer/exceptions.hpp"

/* ************************************************************************* */

namespace shard::tokenizer {

/* ************************************************************************* */

namespace {

/* ************************************************************************* */

/**
 * @brief      Return escaped character.
 *
 * @param      chr       The character.
 * @param      location  The location.
 *
 * @return     The character.
 */
char escape(char chr, const SourceLocation& location)
{
    switch (chr)
    {
    case '\'': return '\'';
    case '"': return '"';
    case '\\': return '\\';
    case '0': return '\0';
    case 'n': return '\n';
    case 'r': return '\r';
    case 't': return '\t';
    }

    throw TokenizerError("Unsupported escape sequence", location);
}

/* ************************************************************************* */

}

/* ************************************************************************* */

Optional<Token> Tokenizer::tokenize()
{
    if (isEmpty())
        return std::nullopt;

    // Identifier start
    if (isLetter() || is('_'))
    {
        return tokenizeIdentifier();
    }
    else if (isDigit())
    {
        return tokenizeNumber();
    }
    else if (is('\"'))
    {
        return tokenizeString();
    }
    else if (is('\''))
    {
        return tokenizeChar();
    }
    else if (isEndOfLine())
    {
        return tokenizeEndOfLine();
    }
    else if (isWhitespace())
    {
        return tokenizeWhiteSpace();
    }
    else
    {
        return tokenizeOther();
    }
}

/* ************************************************************************* */

Token Tokenizer::tokenizeIdentifier()
{
    String value;
    SourceLocation location = m_current.location();

    SHARD_ASSERT(isIdentifier());

    while (isIdentifier())
    {
        value.push_back(*m_current);
        ++m_current;
    }

    return Token(TokenType::Identifier, std::move(value), std::move(location));
}

/* ************************************************************************* */

Token Tokenizer::tokenizeNumber()
{
    String value;
    SourceLocation location = m_current.location();

    SHARD_ASSERT(isDigit());
    value.push_back(*m_current);
    ++m_current;

    while (isIdentifier())
    {
        value.push_back(*m_current);
        ++m_current;
    }

    return Token(
        TokenType::NumberLiteral, std::move(value), std::move(location));
}

/* ************************************************************************* */

Token Tokenizer::tokenizeString()
{
    String value;
    SourceLocation location = m_current.location();

    SHARD_ASSERT(is('"'));
    ++m_current;

    while (!is('"'))
    {
        if (isEmpty())
            throw TokenizerError("missing terminating \" character", location);

        if (*m_current == '\\')
        {
            ++m_current;
            value.push_back(escape(*m_current, location));
        }
        else
        {
            value.push_back(*m_current);
        }

        ++m_current;
    }

    SHARD_ASSERT(is('"'));
    ++m_current;

    return Token(
        TokenType::StringLiteral, std::move(value), std::move(location));
}

/* ************************************************************************* */

Token Tokenizer::tokenizeChar()
{
    String value;
    SourceLocation location = m_current.location();

    SHARD_ASSERT(is('\''));
    ++m_current;

    if (isEmpty())
        throw TokenizerError("missing terminating ' character", location);

    if (*m_current == '\\')
    {
        ++m_current;
        value.push_back(escape(*m_current, location));
    }
    else if (is('\''))
    {
        throw TokenizerError("empty character constant", location);
    }
    else
    {
        value.push_back(*m_current);
    }

    ++m_current;

    if (!is('\''))
        throw TokenizerError("missing terminating ' character", location);

    ++m_current;

    return Token(TokenType::CharLiteral, std::move(value), std::move(location));
}

/* ************************************************************************* */

Token Tokenizer::tokenizeWhiteSpace()
{
    String value;
    SourceLocation location = m_current.location();

    SHARD_ASSERT(isWhitespace());

    while (isWhitespace())
    {
        value.push_back(*m_current);
        ++m_current;
    }

    return Token(TokenType::WhiteSpace, std::move(value), std::move(location));
}

/* ************************************************************************* */

Token Tokenizer::tokenizeEndOfLine()
{
    String value;
    SourceLocation location = m_current.location();

    SHARD_ASSERT(isEndOfLine());

    value.push_back(*m_current);
    ++m_current;

    return Token(TokenType::EndOfLine, std::move(value), std::move(location));
}

/* ************************************************************************* */

Token Tokenizer::tokenizeOther()
{
    String value;
    SourceLocation location = m_current.location();

    // Comment
    if (match('/'))
    {
        if (match('/'))
        {
            while (!is('\n') && !isEmpty())
            {
                value.push_back(*m_current);
                ++m_current;
            }

            // Remove new line
            match('\n');

            return Token(TokenType::Comment, std::move(value), std::move(location));
        }
        else if (match('*'))
        {
            while (!isEmpty())
            {
                if (match('*'))
                {
                    if (match('/'))
                        return Token(TokenType::Comment, std::move(value), std::move(location));
                }
                else
                {
                    value.push_back(*m_current);
                    ++m_current;
                }
            }

            if (isEmpty())
                throw TokenizerError("unterminated /* comment", location);
        }
    }
    else
    {
        value.push_back(*m_current);
        ++m_current;
    }

    return Token(TokenType::Other, std::move(value), std::move(location));
}

/* ************************************************************************* */

} // namespace shard::tokenizer

/* ************************************************************************* */

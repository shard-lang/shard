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

#pragma once

/* ************************************************************************* */

// Shard
#include "shard/Path.hpp"
#include "shard/Assert.hpp"
#include "shard/String.hpp"
#include "shard/ViewPtr.hpp"
#include "shard/SourceLocation.hpp"
#include "shard/tokenizer/Source.hpp"
#include "shard/tokenizer/KeywordType.hpp"
#include "shard/tokenizer/TokenType.hpp"
#include "shard/tokenizer/Token.hpp"
#include "shard/tokenizer/TokenizerException.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace tokenizer {

/* ************************************************************************* */

class Tokenizer; //FWD declaration

/* ************************************************************************* */

/**
 * @brief Input iterator from Shard lexical analyzer.
 */
class TokenizerIterator
{

private:

    ViewPtr<Tokenizer> m_tokenizer;

public:

    /**
     * @brief constructs empty TokenizerIterator.
     */
    TokenizerIterator() = default;

    /**
     * @brief constructs TokenizerIterator for given Tokenizer.
     */
    explicit TokenizerIterator(ViewPtr<Tokenizer> tokenizer):
        m_tokenizer(tokenizer) {}

    inline const Token& operator*() const;
    inline TokenizerIterator& operator++();
    inline TokenizerIterator operator++(int);

    /**
     * @brief returns pointer to related tokenizer.
     */
    inline ViewPtr<Tokenizer> getTokenizer() const noexcept
    {
        return m_tokenizer;
    }
};

/* ************************************************************************* */

/**
 * @brief checks whether lhs or rhs is at final token.
 *
 * This operator serves for range-for purposes. 
 */
inline bool operator==(const TokenizerIterator& lhs, const TokenizerIterator& rhs)
{
    return (lhs.getTokenizer() == nullptr || (*lhs).getType() == TokenType::End)
        && (rhs.getTokenizer() == nullptr || (*rhs).getType() == TokenType::End);
}

inline bool operator!=(const TokenizerIterator& lhs, const TokenizerIterator& rhs)
{
    return !(lhs == rhs);
}

/* ************************************************************************* */

/**
 * @brief Shard lexical analyzer.
 */
class Tokenizer
{

private:

    Source m_src;
    Token m_current;

    static constexpr char string_literal_border = '"';
    static constexpr char char_literal_border = '\'';

/* ************************************************************************* */

public:

    /**
     * @brief constructs Tokenizer which reads from file.
     */
    explicit Tokenizer(const Path& path): m_src(path)
    {
        tokenize();
    }

    /**
     * @brief constructs Tokenizer which reads from String.
     */
    explicit Tokenizer(const String& source): m_src(source)
    {
        tokenize();
    }
            
/* ************************************************************************* */

public:

    /**
     * @brief load next token.
     */
    void tokenize();

/* ************************************************************************* */

public:

    /**
     * @brief get current token.
     */
    inline const Token& get() const noexcept
    {
        return m_current;
    }

    /**
     * @brief get current token and move to next.
     */
    inline Token extract()
    {
        auto tmp = m_current;
        tokenize();
        return tmp;
    }

    /**
     * @brief move to next token and return it.
     */
    inline const Token& getNext()
    {
        tokenize();
        return m_current;
    }

    /**
     * @brief discards current token and moves to next.
     */
    inline void toss()
    {
        tokenize();
    }

/* ************************************************************************* */

public:

    /**
     * @brief checks if current token is final EOF type.
     */
    inline bool empty()
    {
        return m_current.getType() == TokenType::End;
    }

/* ************************************************************************* */

public:

    /**
     * @brief returns tokenizer iterator pointing to currect token.
     */
    inline TokenizerIterator begin() noexcept
    {
        return TokenizerIterator(this);
    }

    /**
     * @brief returns empty tokenizer iterator.
     */
    inline TokenizerIterator end() noexcept
    {
        return TokenizerIterator(nullptr);
    }

/* ************************************************************************* */

private:

    /**
     * @brief returns if current character is tested character.
     */
    inline bool is(char value) noexcept
    {
        return !m_src.empty() && m_src.get() == value;
    }

    /**
     * @brief returns if current character is one of tested characters.
     */
    template<typename... Chars>
    inline bool is(Chars... options) noexcept
    {
        char chars[] {options...};
        for (const char option : chars)
        {
            if (is(option))
            {
                return true;
            }
        }
        return false;
    }

    /**
     * @brief returns if current character is between two chars in the ASCII table.
     */
    inline bool isBetween(char value1, char value2) noexcept
    {
        return !m_src.empty() && (m_src.get() >= value1) && (m_src.get() <= value2);
    }

    /**
    * @brief returns if current character is whitespace.
    */
    inline bool isWhitespace() noexcept
    {
        return isBetween('\1', ' ');
    }

    /**
     * @brief returns if current character is a letter.
     */
    inline bool isLetter() noexcept
    {
        return isBetween('a', 'z') || isBetween('A', 'Z');
    }

    /**
     * @brief returns if current character is a letter, number or '_'.
     */
    inline bool isIdentifier() noexcept
    {
        return isLetter() || isDigit() || is('_');
    }

    /**
     * @brief returns if current character is a number in given numeric system.
     */
    inline bool isDigit(int base = 10) noexcept
    {
        SHARD_ASSERT(base == 10 || base == 16 || base == 8 || base == 2);
        switch (base)
        {
            case 10: return isBetween('0', '9');
            case 16: return isBetween('0', '9') || isBetween('a', 'f') || isBetween('A', 'F');
            case 8: return isBetween('0', '7');
            case 2: return isBetween('0', '1');
            default: return false;
        }
    }

    /**
     * @brief returns if current character is tested character.
     * If so, moves to next character.
     */
    inline bool match(char value) noexcept
    {
        if (is(value))
        {
            m_src.toss();
            return true;
        }
        return false;
    }

    /**
     * @brief returns if current character is one of tested characters.
     * If so, moves to next character.
     */
    template<typename... Chars>
    inline bool match(Chars... options) noexcept
    {
        const char chars[] {options...};
        for (const char option : chars)
        {
            if (is(option))
            {
                m_src.toss();
                return true;
            }
        }
        return false;
    }

/* ************************************************************************* */

private:

    /**
     * @brief Iterates to next non-whitespace char.
     */
    inline void skipWhitespace() noexcept
    {
        while (isWhitespace())
        {
            m_src.toss();
        }
    }

    /**
     * @brief returns escaped char value.
     */
    Token::CharType getEscaped(const char value);

/* ************************************************************************* */

private:

    /**
     * @brief tokenizes int or float literal.
     */
    void tokenizeNumber();

    /**
     * @brief tokenizes identifier or keyword.
     */
    void tokenizeIdentifier() noexcept;

    /**
     * @brief tokenizes string literal.
     */
    void tokenizeString();

    /**
     * @brief tokenizes char literal.
     */
    void tokenizeChar();

    /**
     * @brief tokenizes operators.
     */
    void tokenizeOperator();

};

/* ************************************************************************* */

inline const Token& TokenizerIterator::operator*() const
{
    return m_tokenizer->get();
}

inline TokenizerIterator& TokenizerIterator::operator++()
{
    m_tokenizer->tokenize();
    return *this;
}

inline TokenizerIterator TokenizerIterator::operator++(int)
{
    TokenizerIterator tmp(*this);
    operator++();
    return tmp;
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */


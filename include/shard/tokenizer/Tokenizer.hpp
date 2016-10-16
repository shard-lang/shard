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
#include "shard/String.hpp"
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

class Tokenizer
{

protected:

    Source m_src;
    Token m_current;

    static constexpr char string_literal_border = '"';
    static constexpr char char_literal_border = '\'';

// ===================================================================================== //

public:

    Tokenizer (const Path& path):
            m_src(path){}

    Tokenizer (const String& source):
            m_src(source){}

// ===================================================================================== //

protected:

    /**
     * @brief returns if current character is between two chars in the ASCII table.
     */
    inline bool isBetween(char value1, char value2) noexcept
    {
        return !empty() && (m_src.getCurrent() >= value1) && (m_src.getCurrent() <= value2);
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
        return isBetween('a', 'z') || isBetween('A', 'Z') || isDigit() || is('_');
    }

    /**
     * @brief returns if current character is a number.
     */
    inline bool isDigit() noexcept
    {
        return isBetween('0', '9');
    }

    /**
     * @brief returns if current character is tested character.
     */
    inline bool is(char value) noexcept
    {
        return !empty() && m_src.getCurrent() == value;
    }

    /**
     * @brief returns if current character is one of tested characters.
     */
    template<typename... Chars>
    inline bool is(char a, Chars... options) noexcept
    {
        char chars[]{a, options...};
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
     * @brief returns if current character is tested character.
     * If so, moves to next character.
     */
    inline bool match(char value) noexcept
    {
        if (is(value))
        {
            m_src.extract();
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
        const char chars[]{options...};
        for (const char option : chars)
        {
            if (is(option))
            {
                m_src.extract();
                return true;
            }
        }
        return false;
    }

// ===================================================================================== //

protected:

    /**
     * @brief Iterates to next non-whitespace char.
     */
    inline void skipWhitespace() noexcept
    {
        while (isWhitespace())
        {
            m_src.extract();
        }
    }

    /**
     * @brief chcecks if source is empty.
     */
    inline bool empty()
    {
        return m_src.empty();
    }

// ===================================================================================== //

    /**
     * @brief tokenizes tokentype number.
     */
    void tokenizeNumber();

    /**
     * @brief tokenizes string into identifier.
     */
    void tokenizeIdentifier() noexcept;

    /**
     * @brief tokenizes string value into keyword, function or identifier.
     */
    void tokenizeString();

    /**
     * @brief tokenizes string value into keyword, function or identifier.
     */
    void tokenizeChar();

    /**
     * @brief tokenizes operators.
     */
    void tokenizeOperator();

// ===================================================================================== //

public:

    /**
     * @brief go to next token.
     */
    void next();

    /**
     * @brief get current token.
     */
    inline const Token& get() const noexcept
    {
        return m_current;
    }

    /**
     * @brief get current token an move to next.
     */
    inline const Token extract()
    {
        auto tmp = m_current;
        next();
        return tmp;
    }

    inline bool isEof()
    {
        return m_current.getType() == TokenType::End;
    }
};

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */


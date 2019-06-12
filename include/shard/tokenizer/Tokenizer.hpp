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

// C++
#include <algorithm>

// Shard
#include "shard/SourceLocation.hpp"
#include "shard/Optional.hpp"
#include "shard/tokenizer/Source.hpp"
#include "shard/tokenizer/Token.hpp"
#include "shard/tokenizer/TokenizerIterator.hpp"

/* ************************************************************************* */

namespace shard::tokenizer {

/* ************************************************************************* */

/**
 * @brief      Shard lexical analyzer.
 */
class Tokenizer
{

public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      begin  The begin iterator.
     * @param      end    The end iterator.
     *
     * @tparam     IT     Iterator type.
     */
    template<typename IT>
    explicit Tokenizer(IT begin, IT end)
        : m_current(begin)
        , m_end(end)
    {
        // Nothing to do
    }

    /**
     * @brief      Constructor.
     *
     * @param      source  The source code.
     */
    explicit Tokenizer(Source& source)
        : Tokenizer(source.begin(), source.end())
    {
        // Nothing to do
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns if tokenizer is finished.
     *
     * @return     If finished.
     */
    bool isEmpty() const noexcept
    {
        return m_current == m_end;
    }

    /**
     * @brief      Returns the begin iterator.
     *
     * @return     The begin iterator.
     */
    TokenizerIterator begin() noexcept
    {
        return TokenizerIterator(*this);
    }

    /**
     * @brief      Returns the begin iterator.
     *
     * @return     The begin iterator.
     */
    TokenizerIterator end() noexcept
    {
        return TokenizerIterator();
    }

public:
    // Operations

    /**
     * @brief      Tokenize new token.
     *
     * @return     The token or nullopt if end of source is reached.
     */
    Optional<Token> tokenize();

private:
    // Operations

    /**
     * @brief      Return if current character matches given character.
     *
     * @param      value  The value compare to.
     *
     * @return     If values matches.
     */
    bool is(char value) const noexcept
    {
        return !isEmpty() && *m_current == value;
    }

    /**
     * @brief      Returns if current character is one of given characters.
     *
     * @param      values  The possible values.
     *
     * @tparam     VALUES    The values.
     *
     * @return     True if any, False otherwise.
     */
    template<typename... VALUES>
    bool isAny(VALUES... values) const noexcept
    {
        return (is(values) || ...);
    }

    /**
     * @brief      Returns if current character is between two characters.
     *
     * @param      value1  The first value.
     * @param      value2  The second value.
     *
     * @return     True if is between, False otherwise.
     */
    bool isBetween(char value1, char value2) const noexcept
    {
        return !isEmpty() && *m_current >= value1 && *m_current <= value2;
    }

    /**
     * @brief      Returns if current character is whitespace.
     *
     * @return     True if whitespace, False otherwise.
     */
    bool isWhitespace() const noexcept
    {
        return isAny(' ', '\t');
    }

    /**
     * @brief      Returns if current character is end of line.
     *
     * @return     True if end of line, False otherwise.
     */
    bool isEndOfLine() const noexcept
    {
        return is('\n');
    }

    /**
     * @brief      Returns if current character is a letter.
     *
     * @return     True if character is letter, False otherwise.
     */
    bool isLetter() const noexcept
    {
        return isBetween('a', 'z') || isBetween('A', 'Z');
    }

    /**
     * @brief      Returns if current character is a number.
     *
     * @return     True if character is digit, False otherwise.
     */
    bool isDigit() const noexcept
    {
        return isBetween('0', '9');
    }

    /**
     * @brief      Returns if current character is a letter, number or '_'.
     *
     * @return     True if identifier, False otherwise.
     */
    bool isIdentifier() noexcept
    {
        return isLetter() || isDigit() || is('_');
    }

    /**
     * @brief      Returns if current character is matches given character and
     *             if then advance.
     *
     * @param      value  The value match against to.
     *
     * @return     If values has matched.
     */
    bool match(char value) noexcept
    {
        if (is(value))
        {
            ++m_current;
            return true;
        }

        return false;
    }

    /**
     * @brief      Returns if current character is matches any of given
     *             characters and if then advance.
     *
     * @param      values  The values match against to.
     *
     * @tparam     VALUES  Value types to match.
     *
     * @return     If value has matched.
     */
    template<typename... VALUES>
    bool matchAny(VALUES... values) noexcept
    {
        if (isAny(values...))
        {
            ++m_current;
            return true;
        }

        return false;
    }

private:
    // Operations

    /**
     * @brief      Tokenizes an identifier.
     *
     * @return     The result token.
     */
    Token tokenizeIdentifier();

    /**
     * @brief      Tokenizes integer literal.
     *
     * @return     The result token.
     */
    Token tokenizeNumber();

    /**
     * @brief      Tokenizes string literal.
     *
     * @return     The result token.
     */
    Token tokenizeString();

    /**
     * @brief      Tokenizes character literal.
     *
     * @return     The result token.
     */
    Token tokenizeChar();

    /**
     * @brief      Tokenizes white space.
     *
     * @return     The result token.
     */
    Token tokenizeWhiteSpace();

    /**
     * @brief      Tokenizes end of line.
     *
     * @return     The result token.
     */
    Token tokenizeEndOfLine();

    /**
     * @brief      Tokenizes others.
     *
     * @return     The result token.
     */
    Token tokenizeOther();

private:
    // Data Members

    /// Current source position.
    SourceIterator m_current;

    /// End source position.
    SourceIterator m_end;
};

/* ************************************************************************* */

/**
 * @brief      Tokenize input range.
 *
 * @param      first      The first input iterator.
 * @param      last       The last input iterator.
 * @param      output     The output iterator.
 *
 * @tparam     INPUT_IT   Input iterator type.
 * @tparam     OUTPUT_IT  Output iterator type.
 *
 * @return     Result output iterator.
 */
template<typename INPUT_IT, typename OUTPUT_IT>
OUTPUT_IT tokenize(INPUT_IT first, INPUT_IT last, OUTPUT_IT output)
{
    // Create tokenizer
    Tokenizer tokenizer(first, last);

    return std::copy(tokenizer.begin(), tokenizer.end(), output);
}

/* ************************************************************************* */

} // namespace shard::tokenizer

/* ************************************************************************* */

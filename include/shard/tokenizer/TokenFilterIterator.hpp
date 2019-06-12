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
#include "shard/tokenizer/TokenType.hpp"
#include "shard/tokenizer/TokenizerIterator.hpp"

/* ************************************************************************* */

namespace shard::tokenizer {

/* ************************************************************************* */

/**
 * @brief      Input iterator with skipping specified tokens.
 *
 * @tparam     TYPES  Skipped token types.
 */
template<TokenType... TYPES>
class TokenFilterIterator
{
public:
    // Types

    /// A signed integer type that can be used to identify distance between
    /// iterators.
    using difference_type = std::ptrdiff_t;

    /// The type of the values that can be obtained by dereferencing the
    /// iterator. This type is void for output iterators.
    using value_type = Token;

    /// Defines a pointer to the type iterated over (value_type).
    using pointer = Token*;

    /// Defines a reference to the type iterated over (value_type).
    using reference = Token&;

    /// The category of the iterator.
    using iterator_category = std::input_iterator_tag;

public:
    // Ctors & Dtors

    /**
     * @brief      Default constructor.
     */
    TokenFilterIterator() = default;

    /**
     * @brief      Constructor.
     *
     * @param      it    The iterator.
     */
    explicit TokenFilterIterator(TokenizerIterator it)
        : m_it(it)
    {
        matchOrAdvance();
    }

public:
    // Operators

    /**
     * @brief      Returns current token.
     *
     * @return     The token.
     */
    const Token& operator*() const noexcept
    {
        return m_it.operator*();
    }

    /**
     * @brief      Returns current token.
     *
     * @return     The token.
     */
    const Token* operator->() const noexcept
    {
        return m_it.operator->();
    }

    /**
     * @brief      Fetch new token.
     *
     * @return     *this.
     */
    TokenFilterIterator& operator++()
    {
        ++m_it;
        matchOrAdvance();
        return *this;
    }

    /**
     * @brief      Fetch new token.
     *
     * @return     Copy of the iterator before advance.
     */
    TokenFilterIterator operator++(int)
    {
        TokenFilterIterator tmp(*this);
        ++(*this);
        return tmp;
    }

    /**
     * @brief      Compares two iterators.
     *
     * @param      rhs   Second iterator.
     *
     * @return     Are iterators equal?
     */
    bool operator==(const TokenFilterIterator& rhs) const noexcept
    {
        return m_it == rhs.m_it;
    }

    /**
     * @brief      Compares two iterators.
     *
     * @param      rhs   Second iterator.
     *
     * @return     Aren't iterators equal?
     */
    bool operator!=(const TokenFilterIterator& rhs) const noexcept
    {
        return !operator==(rhs);
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns wrapped iterator.
     *
     * @return     The iterator.
     */
    const TokenizerIterator& iterator() const noexcept
    {
        return m_it;
    }

private:
    // Operations

    /**
     * @brief      Test if current iterator matches filter requirements and if
     *             not advance to value that match requirements.
     */
    void matchOrAdvance() noexcept
    {
        // If current type matches one of required type, advance
        while (m_it.hasTokenizer() && ((m_it->type() == TYPES) || ...))
            ++m_it;
    }

private:
    // Data Members

    /// Wrapped iterator.
    TokenizerIterator m_it;
};

/* ************************************************************************* */

} // namespace shard::tokenizer

/* ************************************************************************* */

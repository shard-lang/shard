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
#include "shard/SourceLocation.hpp"
#include "shard/String.hpp"
#include "shard/ViewPtr.hpp"
#include "shard/tokenizer/Token.hpp"

/* ************************************************************************* */

namespace shard::tokenizer {

/* ************************************************************************* */

class Tokenizer; // FWD declaration

/* ************************************************************************* */

/**
 * @brief Input iterator for tokenizer.
 */
class TokenizerIterator
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
    TokenizerIterator() = default;

    /**
     * @brief      Constructor.
     *
     * @param      tokenizer  The tokenizer.
     */
    explicit TokenizerIterator(Tokenizer& tokenizer)
        : m_tokenizer(&tokenizer)
    {
        fetch();
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
        return m_current;
    }

    /**
     * @brief      Returns current token.
     *
     * @return     The token.
     */
    const Token* operator->() const noexcept
    {
        return &m_current;
    }

    /**
     * @brief      Fetch new token.
     *
     * @return     *this.
     */
    TokenizerIterator& operator++()
    {
        fetch();
        return *this;
    }

    /**
     * @brief      Fetch new token.
     *
     * @return     Copy of the iterator before advance.
     */
    TokenizerIterator operator++(int)
    {
        TokenizerIterator tmp(*this);
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
    bool operator==(const TokenizerIterator& rhs) const noexcept
    {
        // Only end iterator are same
        return m_tokenizer == nullptr && rhs.m_tokenizer == nullptr;
    }

    /**
     * @brief      Compares two iterators.
     *
     * @param      rhs   Second iterator.
     *
     * @return     Aren't iterators equal?
     */
    bool operator!=(const TokenizerIterator& rhs) const noexcept
    {
        return !operator==(rhs);
    }

public:
    // Accessors & Mutators

    /**
     * @brief      If iterator has valid tokenizer.
     *
     * @return     Is valid.
     */
    bool hasTokenizer() const noexcept
    {
        return m_tokenizer != nullptr;
    }

    /**
     * @brief      Returns the tokenizer.
     *
     * @return     The tokenizer.
     *
     * @pre        `hasTokenizer()`.
     */
    Tokenizer& tokenizer() const noexcept
    {
        return *m_tokenizer;
    }

private:
    // Operations

    /**
     * @brief      Fetch a new token.
     */
    void fetch();

private:
    // Data Members

    /// Tokenizer.
    ViewPtr<Tokenizer> m_tokenizer;

    /// Current token.
    Token m_current;
};

/* ************************************************************************* */

} // namespace shard::tokenizer

/* ************************************************************************* */

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
#include "shard/String.hpp"
#include "shard/Exception.hpp"
#include "shard/SourceLocation.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace tokenizer {

/* ************************************************************************* */

class TokenizerException
{

private:

    SourceLocation m_loc;
    const char * m_msg;

protected:

    explicit TokenizerException(const SourceLocation& loc, const char* msg): m_loc(loc), m_msg(msg) {}

public:

    const SourceLocation& getLocation() const noexcept
    {
        return m_loc;
    }

    String formatMessage() const noexcept
    {
        return String(m_msg) + " at " + toString(getLocation().getLine()) + ":" + toString(getLocation().getColumn()) + ".";
    }
};

/* ************************************************************************* */

class ExpectedNumberException : public TokenizerException
{

private:

    static constexpr char const * m_msg = "Expected number";

public:

    explicit ExpectedNumberException(const SourceLocation& loc): TokenizerException(loc, m_msg) {}
};

/* ************************************************************************* */

class UnknownOperatorException : public TokenizerException
{

private:

    static constexpr char const * m_msg = "Unknown operator";

public:

    explicit UnknownOperatorException(const SourceLocation& loc): TokenizerException(loc, m_msg) {}
};

/* ************************************************************************* */

class StringWithoutEndException : public TokenizerException
{

private:

    static constexpr char const * m_msg = "Closing character for string literal not found";

public:

    explicit StringWithoutEndException(const SourceLocation& loc): TokenizerException(loc, m_msg) {}
};

/* ************************************************************************* */

class CharWithoutEndException : public TokenizerException
{
    
private:

    static constexpr char const * m_msg = "Closing character for char literal not found";

public:

    explicit CharWithoutEndException(const SourceLocation& loc): TokenizerException(loc, m_msg) {}
};

/* ************************************************************************* */

class EmptyCharLiteralException : public TokenizerException
{
    
private:

    static constexpr char const * m_msg = "Cannot determine char value";

public:

    explicit EmptyCharLiteralException(const SourceLocation& loc): TokenizerException(loc, m_msg) {}
};

/* ************************************************************************* */

class NewlineInCharLiteralException : public TokenizerException
{
    
private:

    static constexpr char const * m_msg = "Newline is not allowed in char literal";

public:

    explicit NewlineInCharLiteralException(const SourceLocation& loc): TokenizerException(loc, m_msg) {}
};

/* ************************************************************************* */

class InvalidEscapeSequenceException : public TokenizerException
{
    
private:

    static constexpr char const * m_msg = "Unknown escape sequence";

public:

    explicit InvalidEscapeSequenceException(const SourceLocation& loc): TokenizerException(loc, m_msg) {}
};

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

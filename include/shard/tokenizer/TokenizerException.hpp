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

protected:

    SourceLocation m_loc;
    static const char m_msg[];

public:

    explicit TokenizerException(const SourceLocation loc): m_loc(loc) {}

    const SourceLocation& getLocation() const noexcept
    {
        return m_loc;
    }

    String what() const noexcept
    {
        return String(m_msg) + " at " + toString(m_loc.getLine()) + ":" + toString(m_loc.getColumn()) + ".";
    }
};

/* ************************************************************************* */

class ExpectedNumberException : public TokenizerException
{

protected:

    static constexpr char m_msg[] = "Expected number";

public:

    explicit ExpectedNumberException(const SourceLocation loc): TokenizerException(loc) {}

};

/* ************************************************************************* */

class UnknownOperatorException : public TokenizerException
{

protected:

    static constexpr char m_msg[] = "Unknown operator";

public:

    explicit UnknownOperatorException(const SourceLocation loc): TokenizerException(loc) {}

};

/* ************************************************************************* */

class StringWithoutEndException : public TokenizerException
{

protected:

    static constexpr char m_msg[] = "Closing character for string not found";

public:

    explicit StringWithoutEndException(const SourceLocation loc): TokenizerException(loc) {}

};

/* ************************************************************************* */

class CharWithoutEndException : public TokenizerException
{
    
protected:

    static constexpr char m_msg[] = "Closing character for char literal not found";

public:

    explicit CharWithoutEndException(const SourceLocation loc): TokenizerException(loc) {}
};

/* ************************************************************************* */

class EmptyCharLiteralException : public TokenizerException
{
    
protected:

    static constexpr char m_msg[] = "Cannot determine char value";

public:

    explicit EmptyCharLiteralException(const SourceLocation loc): TokenizerException(loc) {}

};

class NewlineInCharLiteralException : public TokenizerException
{
    
protected:

    static constexpr char m_msg[] = "Found newline in char literal";

public:

    explicit NewlineInCharLiteralException(const SourceLocation loc): TokenizerException(loc) {}

};

/* ************************************************************************* */

class InvalidEscapeSequenceException : public TokenizerException
{
    
protected:

    static constexpr char m_msg [] = "Unknown escape sequence";

public:

    explicit InvalidEscapeSequenceException(const SourceLocation loc): TokenizerException(loc) {}

};

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

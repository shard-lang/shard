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

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace tokenizer {

/* ************************************************************************* */

class TokenizerException : public Exception
{
};

/* ************************************************************************* */

class ExpectedNumberException : public TokenizerException
{
    const char *what() const noexcept
    {
        return "Expected Number.";
    }
};

/* ************************************************************************* */

class UnknownOperatorException : public TokenizerException
{
    String m_msg;

public:

    explicit UnknownOperatorException(const char op)
            : m_msg(String("Unknown operator (") + op + ")") {}

    const char *what() const noexcept
    {
        return m_msg.c_str();
    }
};

/* ************************************************************************* */

class StringWithoutEndException : public TokenizerException
{
    const char *what() const noexcept
    {
        return "Escape character for string not found.";
    }
};

/* ************************************************************************* */

class CharWithoutEndException : public TokenizerException
{
    const char *what() const noexcept
    {
        return "Escape character for char not found.";
    }
};

/* ************************************************************************* */

class EmptyCharLiteralException : public TokenizerException
{
    const char *what() const noexcept
    {
        return "Cannot determine char value.";
    }
};

class NewlineInCharLiteralException : public TokenizerException
{
    const char *what() const noexcept
    {
        return "Newline is not allowed in char literal.";
    }
};

/* ************************************************************************* */

class InvalidEscapeSequenceException : public TokenizerException
{
    const char *what() const noexcept
    {
        return "Unknown escape sequence.";
    }
};

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

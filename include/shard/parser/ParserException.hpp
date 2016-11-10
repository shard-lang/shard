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
#include "shard/SourceLocation.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace parser {

/* ************************************************************************* */

class ParserException
{

private:

    const char * m_msg;

protected:

    explicit ParserException(const char* msg): m_msg(msg) {}

public:

    String formatMessage() const noexcept
    {
        return String(m_msg);
    }
};

/* ************************************************************************* */

class ExpectedPrimaryExprException : public ParserException
{

private:

    static constexpr char const * m_msg = "Expected primary expression";

public:

    explicit ExpectedPrimaryExprException(): ParserException(m_msg) {}
};

/* ************************************************************************* */

class ExpectedClosingParenException : public ParserException
{

private:

    static constexpr char const * m_msg = "Expected closing parenthesis";

public:

    explicit ExpectedClosingParenException(): ParserException(m_msg) {}
};

/* ************************************************************************* */

class ExpectedColonException : public ParserException
{

private:

    static constexpr char const * m_msg = "Expected colon for ternary expression";

public:

    explicit ExpectedColonException(): ParserException(m_msg) {}
};

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */
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

class ExpectedWhileException : public ParserException
{

private:

    static constexpr char const * m_msg = "Expected keyword while";

public:

    explicit ExpectedWhileException(): ParserException(m_msg) {}
};

/* ************************************************************************* */

class ExpectedIdentifierException : public ParserException
{

private:

    static constexpr char const * m_msg = "Expected identifier";

public:

    explicit ExpectedIdentifierException(): ParserException(m_msg) {}
};

/* ************************************************************************* */

class ExpectedParenException : public ParserException
{

private:

    static constexpr char const * m_msg = "Expected opening parenthesis";

public:

    explicit ExpectedParenException(): ParserException(m_msg) {}
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

class ExpectedSquareException : public ParserException
{

private:

    static constexpr char const * m_msg = "Expected opening square";

public:

    explicit ExpectedSquareException(): ParserException(m_msg) {}
};

/* ************************************************************************* */

class ExpectedClosingSquareException : public ParserException
{

private:

    static constexpr char const * m_msg = "Expected closing square";

public:

    explicit ExpectedClosingSquareException(): ParserException(m_msg) {}
};

/* ************************************************************************* */

class ExpectedBraceException : public ParserException
{

private:

    static constexpr char const * m_msg = "Expected opening brace";

public:

    explicit ExpectedBraceException(): ParserException(m_msg) {}
};

/* ************************************************************************* */

class ExpectedClosingBraceException : public ParserException
{

private:

    static constexpr char const * m_msg = "Expected closing brace";

public:

    explicit ExpectedClosingBraceException(): ParserException(m_msg) {}
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

class ExpectedSemicolonException : public ParserException
{

private:

    static constexpr char const * m_msg = "Expected semicolon";

public:

    explicit ExpectedSemicolonException(): ParserException(m_msg) {}
};

/* ************************************************************************* */

class ExpectedDeclException : public ParserException
{

private:

    static constexpr char const * m_msg = "Expected declaration";

public:

    explicit ExpectedDeclException(): ParserException(m_msg) {}
};

/* ************************************************************************* */

class InvalidDeclException : public ParserException
{

private:

    static constexpr char const * m_msg = "Invalid declaration (probably a missing semicolon)";

public:

    explicit InvalidDeclException(): ParserException(m_msg) {}
};

/* ************************************************************************* */

class ExpectedExprException : public ParserException
{

private:

    static constexpr char const * m_msg = "Expected expression";

public:

    explicit ExpectedExprException(): ParserException(m_msg) {}
};

/* ************************************************************************* */

class ExpectedStmtException : public ParserException
{

private:

    static constexpr char const * m_msg = "Expected statement";

public:

    explicit ExpectedStmtException(): ParserException(m_msg) {}
};

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */
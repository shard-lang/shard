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

#include <cmath>
#include <limits>

// Shard
#include "shard/String.hpp"
#include "shard/SourceLocation.hpp"
#include "shard/tokenizer/TokenType.hpp"
#include "shard/tokenizer/KeywordType.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace tokenizer {

/* ************************************************************************* */

class Token
{

public:

    using FloatType = double;
    using CharType = char32_t;
    using IntType = long int;

private:

    SourceLocation m_loc;

    TokenType m_type;

    KeywordType m_kType;
    String m_sValue;
    FloatType m_fValue;
    CharType m_cValue;
    IntType m_iValue;

/* ************************************************************************* */

public:

    Token() = default;

    /**
     * @brief constructs Token of given type.
     */
    explicit Token
    (
        TokenType type,
        KeywordType keyVal = {},
        const String& strVal = {},
        FloatType fltVal = {},
        CharType charVal = {},
        IntType intVal = {}
    ):
        m_type(type),
        m_kType(keyVal),
        m_sValue(strVal),
        m_fValue(fltVal),
        m_cValue(charVal),
        m_iValue(intVal) {}

    /**
     * @brief constructs Token of type Keyword with given KeywordType value.
     */
    static Token Keyword(KeywordType type)
    {
        return Token(TokenType::Keyword, type);
    }

    /**
     * @brief constructs Token of type identifier with given String value.
     */ 
    static Token Identifier(const String& value)
    {
        return Token(TokenType::Identifier, {}, value);
    }

    /**
     * @brief constructs Token of type string with given String value.
     */ 
    static Token StringLiteral(const String& value)
    {
        return Token(TokenType::String, {}, value);
    }
    
    /**
     * @brief constructs Token of type comment block with given String value.
     */ 
    static Token CommentBlock(const String& value)
    {
        return Token(TokenType::CommentBlock, {}, value);
    }

    /**
     * @brief constructs Token of type comment line with given String value.
     */ 
    static Token CommentLine(const String& value)
    {
        return Token(TokenType::CommentLine, {}, value);
    }

    /**
     * @brief constructs Token of type Float with given Float value.
     */
    static Token FloatLiteral(FloatType value)
    {
        return Token(TokenType::Float, {}, {}, value);
    }

    /**
     * @brief constructs Token of type Char with given integer value - multibyte character.
     */
    static Token CharLiteral(CharType value)
    {
        return Token(TokenType::Char, {}, {}, {}, value);
    }
       
    /**
     * @brief constructs Token of type Int with given IntType value.
     */ 
    static Token IntLiteral(IntType value)
    {
        return Token(TokenType::Int, {}, {}, {}, {}, value);
    }

/* ************************************************************************* */

public:

    /**
     * @brief returns Type of current token.
     */
    inline TokenType getType() const noexcept
    {
        return m_type;
    }

    /**
     * @brief returns String value of current token.
     */
    inline const String& getStringValue() const noexcept
    {
        return m_sValue;
    }
    
    /**
     * @brief returns FloatValue of current token.
     */
    inline FloatType getFloatValue() const noexcept
    {
        return m_fValue;
    }
    
    /**
     * @brief returns CharValue of current token.
     */
    inline CharType getCharValue() const noexcept
    {
        return m_cValue;
    }
    
    /**
     * @brief returns IntValue of current token.
     */
    inline IntType getIntValue() const noexcept
    {
        return m_iValue;
    }

    /**
     * @brief returns KeywordType of current token.
     */
    inline KeywordType getKeywordType() const noexcept
    {
        return m_kType;
    }

/* ************************************************************************* */

public:

    /**
     * @brief returns SourceLocation of tokens start.
     */
    inline SourceLocation getLocation() const noexcept
    {
        return m_loc;
    }

    /**
     * @brief sets SourceLocation of token.
     */
    inline void setLocation(SourceLocation loc) noexcept
    {
        m_loc = loc;
    }
};

/* ************************************************************************* */

inline bool operator==(const Token& lhs, const Token& rhs)
{
    if (lhs.getType() != rhs.getType())
    {
        return false;
    }

    switch (lhs.getType())
    {
        case TokenType::CommentBlock:
        case TokenType::CommentLine:
        case TokenType::Identifier:
        case TokenType::String:
            return lhs.getStringValue() == rhs.getStringValue();
        case TokenType::Keyword:
            return lhs.getKeywordType() == rhs.getKeywordType();
        case TokenType::Float:
            return std::abs(lhs.getFloatValue() - rhs.getFloatValue())
                    < std::numeric_limits<Token::FloatType>::epsilon();
        case TokenType::Char:
            return lhs.getCharValue() == rhs.getCharValue();
        case TokenType::Int:
            return lhs.getIntValue() == rhs.getIntValue();
        default:
            return true;
    }
}

inline bool operator!=(const Token& lhs, const Token& rhs)
{
    return !(lhs == rhs);
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

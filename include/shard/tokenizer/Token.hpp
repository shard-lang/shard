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
#include "shard/Variant.hpp"
#include "shard/SourceLocation.hpp"
#include "shard/tokenizer/TokenType.hpp"

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

    Variant m_value;

/* ************************************************************************* */

public:

    Token() = default;

    /**
     * @brief constructs Token of given type.
     */
    explicit Token(TokenType type):
        m_type(type), m_value(nullptr){}

    /**
     * @brief constructs Token of given type with given value.
     */
    template <typename T>
    explicit Token(TokenType type, const T& value):
        m_type(type), m_value(value) {}

    /**
     * @brief constructs Token of type identifier with given String value.
     */ 
    static Token Identifier(const String& value)
    {
        return Token(TokenType::Identifier, value);
    }

    /**
     * @brief constructs Token of type string with given String value.
     */ 
    static Token StringLiteral(const String& value)
    {
        return Token(TokenType::StringLiteral, value);
    }
    
    /**
     * @brief constructs Token of type comment block with given String value.
     */ 
    static Token CommentBlock(const String& value)
    {
        return Token(TokenType::CommentBlock, value);
    }

    /**
     * @brief constructs Token of type comment line with given String value.
     */ 
    static Token CommentLine(const String& value)
    {
        return Token(TokenType::CommentLine, value);
    }

    /**
     * @brief constructs Token of type Float with given Float value.
     */
    static Token FloatLiteral(FloatType value)
    {
        return Token(TokenType::FloatLiteral, value);
    }

    /**
     * @brief constructs Token of type Char with given integer value - multibyte character.
     */
    static Token CharLiteral(CharType value)
    {
        return Token(TokenType::CharLiteral, value);
    }
       
    /**
     * @brief constructs Token of type Int with given IntType value.
     */ 
    static Token IntLiteral(IntType value)
    {
        return Token(TokenType::IntLiteral, value);
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
     * @brief returns value of current token.
     */
    template <typename T>
    inline T getValue() const noexcept
    {
        return m_value.get<T>();
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
        case TokenType::StringLiteral:
            return lhs.getValue<String>() == rhs.getValue<String>();
        case TokenType::FloatLiteral:
            return std::abs(lhs.getValue<Token::FloatType>() - rhs.getValue<Token::FloatType>())
                    < std::numeric_limits<Token::FloatType>::epsilon();
        case TokenType::CharLiteral:
            return lhs.getValue<Token::CharType>() == rhs.getValue<Token::CharType>();
        case TokenType::IntLiteral:
            return lhs.getValue<Token::IntType>() == rhs.getValue<Token::IntType>();
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

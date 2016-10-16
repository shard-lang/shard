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
// Shard Core
#include "core/src/String.hpp"
// Shard Tokenizer
#include "TokenType.hpp"
#include "KeywordType.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace tokenizer {

/* ************************************************************************* */

class Token
{

public:

    using FloatType = double;
    using IntType = long int;

private:

    TokenType m_type;

    KeywordType m_kType;
    String m_sValue;
    FloatType m_fValue;
    char m_cValue;
    IntType m_iValue;

public:

    Token() = default;

    Token(TokenType type):
        m_type(type) {}

    Token(TokenType type, String value):
        m_type(type), m_sValue(value) {}
     
    Token(String value):
        m_type(TokenType::Identifier), m_sValue(value) {}
   
    Token (FloatType value):
        m_type(TokenType::Float), m_fValue(value) {}
        
    Token(char value):
        m_type(TokenType::Char), m_cValue(value) {}
        
    Token(IntType value):
        m_type(TokenType::Int), m_iValue(value) {}

    Token(KeywordType type):
        m_type(TokenType::Keyword), m_kType(type) {}

    inline TokenType getType() const noexcept
    {
        return m_type;
    }

    inline const String& getStringValue() const noexcept
    {
        return m_sValue;
    }
    
    inline FloatType getFloatValue() const noexcept
    {
        return m_fValue;
    }
    
    inline float getCharValue() const noexcept
    {
        return m_cValue;
    }
    
    inline IntType getIntValue() const noexcept
    {
        return m_iValue;
    }

    inline KeywordType getKeywordType() const noexcept
    {
        return m_kType;
    }
};

inline bool operator==(const Token& lhs, const Token& rhs)
{
    if (lhs.getType() != rhs.getType())
    {
        return false;
    }

    switch (lhs.getType())
    {
        case TokenType::Keyword: return lhs.getKeywordType() == rhs.getKeywordType();
        case TokenType::String: return lhs.getStringValue() == rhs.getStringValue();
        case TokenType::Float: return
                    std::abs(lhs.getFloatValue() - rhs.getFloatValue())
                    < std::numeric_limits<Token::FloatType>::epsilon();
        case TokenType::Char: return lhs.getCharValue() == rhs.getCharValue();
        case TokenType::Int: return lhs.getIntValue() == rhs.getIntValue();
        default: return true;
    }
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

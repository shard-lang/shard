
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

// Declaration
#include "shard/interpreter/Value.hpp"

// Shard
#include "shard/Assert.hpp"
#include "shard/ast/Expr.hpp"
#include "shard/interpreter/Exception.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace interpreter {

/* ************************************************************************* */

bool operator==(const Value& lhs, const Value& rhs)
{
    if (lhs.getKind() != rhs.getKind())
        throw Exception("Operands have different types");

    switch (lhs.getKind())
    {
    case ValueKind::Null:       return true;
    case ValueKind::Bool:       return lhs.asBool() == rhs.asBool();
    case ValueKind::Int:        return lhs.asInt() == rhs.asInt();
    case ValueKind::Float:      return lhs.asFloat() == rhs.asFloat();
    case ValueKind::Char:       return lhs.asChar() == rhs.asChar();
    case ValueKind::String:     return lhs.asString() == rhs.asString();
    case ValueKind::Function:   throw Exception("Cannot compare two functions");
    }
}

/* ************************************************************************* */

bool operator<(const Value& lhs, const Value& rhs)
{
    if (lhs.getKind() != rhs.getKind())
        throw Exception("Operands have different types");

    switch (lhs.getKind())
    {
    case ValueKind::Null:       throw Exception("Cannot LT two nulls");
    case ValueKind::Bool:       return lhs.asBool() < rhs.asBool();
    case ValueKind::Int:        return lhs.asInt() < rhs.asInt();
    case ValueKind::Float:      return lhs.asFloat() < rhs.asFloat();
    case ValueKind::Char:       return lhs.asChar() < rhs.asChar();
    case ValueKind::String:     return lhs.asString() < rhs.asString();
    case ValueKind::Function:   throw Exception("Cannot compare two functions");
    }
}

/* ************************************************************************* */

Value operator+(const Value& lhs, const Value& rhs)
{
    if (lhs.getKind() != rhs.getKind())
        throw Exception("Operands have different types");

    switch (lhs.getKind())
    {
    case ValueKind::Null:       throw Exception("Cannot add two nulls");
    case ValueKind::Bool:       return lhs.asBool() + rhs.asBool();
    case ValueKind::Int:        return lhs.asInt() + rhs.asInt();
    case ValueKind::Float:      return lhs.asFloat() + rhs.asFloat();
    case ValueKind::Char:       throw Exception("Cannot add two chars");
    case ValueKind::String:     return lhs.asString() + rhs.asString();
    case ValueKind::Function:   throw Exception("Cannot add two functions");
    }
}

/* ************************************************************************* */

Value operator-(const Value& lhs, const Value& rhs)
{
    if (lhs.getKind() != rhs.getKind())
        throw Exception("Operands have different types");

    switch (lhs.getKind())
    {
    case ValueKind::Null:       throw Exception("Cannot subtract two nulls");
    case ValueKind::Bool:       return lhs.asBool() - rhs.asBool();
    case ValueKind::Int:        return lhs.asInt() - rhs.asInt();
    case ValueKind::Float:      return lhs.asFloat() - rhs.asFloat();
    case ValueKind::Char:       throw Exception("Cannot subtract two chars");
    case ValueKind::String:     throw Exception("Cannot subtract two strings");
    case ValueKind::Function:   throw Exception("Cannot subtract two functions");
    }
}

/* ************************************************************************* */

Value operator*(const Value& lhs, const Value& rhs)
{
    if (lhs.getKind() != rhs.getKind())
        throw Exception("Operands have different types");

    switch (lhs.getKind())
    {
    case ValueKind::Null:       throw Exception("Cannot multiply two nulls");
    case ValueKind::Bool:       return lhs.asBool() * rhs.asBool();
    case ValueKind::Int:        return lhs.asInt() * rhs.asInt();
    case ValueKind::Float:      return lhs.asFloat() * rhs.asFloat();
    case ValueKind::Char:       throw Exception("Cannot multiply two chars");
    case ValueKind::String:     return lhs.asString() * rhs.asString();
    case ValueKind::Function:   throw Exception("Cannot multiply two functions");
    }
}

/* ************************************************************************* */

Value operator/(const Value& lhs, const Value& rhs)
{
    if (lhs.getKind() != rhs.getKind())
        throw Exception("Operands have different types");

    switch (lhs.getKind())
    {
    case ValueKind::Null:       throw Exception("Cannot divide two nulls");
    case ValueKind::Bool:       return lhs.asBool() / rhs.asBool();
    case ValueKind::Int:        return lhs.asInt() / rhs.asInt();
    case ValueKind::Float:      return lhs.asFloat() / rhs.asFloat();
    case ValueKind::Char:       throw Exception("Cannot divide two chars");
    case ValueKind::String:     throw Exception("Cannot divide two strings");
    case ValueKind::Function:   throw Exception("Cannot divide two functions");
    }
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */


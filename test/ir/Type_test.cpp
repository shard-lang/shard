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

// C++
#include <type_traits>

// GTest
#include "gtest/gtest.h"

// Shard
#include "shard/ir/Type.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ir;

/* ************************************************************************ */

template<typename T>
constexpr std::add_const_t<T>& asConst(T& t) noexcept
{
    return t;
}

/* ************************************************************************ */

TEST(Type, Int8)
{
    TypeInt8 type;

    EXPECT_EQ(type.kind(), TypeKind::Int8);
    EXPECT_TRUE(type.is<TypeInt8>());
}

/* ************************************************************************ */

TEST(Type, Int16)
{
    TypeInt16 type;

    EXPECT_EQ(type.kind(), TypeKind::Int16);
    EXPECT_TRUE(type.is<TypeInt16>());
}

/* ************************************************************************ */

TEST(Type, Int32)
{
    TypeInt32 type;

    EXPECT_EQ(type.kind(), TypeKind::Int32);
    EXPECT_TRUE(type.is<TypeInt32>());
}

/* ************************************************************************ */

TEST(Type, Int64)
{
    TypeInt64 type;

    EXPECT_EQ(type.kind(), TypeKind::Int64);
    EXPECT_TRUE(type.is<TypeInt64>());
}

/* ************************************************************************ */

TEST(Type, Float32)
{
    TypeFloat32 type;

    EXPECT_EQ(type.kind(), TypeKind::Float32);
    EXPECT_TRUE(type.is<TypeFloat32>());
}

/* ************************************************************************ */

TEST(Type, Float64)
{
    TypeFloat64 type;

    EXPECT_EQ(type.kind(), TypeKind::Float64);
    EXPECT_TRUE(type.is<TypeFloat64>());
}

/* ************************************************************************ */

TEST(Type, Struct)
{
    // struct { Int8 field1; Int32 field2; };
    TypeStruct type({
        TypeInt8::instance(),
        TypeInt32::instance(),
    });

    EXPECT_EQ(type.kind(), TypeKind::Struct);
    EXPECT_TRUE(type.is<TypeStruct>());
    ASSERT_EQ(type.fields().size(), 2);
    ASSERT_EQ(type.size(), 2);
    EXPECT_EQ(type.field(0), TypeInt8::instance());
    EXPECT_EQ(type.field(1), TypeInt32::instance());
    EXPECT_EQ(asConst(type).field(0), TypeInt8::instance());
    EXPECT_EQ(asConst(type).field(1), TypeInt32::instance());
}

/* ************************************************************************ */

TEST(Type, cast)
{
    ViewPtr<Type> type = TypeInt8::instance();

    EXPECT_TRUE(type->is<TypeInt8>());
    EXPECT_EQ(type->as<TypeInt8>().kind(), TypeKind::Int8);
}

/* ************************************************************************ */
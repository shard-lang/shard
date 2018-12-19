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

// GTest
#include "gtest/gtest.h"

// Shard
#include "shard/ir/Constant.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ir;

/* ************************************************************************ */

TEST(Constant, Int1)
{
    ConstInt1 value(true);

    EXPECT_EQ(value.type()->kind(), TypeKind::Int1);
    EXPECT_EQ(value.value(), true);
    testing::StaticAssertTypeEq<typename ConstInt1::ValueType, bool>();
}

/* ************************************************************************ */

TEST(Constant, Int8)
{
    ConstInt8 value(30);

    EXPECT_EQ(value.type()->kind(), TypeKind::Int8);
    EXPECT_EQ(value.value(), 30);
    testing::StaticAssertTypeEq<typename ConstInt8::ValueType, std::int8_t>();
}

/* ************************************************************************ */

TEST(Constant, Int16)
{
    ConstInt16 value(836);

    EXPECT_EQ(value.type()->kind(), TypeKind::Int16);
    EXPECT_EQ(value.value(), 836);
    testing::StaticAssertTypeEq<typename ConstInt16::ValueType, std::int16_t>();
}

/* ************************************************************************ */

TEST(Constant, Int32)
{
    ConstInt32 value(4756);

    EXPECT_EQ(value.type()->kind(), TypeKind::Int32);
    EXPECT_EQ(value.value(), 4756);
    testing::StaticAssertTypeEq<typename ConstInt32::ValueType, std::int32_t>();
}

/* ************************************************************************ */

TEST(Constant, Int64)
{
    ConstInt64 value(7652);

    EXPECT_EQ(value.type()->kind(), TypeKind::Int64);
    EXPECT_EQ(value.value(), 7652);
    testing::StaticAssertTypeEq<typename ConstInt64::ValueType, std::int64_t>();
}

/* ************************************************************************ */

TEST(Constant, Float32)
{
    ConstFloat32 value(753.1f);

    EXPECT_EQ(value.type()->kind(), TypeKind::Float32);
    EXPECT_FLOAT_EQ(value.value(), 753.1f);
    testing::StaticAssertTypeEq<typename ConstFloat32::ValueType, float>();
}

/* ************************************************************************ */

TEST(Constant, Float64)
{
    ConstFloat64 value(853.457);

    EXPECT_EQ(value.type()->kind(), TypeKind::Float64);
    EXPECT_DOUBLE_EQ(value.value(), 853.457);
    testing::StaticAssertTypeEq<typename ConstFloat64::ValueType, double>();
}

/* ************************************************************************ */
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
#include "shard/interpreter/Value.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::interpreter;

/* ************************************************************************ */

TEST(Value, test1)
{
    Value value;

    EXPECT_TRUE(value.isNothing());
    EXPECT_FALSE(value.is<bool>());
    EXPECT_FALSE(value.is<int8_t>());
    EXPECT_FALSE(value.is<int16_t>());
    EXPECT_FALSE(value.is<int32_t>());
    EXPECT_FALSE(value.is<int64_t>());
    EXPECT_FALSE(value.is<float>());
    EXPECT_FALSE(value.is<double>());

    value = true;

    EXPECT_FALSE(value.isNothing());
    EXPECT_TRUE(value.is<bool>());
    EXPECT_FALSE(value.is<int8_t>());
    EXPECT_FALSE(value.is<int16_t>());
    EXPECT_FALSE(value.is<int32_t>());
    EXPECT_FALSE(value.is<int64_t>());
    EXPECT_FALSE(value.is<float>());
    EXPECT_FALSE(value.is<double>());
    EXPECT_EQ(true, value.get<bool>());

    value = int8_t{5};

    EXPECT_FALSE(value.isNothing());
    EXPECT_FALSE(value.is<bool>());
    EXPECT_TRUE(value.is<int8_t>());
    EXPECT_FALSE(value.is<int16_t>());
    EXPECT_FALSE(value.is<int32_t>());
    EXPECT_FALSE(value.is<int64_t>());
    EXPECT_FALSE(value.is<float>());
    EXPECT_FALSE(value.is<double>());
    EXPECT_EQ(5, value.get<int8_t>());

    value = int16_t{-3};

    EXPECT_FALSE(value.isNothing());
    EXPECT_FALSE(value.is<bool>());
    EXPECT_FALSE(value.is<int8_t>());
    EXPECT_TRUE(value.is<int16_t>());
    EXPECT_FALSE(value.is<int32_t>());
    EXPECT_FALSE(value.is<int64_t>());
    EXPECT_FALSE(value.is<float>());
    EXPECT_FALSE(value.is<double>());
    EXPECT_EQ(-3, value.get<int16_t>());

    value = int32_t{453};

    EXPECT_FALSE(value.isNothing());
    EXPECT_FALSE(value.is<bool>());
    EXPECT_FALSE(value.is<int8_t>());
    EXPECT_FALSE(value.is<int16_t>());
    EXPECT_TRUE(value.is<int32_t>());
    EXPECT_FALSE(value.is<int64_t>());
    EXPECT_FALSE(value.is<float>());
    EXPECT_FALSE(value.is<double>());
    EXPECT_EQ(453, value.get<int32_t>());

    value = int64_t{45345};

    EXPECT_FALSE(value.isNothing());
    EXPECT_FALSE(value.is<bool>());
    EXPECT_FALSE(value.is<int8_t>());
    EXPECT_FALSE(value.is<int16_t>());
    EXPECT_FALSE(value.is<int32_t>());
    EXPECT_TRUE(value.is<int64_t>());
    EXPECT_FALSE(value.is<float>());
    EXPECT_FALSE(value.is<double>());
    EXPECT_EQ(45345, value.get<int64_t>());

    value = float{3.8263f};

    EXPECT_FALSE(value.isNothing());
    EXPECT_FALSE(value.is<bool>());
    EXPECT_FALSE(value.is<int8_t>());
    EXPECT_FALSE(value.is<int16_t>());
    EXPECT_FALSE(value.is<int32_t>());
    EXPECT_FALSE(value.is<int64_t>());
    EXPECT_TRUE(value.is<float>());
    EXPECT_FALSE(value.is<double>());
    EXPECT_EQ(3.8263f, value.get<float>());

    value = double{382.63};

    EXPECT_FALSE(value.isNothing());
    EXPECT_FALSE(value.is<bool>());
    EXPECT_FALSE(value.is<int8_t>());
    EXPECT_FALSE(value.is<int16_t>());
    EXPECT_FALSE(value.is<int32_t>());
    EXPECT_FALSE(value.is<int64_t>());
    EXPECT_FALSE(value.is<float>());
    EXPECT_TRUE(value.is<double>());
    EXPECT_EQ(382.63, value.get<double>());
}

/* ************************************************************************ */
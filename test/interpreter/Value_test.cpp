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

// C++
#include <optional>

// Shard
#include "shard/interpreter/Exception.hpp"
#include "shard/interpreter/Value.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::interpreter;

/* ************************************************************************ */

struct Visitor
{
    std::optional<bool> value_bool;
    std::optional<int8_t> value_int8_t;
    std::optional<int16_t> value_int16_t;
    std::optional<int32_t> value_int32_t;
    std::optional<int64_t> value_int64_t;
    std::optional<float> value_float;
    std::optional<double> value_double;

    void operator()(std::monostate) const
    {
        // Nothing
    }

    void operator()(bool arg)
    {
        value_bool = arg;
    }

    void operator()(int8_t arg)
    {
        value_int8_t = arg;
    }

    void operator()(int16_t arg)
    {
        value_int16_t = arg;
    }

    void operator()(int32_t arg)
    {
        value_int32_t = arg;
    }

    void operator()(int64_t arg)
    {
        value_int64_t = arg;
    }

    void operator()(float arg)
    {
        value_float = arg;
    }

    void operator()(double arg)
    {
        value_double = arg;
    }
};

/* ************************************************************************ */

TEST(Value, test1)
{
    Value value;

    {
        EXPECT_TRUE(value.isNothing());
        EXPECT_FALSE(value.is<bool>());
        EXPECT_FALSE(value.is<int8_t>());
        EXPECT_FALSE(value.is<int16_t>());
        EXPECT_FALSE(value.is<int32_t>());
        EXPECT_FALSE(value.is<int64_t>());
        EXPECT_FALSE(value.is<float>());
        EXPECT_FALSE(value.is<double>());

        EXPECT_THROW(value.get<bool>(), interpreter::Exception);
        EXPECT_THROW(value.get<int8_t>(), interpreter::Exception);
        EXPECT_THROW(value.get<int16_t>(), interpreter::Exception);
        EXPECT_THROW(value.get<int32_t>(), interpreter::Exception);
        EXPECT_THROW(value.get<int64_t>(), interpreter::Exception);
        EXPECT_THROW(value.get<float>(), interpreter::Exception);
        EXPECT_THROW(value.get<double>(), interpreter::Exception);

        Visitor visitor;
        value.visit(visitor);

        EXPECT_FALSE(visitor.value_bool.has_value());
        EXPECT_FALSE(visitor.value_int8_t.has_value());
        EXPECT_FALSE(visitor.value_int16_t.has_value());
        EXPECT_FALSE(visitor.value_int32_t.has_value());
        EXPECT_FALSE(visitor.value_int64_t.has_value());
        EXPECT_FALSE(visitor.value_float.has_value());
        EXPECT_FALSE(visitor.value_double.has_value());
    }

    {
        value = true;

        EXPECT_FALSE(value.isNothing());
        ASSERT_TRUE(value.is<bool>());
        EXPECT_FALSE(value.is<int8_t>());
        EXPECT_FALSE(value.is<int16_t>());
        EXPECT_FALSE(value.is<int32_t>());
        EXPECT_FALSE(value.is<int64_t>());
        EXPECT_FALSE(value.is<float>());
        EXPECT_FALSE(value.is<double>());

        ASSERT_NO_THROW(value.get<bool>());
        EXPECT_THROW(value.get<int8_t>(), interpreter::Exception);
        EXPECT_THROW(value.get<int16_t>(), interpreter::Exception);
        EXPECT_THROW(value.get<int32_t>(), interpreter::Exception);
        EXPECT_THROW(value.get<int64_t>(), interpreter::Exception);
        EXPECT_THROW(value.get<float>(), interpreter::Exception);
        EXPECT_THROW(value.get<double>(), interpreter::Exception);

        EXPECT_EQ(true, value.get<bool>());

        Visitor visitor;
        value.visit(visitor);

        ASSERT_TRUE(visitor.value_bool.has_value());
        EXPECT_FALSE(visitor.value_int8_t.has_value());
        EXPECT_FALSE(visitor.value_int16_t.has_value());
        EXPECT_FALSE(visitor.value_int32_t.has_value());
        EXPECT_FALSE(visitor.value_int64_t.has_value());
        EXPECT_FALSE(visitor.value_float.has_value());
        EXPECT_FALSE(visitor.value_double.has_value());

        EXPECT_EQ(true, *visitor.value_bool);
    }

    {
        value = int8_t{5};

        EXPECT_FALSE(value.isNothing());
        EXPECT_FALSE(value.is<bool>());
        ASSERT_TRUE(value.is<int8_t>());
        EXPECT_FALSE(value.is<int16_t>());
        EXPECT_FALSE(value.is<int32_t>());
        EXPECT_FALSE(value.is<int64_t>());
        EXPECT_FALSE(value.is<float>());
        EXPECT_FALSE(value.is<double>());

        EXPECT_THROW(value.get<bool>(), interpreter::Exception);
        ASSERT_NO_THROW(value.get<int8_t>());
        EXPECT_THROW(value.get<int16_t>(), interpreter::Exception);
        EXPECT_THROW(value.get<int32_t>(), interpreter::Exception);
        EXPECT_THROW(value.get<int64_t>(), interpreter::Exception);
        EXPECT_THROW(value.get<float>(), interpreter::Exception);
        EXPECT_THROW(value.get<double>(), interpreter::Exception);

        EXPECT_EQ(5, value.get<int8_t>());

        Visitor visitor;
        value.visit(visitor);

        EXPECT_FALSE(visitor.value_bool.has_value());
        ASSERT_TRUE(visitor.value_int8_t.has_value());
        EXPECT_FALSE(visitor.value_int16_t.has_value());
        EXPECT_FALSE(visitor.value_int32_t.has_value());
        EXPECT_FALSE(visitor.value_int64_t.has_value());
        EXPECT_FALSE(visitor.value_float.has_value());
        EXPECT_FALSE(visitor.value_double.has_value());

        EXPECT_EQ(5, *visitor.value_int8_t);
    }

    {
        value = int16_t{-3};

        EXPECT_FALSE(value.isNothing());
        EXPECT_FALSE(value.is<bool>());
        EXPECT_FALSE(value.is<int8_t>());
        ASSERT_TRUE(value.is<int16_t>());
        EXPECT_FALSE(value.is<int32_t>());
        EXPECT_FALSE(value.is<int64_t>());
        EXPECT_FALSE(value.is<float>());
        EXPECT_FALSE(value.is<double>());

        EXPECT_THROW(value.get<bool>(), interpreter::Exception);
        EXPECT_THROW(value.get<int8_t>(), interpreter::Exception);
        ASSERT_NO_THROW(value.get<int16_t>());
        EXPECT_THROW(value.get<int32_t>(), interpreter::Exception);
        EXPECT_THROW(value.get<int64_t>(), interpreter::Exception);
        EXPECT_THROW(value.get<float>(), interpreter::Exception);
        EXPECT_THROW(value.get<double>(), interpreter::Exception);

        EXPECT_EQ(-3, value.get<int16_t>());

        Visitor visitor;
        value.visit(visitor);

        EXPECT_FALSE(visitor.value_bool.has_value());
        EXPECT_FALSE(visitor.value_int8_t.has_value());
        ASSERT_TRUE(visitor.value_int16_t.has_value());
        EXPECT_FALSE(visitor.value_int32_t.has_value());
        EXPECT_FALSE(visitor.value_int64_t.has_value());
        EXPECT_FALSE(visitor.value_float.has_value());
        EXPECT_FALSE(visitor.value_double.has_value());

        EXPECT_EQ(-3, *visitor.value_int16_t);
    }

    {
        value = int32_t{453};

        EXPECT_FALSE(value.isNothing());
        EXPECT_FALSE(value.is<bool>());
        EXPECT_FALSE(value.is<int8_t>());
        EXPECT_FALSE(value.is<int16_t>());
        ASSERT_TRUE(value.is<int32_t>());
        EXPECT_FALSE(value.is<int64_t>());
        EXPECT_FALSE(value.is<float>());
        EXPECT_FALSE(value.is<double>());

        EXPECT_THROW(value.get<bool>(), interpreter::Exception);
        EXPECT_THROW(value.get<int8_t>(), interpreter::Exception);
        EXPECT_THROW(value.get<int16_t>(), interpreter::Exception);
        ASSERT_NO_THROW(value.get<int32_t>());
        EXPECT_THROW(value.get<int64_t>(), interpreter::Exception);
        EXPECT_THROW(value.get<float>(), interpreter::Exception);
        EXPECT_THROW(value.get<double>(), interpreter::Exception);

        EXPECT_EQ(453, value.get<int32_t>());

        Visitor visitor;
        value.visit(visitor);

        EXPECT_FALSE(visitor.value_bool.has_value());
        EXPECT_FALSE(visitor.value_int8_t.has_value());
        EXPECT_FALSE(visitor.value_int16_t.has_value());
        ASSERT_TRUE(visitor.value_int32_t.has_value());
        EXPECT_FALSE(visitor.value_int64_t.has_value());
        EXPECT_FALSE(visitor.value_float.has_value());
        EXPECT_FALSE(visitor.value_double.has_value());

        EXPECT_EQ(453, *visitor.value_int32_t);
    }

    {
        value = int64_t{45345};

        EXPECT_FALSE(value.isNothing());
        EXPECT_FALSE(value.is<bool>());
        EXPECT_FALSE(value.is<int8_t>());
        EXPECT_FALSE(value.is<int16_t>());
        EXPECT_FALSE(value.is<int32_t>());
        ASSERT_TRUE(value.is<int64_t>());
        EXPECT_FALSE(value.is<float>());
        EXPECT_FALSE(value.is<double>());

        EXPECT_THROW(value.get<bool>(), interpreter::Exception);
        EXPECT_THROW(value.get<int8_t>(), interpreter::Exception);
        EXPECT_THROW(value.get<int16_t>(), interpreter::Exception);
        EXPECT_THROW(value.get<int32_t>(), interpreter::Exception);
        ASSERT_NO_THROW(value.get<int64_t>());
        EXPECT_THROW(value.get<float>(), interpreter::Exception);
        EXPECT_THROW(value.get<double>(), interpreter::Exception);

        EXPECT_EQ(45345, value.get<int64_t>());

        Visitor visitor;
        value.visit(visitor);

        EXPECT_FALSE(visitor.value_bool.has_value());
        EXPECT_FALSE(visitor.value_int8_t.has_value());
        EXPECT_FALSE(visitor.value_int16_t.has_value());
        EXPECT_FALSE(visitor.value_int32_t.has_value());
        ASSERT_TRUE(visitor.value_int64_t.has_value());
        EXPECT_FALSE(visitor.value_float.has_value());
        EXPECT_FALSE(visitor.value_double.has_value());

        EXPECT_EQ(45345, *visitor.value_int64_t);
    }

    {
        value = float{3.8263f};

        EXPECT_FALSE(value.isNothing());
        EXPECT_FALSE(value.is<bool>());
        EXPECT_FALSE(value.is<int8_t>());
        EXPECT_FALSE(value.is<int16_t>());
        EXPECT_FALSE(value.is<int32_t>());
        EXPECT_FALSE(value.is<int64_t>());
        ASSERT_TRUE(value.is<float>());
        EXPECT_FALSE(value.is<double>());

        EXPECT_THROW(value.get<bool>(), interpreter::Exception);
        EXPECT_THROW(value.get<int8_t>(), interpreter::Exception);
        EXPECT_THROW(value.get<int16_t>(), interpreter::Exception);
        EXPECT_THROW(value.get<int32_t>(), interpreter::Exception);
        EXPECT_THROW(value.get<int64_t>(), interpreter::Exception);
        ASSERT_NO_THROW(value.get<float>());
        EXPECT_THROW(value.get<double>(), interpreter::Exception);

        EXPECT_FLOAT_EQ(3.8263f, value.get<float>());

        Visitor visitor;
        value.visit(visitor);

        EXPECT_FALSE(visitor.value_bool.has_value());
        EXPECT_FALSE(visitor.value_int8_t.has_value());
        EXPECT_FALSE(visitor.value_int16_t.has_value());
        EXPECT_FALSE(visitor.value_int32_t.has_value());
        EXPECT_FALSE(visitor.value_int64_t.has_value());
        ASSERT_TRUE(visitor.value_float.has_value());
        EXPECT_FALSE(visitor.value_double.has_value());

        EXPECT_FLOAT_EQ(3.8263f, *visitor.value_float);
    }

    {
        value = double{382.63};

        EXPECT_FALSE(value.isNothing());
        EXPECT_FALSE(value.is<bool>());
        EXPECT_FALSE(value.is<int8_t>());
        EXPECT_FALSE(value.is<int16_t>());
        EXPECT_FALSE(value.is<int32_t>());
        EXPECT_FALSE(value.is<int64_t>());
        EXPECT_FALSE(value.is<float>());
        ASSERT_TRUE(value.is<double>());

        EXPECT_THROW(value.get<bool>(), interpreter::Exception);
        EXPECT_THROW(value.get<int8_t>(), interpreter::Exception);
        EXPECT_THROW(value.get<int16_t>(), interpreter::Exception);
        EXPECT_THROW(value.get<int32_t>(), interpreter::Exception);
        EXPECT_THROW(value.get<int64_t>(), interpreter::Exception);
        EXPECT_THROW(value.get<float>(), interpreter::Exception);
        ASSERT_NO_THROW(value.get<double>());

        EXPECT_FLOAT_EQ(382.63, value.get<double>());

        Visitor visitor;
        value.visit(visitor);

        EXPECT_FALSE(visitor.value_bool.has_value());
        EXPECT_FALSE(visitor.value_int8_t.has_value());
        EXPECT_FALSE(visitor.value_int16_t.has_value());
        EXPECT_FALSE(visitor.value_int32_t.has_value());
        EXPECT_FALSE(visitor.value_int64_t.has_value());
        EXPECT_FALSE(visitor.value_float.has_value());
        ASSERT_TRUE(visitor.value_double.has_value());

        EXPECT_FLOAT_EQ(382.63, *visitor.value_double);
    }
}

/* ************************************************************************ */
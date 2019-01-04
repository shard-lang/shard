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
#include "shard/interpreter/Interpreter.hpp"
#include "shard/ir/Constant.hpp"
#include "shard/ir/Instruction.hpp"
#include "shard/ir/Module.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::interpreter;

/* ************************************************************************* */

namespace {

/* ************************************************************************* */

template<typename T>
struct IrType;

/* ************************************************************************* */

template<>
struct IrType<int8_t>
{
    using Type = ir::TypeInt8;
};

/* ************************************************************************* */

template<>
struct IrType<int16_t>
{
    using Type = ir::TypeInt16;
};

/* ************************************************************************* */

template<>
struct IrType<int32_t>
{
    using Type = ir::TypeInt32;
};

/* ************************************************************************* */

template<>
struct IrType<int64_t>
{
    using Type = ir::TypeInt64;
};

/* ************************************************************************* */

template<>
struct IrType<float>
{
    using Type = ir::TypeFloat32;
};

/* ************************************************************************* */

template<>
struct IrType<double>
{
    using Type = ir::TypeFloat64;
};

/* ************************************************************************* */

template<typename T>
ir::Module createModule()
{
    using Type = typename IrType<T>::Type;

    ir::Module module;

    {
        auto add = module.createFunction(
            "add",
            Type::instance(),
            Vector<ViewPtr<ir::Type>>{Type::instance(), Type::instance()});

        auto block = add->createBlock();

        // Result variable
        auto result = block->template createInstruction<ir::InstructionAdd>(
            Type::instance(), add->arg(0), add->arg(1));

        // Return result
        block->template createInstruction<ir::InstructionReturn>(
            Type::instance(), result->result());
    }

    {
        auto sub = module.createFunction(
            "sub",
            Type::instance(),
            Vector<ViewPtr<ir::Type>>{Type::instance(), Type::instance()});

        auto block = sub->createBlock();

        // Result variable
        auto result = block->template createInstruction<ir::InstructionSub>(
            Type::instance(), sub->arg(0), sub->arg(1));

        // Return result
        block->template createInstruction<ir::InstructionReturn>(
            Type::instance(), result->result());
    }

    {
        auto mul = module.createFunction(
            "mul",
            Type::instance(),
            Vector<ViewPtr<ir::Type>>{Type::instance(), Type::instance()});

        auto block = mul->createBlock();

        // Result variable
        auto result = block->template createInstruction<ir::InstructionMul>(
            Type::instance(), mul->arg(0), mul->arg(1));

        // Return result
        block->template createInstruction<ir::InstructionReturn>(
            Type::instance(), result->result());
    }

    return module;
}

/* ************************************************************************* */

} // namespace

/* ************************************************************************ */

template<typename T>
struct InterpreterTest : public ::testing::Test
{
    // Nothing
};

/* ************************************************************************ */

using Types = ::testing::Types<int8_t, int16_t, int32_t, int64_t, float, double>;
TYPED_TEST_CASE(InterpreterTest, Types);

/* ************************************************************************ */

TYPED_TEST(InterpreterTest, test1)
{
    using Type = TypeParam;

    Interpreter intpr;

    // Create module
    auto module = createModule<Type>();

    // Load module
    intpr.load(module);

    // Call add function
    {
        auto res = intpr.call("add", {Type{2}, Type{5}});

        ASSERT_TRUE(res.template is<Type>());
        EXPECT_EQ(2 + 5, res.template get<Type>());
    }

    // Call sub function
    {
        auto res = intpr.call("sub", {Type{2}, Type{5}});

        ASSERT_TRUE(res.template is<Type>());
        EXPECT_EQ(2 - 5, res.template get<Type>());
    }

    // Call mul function
    {
        auto res = intpr.call("mul", {Type{3}, Type{7}});

        ASSERT_TRUE(res.template is<Type>());
        EXPECT_EQ(3 * 7, res.template get<Type>());
    }
}

/* ************************************************************************ */
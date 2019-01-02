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
#include <sstream>
#include <fstream>

// Shard
#include "shard/ir/Block.hpp"
#include "shard/ir/Instruction.hpp"
#include "shard/ir/Module.hpp"
#include "shard/ir/Serializer.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ir;

/* ************************************************************************ */

TEST(Serializer, test1)
{
    std::stringstream ss;

    {
        Module module;

        // Main function
        {
            auto main = module.createFunction("main", {});

            auto block1 = main->createBlock();
            auto alloc1 = block1->createInstruction<InstructionAlloc>(
                TypeInt8::instance());
            auto const1 = module.createConstant<ConstInt8>(1);

            block1->createInstruction<InstructionStore>(
                alloc1->result(), const1);

            auto block2 = main->createBlock();

            // Jump to block2
            block1->createInstruction<InstructionBranch>(block2);

            // Load variable
            auto load1 = block2->createInstruction<InstructionLoad>(alloc1->result());

            // Call add
            auto add1 = block2->createInstruction<InstructionCall>("add", TypeInt32::instance(), Vector<ViewPtr<Value>>{load1->result(), load1->result()});

            auto sub1 = block2->createInstruction<InstructionCall>("sub", TypeInt32::instance(), Vector<ViewPtr<Value>>{add1->result(), const1});

            block2->createInstruction<InstructionCall>("doSomething", Vector<ViewPtr<Value>>{sub1->result()});

            block2->createInstruction<InstructionReturnVoid>();
        }

        // Add function for Int32
        {
            auto add = module.createFunction(
                "add",
                TypeInt32::instance(),
                {TypeInt32::instance(), TypeInt32::instance()});

            auto block = add->createBlock();

            // Result variable
            auto result = block->createInstruction<InstructionAdd>(
                TypeInt32::instance(), add->arg(0), add->arg(1));

            // Return result
            block->createInstruction<InstructionReturn>(
                TypeInt32::instance(), result->result());
        }

        // Add function for Float32
        {
            auto add = module.createFunction(
                "add",
                TypeFloat32::instance(),
                {TypeFloat32::instance(), TypeFloat32::instance()});

            auto block = add->createBlock();

            // Result variable
            auto result = block->createInstruction<InstructionAdd>(
                TypeFloat32::instance(), add->arg(0), add->arg(1));

            // Return result
            block->createInstruction<InstructionReturn>(
                TypeFloat32::instance(), result->result());
        }

        // Sub function for Int32
        {
            auto sub = module.createFunction(
                "sub",
                TypeInt32::instance(),
                {TypeInt32::instance(), TypeInt32::instance()});

            auto block = sub->createBlock();

            // Result variable
            auto result = block->createInstruction<InstructionSub>(
                TypeInt32::instance(), sub->arg(0), sub->arg(1));

            // Return result
            block->createInstruction<InstructionReturn>(
                TypeInt32::instance(), result->result());
        }

        // mul2 function for Int32
        {
            auto mul2 = module.createFunction(
                "mul2",
                TypeInt32::instance(),
                {TypeInt32::instance()});

            auto block = mul2->createBlock();
            auto const1 = module.createConstant<ConstInt32>(2);

            // Result variable
            auto result = block->createInstruction<InstructionMul>(
                TypeInt32::instance(), mul2->arg(0), const1);

            // Return result
            block->createInstruction<InstructionReturn>(
                TypeInt32::instance(), result->result());
        }

        // Serialize
        EXPECT_NO_THROW(serialize(ss, module));
    }

    if (true)
    {
        std::ofstream file("module.bin", std::ios::out | std::ios::binary);

        file << ss.str();
    }

    {
        // Deserialize
        Module module;

        ASSERT_NO_THROW(module = deserialize(ss));

        EXPECT_EQ(5, module.functions().size());

        // Main function
        {
            auto main = module.findFunction("main", {});
            EXPECT_NE(nullptr, main);

            const auto& blocks = main->blocks();
            ASSERT_EQ(2, blocks.size());

            const auto& instrs1 = blocks[0]->instructions();
            ASSERT_EQ(3, instrs1.size());

            ASSERT_TRUE(instrs1[0]->is<InstructionAlloc>());
            ASSERT_TRUE(instrs1[1]->is<InstructionStore>());
            ASSERT_TRUE(instrs1[2]->is<InstructionBranch>());

            const auto& alloc1 = instrs1[0]->as<InstructionAlloc>();
            EXPECT_EQ(1, alloc1.count());
            EXPECT_EQ(TypeInt8::instance(), alloc1.type());

            const auto& store1 = instrs1[1]->as<InstructionStore>();
            EXPECT_EQ(alloc1.result(), store1.pointer());
            EXPECT_TRUE(store1.value()->type()->is<TypeInt8>());
            EXPECT_EQ(0, store1.index());

            const auto& branch1 = instrs1[2]->as<InstructionBranch>();
            EXPECT_EQ(blocks[1].get(), branch1.block());

            const auto& instrs2 = blocks[1]->instructions();
            ASSERT_EQ(5, instrs2.size());

            ASSERT_TRUE(instrs2[0]->is<InstructionLoad>());
            ASSERT_TRUE(instrs2[1]->is<InstructionCall>());
            ASSERT_TRUE(instrs2[2]->is<InstructionCall>());
            ASSERT_TRUE(instrs2[3]->is<InstructionCall>());
            ASSERT_TRUE(instrs2[4]->is<InstructionReturnVoid>());

            const auto& load2 = instrs2[0]->as<InstructionLoad>();
            EXPECT_EQ(0, load2.index());
            EXPECT_EQ(alloc1.result(), load2.pointer());

            const auto& call2_1 = instrs2[1]->as<InstructionCall>();
            EXPECT_EQ("add", call2_1.name());
            ASSERT_EQ(2, call2_1.arguments().size());
            EXPECT_EQ(TypeInt8::instance(), call2_1.arguments()[0]->type());
            EXPECT_EQ(TypeInt8::instance(), call2_1.arguments()[1]->type());
            EXPECT_EQ(load2.result(), call2_1.arguments()[0]);
            EXPECT_EQ(load2.result(), call2_1.arguments()[1]);

            const auto& call2_2 = instrs2[2]->as<InstructionCall>();
            EXPECT_EQ("sub", call2_2.name());
            ASSERT_EQ(2, call2_2.arguments().size());
            EXPECT_EQ(TypeInt32::instance(), call2_2.arguments()[0]->type());
            EXPECT_EQ(TypeInt8::instance(), call2_2.arguments()[1]->type());
            EXPECT_EQ(call2_1.result(), call2_2.arguments()[0]);
            EXPECT_TRUE(call2_2.arguments()[1]->isConst());

            const auto& call2_3 = instrs2[3]->as<InstructionCall>();
            EXPECT_EQ("doSomething", call2_3.name());
            ASSERT_EQ(1, call2_3.arguments().size());
            EXPECT_EQ(TypeInt32::instance(), call2_3.arguments()[0]->type());
            EXPECT_EQ(call2_2.result(), call2_3.arguments()[0]);
        }

        // Add function for Int32
        {
            auto add = module.findFunction(
                "add", {TypeInt32::instance(), TypeInt32::instance()});
            EXPECT_NE(nullptr, add);

            const auto& blocks = add->blocks();
            ASSERT_EQ(1, blocks.size());

            const auto& instrs = blocks[0]->instructions();
            ASSERT_EQ(2, instrs.size());

            ASSERT_TRUE(instrs[0]->is<InstructionAdd>());
            ASSERT_TRUE(instrs[1]->is<InstructionReturn>());

            const auto& result = instrs[0]->as<InstructionAdd>();
            EXPECT_EQ(add->arg(0), result.value1());
            EXPECT_EQ(add->arg(1), result.value2());

            const auto& ret = instrs[1]->as<InstructionReturn>();
            EXPECT_EQ(TypeInt32::instance(), ret.type());
            EXPECT_EQ(result.result(), ret.value());
        }

        // Add function for Float32
        {
            auto add = module.findFunction(
                "add", {TypeFloat32::instance(), TypeFloat32::instance()});
            EXPECT_NE(nullptr, add);

            const auto& blocks = add->blocks();
            ASSERT_EQ(1, blocks.size());

            const auto& instrs = blocks[0]->instructions();
            ASSERT_EQ(2, instrs.size());

            ASSERT_TRUE(instrs[0]->is<InstructionAdd>());
            ASSERT_TRUE(instrs[1]->is<InstructionReturn>());

            const auto& result = instrs[0]->as<InstructionAdd>();
            EXPECT_EQ(add->arg(0), result.value1());
            EXPECT_EQ(add->arg(1), result.value2());

            const auto& ret = instrs[1]->as<InstructionReturn>();
            EXPECT_EQ(TypeFloat32::instance(), ret.type());
            EXPECT_EQ(result.result(), ret.value());
        }

        // Sub function for Int32
        {
            auto sub = module.findFunction(
                "sub", {TypeInt32::instance(), TypeInt32::instance()});
            EXPECT_NE(nullptr, sub);

            const auto& blocks = sub->blocks();
            ASSERT_EQ(1, blocks.size());

            const auto& instrs = blocks[0]->instructions();
            ASSERT_EQ(2, instrs.size());

            ASSERT_TRUE(instrs[0]->is<InstructionSub>());
            ASSERT_TRUE(instrs[1]->is<InstructionReturn>());

            const auto& result = instrs[0]->as<InstructionSub>();
            EXPECT_EQ(sub->arg(0), result.value1());
            EXPECT_EQ(sub->arg(1), result.value2());

            const auto& ret = instrs[1]->as<InstructionReturn>();
            EXPECT_EQ(TypeInt32::instance(), ret.type());
            EXPECT_EQ(result.result(), ret.value());
        }

        // Mul2 function for Int32
        {
            auto mul2 = module.findFunction(
                "mul2", {TypeInt32::instance()});
            EXPECT_NE(nullptr, mul2);

            const auto& blocks = mul2->blocks();
            ASSERT_EQ(1, blocks.size());

            const auto& instrs = blocks[0]->instructions();
            ASSERT_EQ(2, instrs.size());

            ASSERT_TRUE(instrs[0]->is<InstructionMul>());
            ASSERT_TRUE(instrs[1]->is<InstructionReturn>());

            const auto& result = instrs[0]->as<InstructionMul>();
            EXPECT_EQ(mul2->arg(0), result.value1());
            EXPECT_EQ(TypeInt32::instance(), result.value2()->type());
            EXPECT_TRUE(result.value2()->isConst());

            const auto& ret = instrs[1]->as<InstructionReturn>();
            EXPECT_EQ(TypeInt32::instance(), ret.type());
            EXPECT_EQ(result.result(), ret.value());
        }
    }
}

/* ************************************************************************ */
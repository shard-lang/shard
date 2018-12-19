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
#include "shard/ir/Block.hpp"
#include "shard/ir/Constant.hpp"
#include "shard/ir/Instruction.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ir;

/* ************************************************************************ */

TEST(Instruction, Alloc)
{
    InstructionAlloc instr(TypeInt32::instance());

    EXPECT_EQ(instr.kind(), InstructionKind::Alloc);
    EXPECT_TRUE(instr.is<InstructionAlloc>());

    // Result type must be pointer
    EXPECT_TRUE(instr.resultType()->is<TypePointer>());
    EXPECT_EQ(instr.count(), 1);
    EXPECT_EQ(instr.type(), TypeInt32::instance());
}

/* ************************************************************************ */

TEST(Instruction, Load)
{
    // Allocate memory - get pointer
    InstructionAlloc pointer(TypeInt32::instance());

    // Load value from memory
    InstructionLoad instr(pointer.result());

    EXPECT_EQ(instr.kind(), InstructionKind::Load);
    EXPECT_TRUE(instr.is<InstructionLoad>());

    // Result value should be type the pointer points to
    EXPECT_EQ(instr.resultType(), TypeInt32::instance());
    EXPECT_EQ(instr.index(), 0);
    EXPECT_TRUE(instr.pointer()->type()->is<TypePointer>());
    EXPECT_EQ(
        instr.pointer()->type<TypePointer>().type(), TypeInt32::instance());
}

/* ************************************************************************ */

TEST(Instruction, Store)
{
    // Allocate memory - get pointer
    InstructionAlloc pointer(TypeInt32::instance());

    ConstInt32 value(64);

    // Store value to memory
    InstructionStore instr(pointer.result(), &value);

    EXPECT_EQ(instr.kind(), InstructionKind::Store);
    EXPECT_TRUE(instr.is<InstructionStore>());

    // Result value should be type the pointer points to
    EXPECT_EQ(instr.value(), &value);
    EXPECT_EQ(instr.index(), 0);
    EXPECT_EQ(instr.value()->type(), TypeInt32::instance());
    EXPECT_TRUE(instr.pointer()->type()->is<TypePointer>());
    EXPECT_EQ(
        instr.pointer()->type<TypePointer>().type(), TypeInt32::instance());
}

/* ************************************************************************ */

TEST(Instruction, Add)
{
    ConstInt32 value1(64);
    ConstInt32 value2(32);

    InstructionAdd instr(TypeInt32::instance(), &value1, &value2);

    EXPECT_EQ(instr.kind(), InstructionKind::Add);
    EXPECT_TRUE(instr.is<InstructionAdd>());

    EXPECT_EQ(instr.value1(), &value1);
    EXPECT_EQ(instr.value2(), &value2);
    EXPECT_EQ(instr.value1()->type(), TypeInt32::instance());
    EXPECT_EQ(instr.value2()->type(), TypeInt32::instance());
    EXPECT_EQ(instr.result()->type(), TypeInt32::instance());
    EXPECT_EQ(instr.resultType(), TypeInt32::instance());
}

/* ************************************************************************ */

TEST(Instruction, Sub)
{
    ConstInt32 value1(64);
    ConstInt32 value2(32);

    InstructionSub instr(TypeInt32::instance(), &value1, &value2);

    EXPECT_EQ(instr.kind(), InstructionKind::Sub);
    EXPECT_TRUE(instr.is<InstructionSub>());

    EXPECT_EQ(instr.value1(), &value1);
    EXPECT_EQ(instr.value2(), &value2);
    EXPECT_EQ(instr.value1()->type(), TypeInt32::instance());
    EXPECT_EQ(instr.value2()->type(), TypeInt32::instance());
    EXPECT_EQ(instr.result()->type(), TypeInt32::instance());
    EXPECT_EQ(instr.resultType(), TypeInt32::instance());
}

/* ************************************************************************ */

TEST(Instruction, Mul)
{
    ConstInt32 value1(64);
    ConstInt32 value2(32);

    InstructionMul instr(TypeInt32::instance(), &value1, &value2);

    EXPECT_EQ(instr.kind(), InstructionKind::Mul);
    EXPECT_TRUE(instr.is<InstructionMul>());

    EXPECT_EQ(instr.value1(), &value1);
    EXPECT_EQ(instr.value2(), &value2);
    EXPECT_EQ(instr.value1()->type(), TypeInt32::instance());
    EXPECT_EQ(instr.value2()->type(), TypeInt32::instance());
    EXPECT_EQ(instr.result()->type(), TypeInt32::instance());
    EXPECT_EQ(instr.resultType(), TypeInt32::instance());
}

/* ************************************************************************ */

TEST(Instruction, Div)
{
    ConstInt32 value1(64);
    ConstInt32 value2(32);

    InstructionDiv instr(TypeInt32::instance(), &value1, &value2);

    EXPECT_EQ(instr.kind(), InstructionKind::Div);
    EXPECT_TRUE(instr.is<InstructionDiv>());

    EXPECT_EQ(instr.value1(), &value1);
    EXPECT_EQ(instr.value2(), &value2);
    EXPECT_EQ(instr.value1()->type(), TypeInt32::instance());
    EXPECT_EQ(instr.value2()->type(), TypeInt32::instance());
    EXPECT_EQ(instr.result()->type(), TypeInt32::instance());
    EXPECT_EQ(instr.resultType(), TypeInt32::instance());
}

/* ************************************************************************ */

TEST(Instruction, Rem)
{
    ConstInt32 value1(64);
    ConstInt32 value2(32);

    InstructionRem instr(TypeInt32::instance(), &value1, &value2);

    EXPECT_EQ(instr.kind(), InstructionKind::Rem);
    EXPECT_TRUE(instr.is<InstructionRem>());

    EXPECT_EQ(instr.value1(), &value1);
    EXPECT_EQ(instr.value2(), &value2);
    EXPECT_EQ(instr.value1()->type(), TypeInt32::instance());
    EXPECT_EQ(instr.value2()->type(), TypeInt32::instance());
    EXPECT_EQ(instr.result()->type(), TypeInt32::instance());
    EXPECT_EQ(instr.resultType(), TypeInt32::instance());
}

/* ************************************************************************ */

TEST(Instruction, Cmp)
{
    ConstInt32 value1(64);
    ConstInt32 value2(32);

    InstructionCmp instr(
        InstructionCmp::Operation::Equal,
        TypeInt32::instance(),
        &value1,
        &value2);

    EXPECT_EQ(instr.kind(), InstructionKind::Cmp);
    EXPECT_TRUE(instr.is<InstructionCmp>());

    EXPECT_EQ(instr.operation(), InstructionCmp::Operation::Equal);
    EXPECT_EQ(instr.value1(), &value1);
    EXPECT_EQ(instr.value2(), &value2);
    EXPECT_EQ(instr.value1()->type(), TypeInt32::instance());
    EXPECT_EQ(instr.value2()->type(), TypeInt32::instance());
    EXPECT_EQ(instr.result()->type(), TypeInt32::instance());
    EXPECT_EQ(instr.resultType(), TypeInt32::instance());
}

/* ************************************************************************ */

TEST(Instruction, And)
{
    ConstInt32 value1(64);
    ConstInt32 value2(32);

    InstructionAnd instr(TypeInt32::instance(), &value1, &value2);

    EXPECT_EQ(instr.kind(), InstructionKind::And);
    EXPECT_TRUE(instr.is<InstructionAnd>());

    EXPECT_EQ(instr.value1(), &value1);
    EXPECT_EQ(instr.value2(), &value2);
    EXPECT_EQ(instr.value1()->type(), TypeInt32::instance());
    EXPECT_EQ(instr.value2()->type(), TypeInt32::instance());
    EXPECT_EQ(instr.result()->type(), TypeInt32::instance());
    EXPECT_EQ(instr.resultType(), TypeInt32::instance());
}

/* ************************************************************************ */

TEST(Instruction, Or)
{
    ConstInt32 value1(64);
    ConstInt32 value2(32);

    InstructionOr instr(TypeInt32::instance(), &value1, &value2);

    EXPECT_EQ(instr.kind(), InstructionKind::Or);
    EXPECT_TRUE(instr.is<InstructionOr>());

    EXPECT_EQ(instr.value1(), &value1);
    EXPECT_EQ(instr.value2(), &value2);
    EXPECT_EQ(instr.value1()->type(), TypeInt32::instance());
    EXPECT_EQ(instr.value2()->type(), TypeInt32::instance());
    EXPECT_EQ(instr.result()->type(), TypeInt32::instance());
    EXPECT_EQ(instr.resultType(), TypeInt32::instance());
}

/* ************************************************************************ */

TEST(Instruction, Xor)
{
    ConstInt32 value1(64);
    ConstInt32 value2(32);

    InstructionXor instr(TypeInt32::instance(), &value1, &value2);

    EXPECT_EQ(instr.kind(), InstructionKind::Xor);
    EXPECT_TRUE(instr.is<InstructionXor>());

    EXPECT_EQ(instr.value1(), &value1);
    EXPECT_EQ(instr.value2(), &value2);
    EXPECT_EQ(instr.value1()->type(), TypeInt32::instance());
    EXPECT_EQ(instr.value2()->type(), TypeInt32::instance());
    EXPECT_EQ(instr.result()->type(), TypeInt32::instance());
    EXPECT_EQ(instr.resultType(), TypeInt32::instance());
}

/* ************************************************************************ */

TEST(Instruction, Branch)
{
    Block block;
    InstructionBranch instr(&block);

    EXPECT_EQ(instr.kind(), InstructionKind::Branch);
    EXPECT_TRUE(instr.is<InstructionBranch>());

    EXPECT_EQ(instr.block(), &block);
}

/* ************************************************************************ */

TEST(Instruction, BranchCondition)
{
    ConstInt1 cond(false);

    Block block1;
    Block block2;
    InstructionBranchCondition instr(&cond, &block1, &block2);

    EXPECT_EQ(instr.kind(), InstructionKind::BranchCondition);
    EXPECT_TRUE(instr.is<InstructionBranchCondition>());

    EXPECT_EQ(instr.condition(), &cond);
    EXPECT_EQ(instr.blockTrue(), &block1);
    EXPECT_EQ(instr.blockFalse(), &block2);
}

/* ************************************************************************ */

TEST(Instruction, Call)
{
    ConstInt32 const1(15);
    ConstInt32 const2(5);

    InstructionCall instr("fn1", TypeInt32::instance(), {&const1, &const2});

    EXPECT_EQ(instr.kind(), InstructionKind::Call);
    EXPECT_TRUE(instr.is<InstructionCall>());

    EXPECT_EQ(instr.resultType(), TypeInt32::instance());
    ASSERT_EQ(instr.arguments().size(), 2);
    EXPECT_EQ(instr.arguments()[0], &const1);
    EXPECT_EQ(instr.arguments()[1], &const2);
}

/* ************************************************************************ */

TEST(Instruction, CallVoid)
{
    ConstInt32 const1(15);
    ConstInt32 const2(5);

    InstructionCall instr("fn2", {&const1, &const2});

    EXPECT_EQ(instr.kind(), InstructionKind::Call);
    EXPECT_TRUE(instr.is<InstructionCall>());

    EXPECT_EQ(instr.result(), nullptr);
    EXPECT_EQ(instr.resultType(), nullptr);
    ASSERT_EQ(instr.arguments().size(), 2);
    EXPECT_EQ(instr.arguments()[0], &const1);
    EXPECT_EQ(instr.arguments()[1], &const2);
}

/* ************************************************************************ */

TEST(Instruction, ReturnVoid)
{
    InstructionReturnVoid instr;

    EXPECT_EQ(instr.kind(), InstructionKind::ReturnVoid);
    EXPECT_TRUE(instr.is<InstructionReturnVoid>());
}

/* ************************************************************************ */

TEST(Instruction, Return)
{
    ConstInt32 value(64);

    InstructionReturn instr(TypeInt32::instance(), &value);

    EXPECT_EQ(instr.kind(), InstructionKind::Return);
    EXPECT_TRUE(instr.is<InstructionReturn>());

    EXPECT_EQ(instr.type(), TypeInt32::instance());
    EXPECT_EQ(instr.value(), &value);
}

/* ************************************************************************ */

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
#include "shard/ir/Function.hpp"
#include "shard/ir/Instruction.hpp"
#include "shard/ir/Type.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ir;

/* ************************************************************************ */

TEST(Function, Void)
{
    Function function("main", {});

    EXPECT_EQ(function.name(), "main");
    EXPECT_EQ(function.returnType(), nullptr);
    EXPECT_EQ(function.parameterTypes().size(), 0);
    ASSERT_EQ(function.arguments().size(), 0);

    auto l1 = function.createBlock();
    l1->createInstruction<InstructionReturnVoid>();

    EXPECT_EQ(l1->size(), 1);

    function.setName("main2");
    EXPECT_EQ(function.name(), "main2");
}

/* ************************************************************************ */

TEST(Function, Add)
{
    // int32 add(int32, int32)
    Function function(
        "add",
        TypeInt32::instance(),
        {TypeInt32::instance(), TypeInt32::instance()});

    EXPECT_EQ(function.name(), "add");
    EXPECT_EQ(function.returnType(), TypeInt32::instance());
    EXPECT_EQ(function.parameterTypes().size(), 2);
    ASSERT_EQ(function.arguments().size(), 2);

    auto arg1 = function.arg(0);
    auto arg2 = function.arg(1);

    EXPECT_EQ(arg1->type(), TypeInt32::instance());
    EXPECT_EQ(arg2->type(), TypeInt32::instance());

    auto l1  = function.createBlock();
    auto add = l1->createInstruction<InstructionAdd>(
        TypeInt32::instance(), arg1, arg2);
    l1->createInstruction<InstructionReturn>(
        TypeInt32::instance(), add->result());

    EXPECT_EQ(function.blocks().size(), 1);
    EXPECT_EQ(l1->size(), 2);
}

/* ************************************************************************ */

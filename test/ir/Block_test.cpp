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
#include "shard/ir/Instruction.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ir;

/* ************************************************************************ */

TEST(Block, test1)
{
    Block block;

    EXPECT_TRUE(block.instructions().empty());
    EXPECT_EQ(block.size(), 0);

    block.createInstruction<InstructionReturnVoid>();

    EXPECT_FALSE(block.instructions().empty());
    EXPECT_EQ(block.size(), 1);
    EXPECT_EQ(block.instructions().size(), 1);

    block.addInstruction(makeUnique<InstructionBranch>(&block));

    EXPECT_FALSE(block.instructions().empty());
    EXPECT_EQ(block.size(), 2);
    EXPECT_EQ(block.instructions().size(), 2);

    PtrVector<Instruction> instructions;
    instructions.push_back(makeUnique<InstructionBranch>(&block));

    block.setInstructions(std::move(instructions));

    EXPECT_FALSE(block.instructions().empty());
    EXPECT_EQ(block.size(), 1);
    EXPECT_EQ(block.instructions().size(), 1);
}

/* ************************************************************************ */
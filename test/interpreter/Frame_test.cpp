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
#include "shard/interpreter/Frame.hpp"
#include "shard/ir/Constant.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::interpreter;

/* ************************************************************************ */

TEST(Frame, test1)
{
    Frame frame;

    frame.result() = int32_t{5};
    EXPECT_EQ(5, frame.result().get<int32_t>());

    ir::ConstInt32 val1{3};

    // Store value
    frame.value(val1) = val1.value();
    EXPECT_EQ(3, frame.value(val1).get<int32_t>());
}

/* ************************************************************************ */
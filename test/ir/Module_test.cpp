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
#include "shard/ir/Module.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ir;

/* ************************************************************************ */

TEST(Module, test1)
{
    Module module;

    EXPECT_TRUE(module.functions().empty());
    EXPECT_EQ(module.functions().size(), 0);

    auto fn1 = module.createFunction("main", {});

    EXPECT_FALSE(module.functions().empty());
    ASSERT_EQ(module.functions().size(), 1);

    EXPECT_EQ(module.functions()[0].get(), fn1);

    auto fn2 = module.createFunction(
        "add",
        TypeInt32::instance(),
        {TypeInt32::instance(), TypeInt32::instance()});

    EXPECT_FALSE(module.functions().empty());
    ASSERT_EQ(module.functions().size(), 2);

    EXPECT_EQ(module.functions()[0].get(), fn1);
    EXPECT_EQ(module.functions()[1].get(), fn2);

    PtrVector<Function> functions;
    functions.push_back(makeUnique<Function>(
        "sub",
        TypeInt8::instance(),
        Vector<ViewPtr<Type>>{TypeInt8::instance(), TypeInt8::instance()}));
    module.setFunctions(std::move(functions));

    EXPECT_FALSE(module.functions().empty());
    ASSERT_EQ(module.functions().size(), 1);

    EXPECT_EQ(module.functions()[0]->name(), "sub");
}

/* ************************************************************************ */
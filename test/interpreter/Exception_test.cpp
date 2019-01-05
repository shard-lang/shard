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
#include "shard/UniquePtr.hpp"
#include "shard/interpreter/Exception.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::interpreter;

/* ************************************************************************ */

TEST(Exception, test1)
{
    interpreter::Exception except("Error");
    EXPECT_STREQ("Error", except.what());

    // Test virtual destructor
    auto ptr = makeUnique<interpreter::Exception>("Message");

    EXPECT_STREQ("Message", ptr->what());
}

/* ************************************************************************ */
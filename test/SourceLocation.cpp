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

// CeCe
#include "shard/SourceLocation.hpp"

/* ************************************************************************ */

using namespace shard;

/* ************************************************************************ */

TEST(SourceLocationTest, constructor)
{
    SourceLocation loc1;
    SourceLocation loc2(100, 1000);

    EXPECT_EQ(0, loc1.getLine());
    EXPECT_EQ(0, loc1.getColumn());

    EXPECT_EQ(100, loc2.getLine());
    EXPECT_EQ(1000, loc2.getColumn());
}

/* ************************************************************************ */
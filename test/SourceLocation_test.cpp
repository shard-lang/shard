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
#include "shard/SourceLocation.hpp"

/* ************************************************************************ */

using namespace shard;

/* ************************************************************************ */

::std::ostream& operator<<(::std::ostream& os, const shard::SourceLocation& loc)
{
    return os << loc.line() << ":" << loc.column();
}

/* ************************************************************************ */

TEST(SourceLocationTest, constructor)
{
    SourceLocation loc1;
    SourceLocation loc2(100, 1000);

    EXPECT_EQ(0, loc1.line());
    EXPECT_EQ(0, loc1.column());

    EXPECT_EQ(100, loc2.line());
    EXPECT_EQ(1000, loc2.column());
}

/* ************************************************************************ */

TEST(SourceLocationTest, boolean)
{
    SourceLocation loc1;
    SourceLocation loc2{100, 1000};
    SourceLocation loc3{0, 50};
    SourceLocation loc4{10, 0};

    EXPECT_FALSE(loc1);
    EXPECT_TRUE(loc2);
    EXPECT_FALSE(loc3);
    EXPECT_FALSE(loc4);
}

/* ************************************************************************ */

TEST(SourceLocationTest, relationalOperators)
{
    SourceLocation loc1;
    SourceLocation loc2{100, 1000};
    SourceLocation loc3{100, 1000};
    SourceLocation loc4{100, 456};
    SourceLocation loc5{32, 456};

    EXPECT_EQ(loc1, loc1);
    EXPECT_EQ(loc2, loc2);
    EXPECT_EQ(loc3, loc3);
    EXPECT_EQ(loc4, loc4);
    EXPECT_EQ(loc5, loc5);

    EXPECT_NE(loc1, loc2);
    EXPECT_NE(loc1, loc3);
    EXPECT_NE(loc1, loc4);
    EXPECT_NE(loc1, loc5);

    EXPECT_NE(loc2, loc1);
    EXPECT_EQ(loc2, loc3);
    EXPECT_NE(loc2, loc4);
    EXPECT_NE(loc2, loc5);

    EXPECT_NE(loc3, loc1);
    EXPECT_EQ(loc3, loc2);
    EXPECT_NE(loc3, loc4);
    EXPECT_NE(loc3, loc5);

    EXPECT_NE(loc4, loc1);
    EXPECT_NE(loc4, loc2);
    EXPECT_NE(loc4, loc3);
    EXPECT_NE(loc4, loc5);

    EXPECT_NE(loc5, loc1);
    EXPECT_NE(loc5, loc2);
    EXPECT_NE(loc5, loc3);
    EXPECT_NE(loc5, loc4);

    EXPECT_LE(loc2, loc3);
    EXPECT_LE(loc4, loc2);
    EXPECT_LE(loc5, loc4);

    EXPECT_LT(loc4, loc2);
    EXPECT_LT(loc5, loc4);

    EXPECT_GE(loc2, loc3);
    EXPECT_GE(loc2, loc4);
    EXPECT_GE(loc3, loc5);

    EXPECT_GT(loc2, loc4);
    EXPECT_GT(loc3, loc5);
}

/* ************************************************************************ */
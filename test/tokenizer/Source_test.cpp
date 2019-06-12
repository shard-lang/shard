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

// Google test
#include "gtest/gtest.h"

// C++
#include <stdexcept>

// Shard
#include "shard/String.hpp"
#include "shard/tokenizer/Source.hpp"

/* ************************************************************************* */

using namespace shard;
using namespace shard::tokenizer;

/* ************************************************************************* */

TEST(Source, basic)
{
    const String src = "Hello World!\n";

    auto source = Source(src);

    EXPECT_EQ(source.filename(), "<input>");
    EXPECT_EQ(source.size(), src.length());

    // Must be same
    EXPECT_EQ(source.source(), src);

    // Index checking
    EXPECT_EQ(source.at(0), 'H');
    EXPECT_EQ(source.at(1), 'e');
    EXPECT_EQ(source.at(2), 'l');
    EXPECT_EQ(source.at(3), 'l');
    EXPECT_EQ(source.at(4), 'o');
    EXPECT_EQ(source.at(5), ' ');
    EXPECT_EQ(source.at(6), 'W');
    EXPECT_EQ(source.at(7), 'o');
    EXPECT_EQ(source.at(8), 'r');
    EXPECT_EQ(source.at(9), 'l');
    EXPECT_EQ(source.at(10), 'd');
    EXPECT_EQ(source.at(11), '!');
    EXPECT_EQ(source.at(12), '\n');
    EXPECT_THROW(source.at(13), std::out_of_range);

    EXPECT_EQ(source[0], 'H');
    EXPECT_EQ(source[1], 'e');
    EXPECT_EQ(source[2], 'l');
    EXPECT_EQ(source[3], 'l');
    EXPECT_EQ(source[4], 'o');
    EXPECT_EQ(source[5], ' ');
    EXPECT_EQ(source[6], 'W');
    EXPECT_EQ(source[7], 'o');
    EXPECT_EQ(source[8], 'r');
    EXPECT_EQ(source[9], 'l');
    EXPECT_EQ(source[10], 'd');
    EXPECT_EQ(source[11], '!');
    EXPECT_EQ(source[12], '\n');
    EXPECT_EQ(source[13], '\0');
}

/* ************************************************************************* */

TEST(Source, eol)
{
    auto source = Source("Line1\n  Line2\r\n    Line3\n");

    // Must be same
    EXPECT_EQ(source.source(), "Line1\n  Line2\n    Line3\n");
}

/* ************************************************************************* */

TEST(Source, iterators)
{
    auto source = Source("Hello World!\n");

    // Copy source
    String src;
    src.reserve(source.size());
    std::copy(source.begin(), source.end(), std::back_inserter(src));

    EXPECT_EQ(src, "Hello World!\n");
}

/* ************************************************************************* */

TEST(Source, locations)
{
    auto source = Source("Line1\n  Line2\r\n    Line3\n");

    const auto loc1 = source.location(0);
    EXPECT_EQ(loc1.line(), 1);
    EXPECT_EQ(loc1.column(), 1);

    const auto loc2 = source.location(5);
    EXPECT_EQ(loc2.line(), 1);
    EXPECT_EQ(loc2.column(), 6);

    const auto loc3 = source.location(6);
    EXPECT_EQ(loc3.line(), 2);
    EXPECT_EQ(loc3.column(), 1);

    const auto loc4 = source.location(8);
    EXPECT_EQ(loc4.line(), 2);
    EXPECT_EQ(loc4.column(), 3);
}

/* ************************************************************************* */

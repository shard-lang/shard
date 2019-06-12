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

// Shard
#include "shard/UniquePtr.hpp"
#include "shard/parser/exceptions.hpp"

/* ************************************************************************* */

using namespace shard;
using namespace shard::parser;

/* ************************************************************************* */

TEST(exceptions, ParseError)
{
    ParseError error("failed", SourceLocation{1, 1});

    EXPECT_STREQ(error.what(), "1:1: failed");
    EXPECT_EQ(error.location(), (SourceLocation{1, 1}));

    auto errPtr = makeUnique<ParseError>("error", SourceLocation{5, 8});

    EXPECT_STREQ(errPtr->what(), "5:8: error");
    EXPECT_EQ(errPtr->location(), (SourceLocation{5, 8}));
}

/* ************************************************************************* */

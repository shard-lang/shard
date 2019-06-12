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
#include "shard/tokenizer/Source.hpp"
#include "shard/tokenizer/SourceIterator.hpp"

/* ************************************************************************* */

using namespace shard;
using namespace shard::tokenizer;

/* ************************************************************************* */

namespace shard {

/* ************************************************************************* */

inline std::ostream& operator<<(std::ostream& os, const SourceLocation& loc)
{
    return os << loc.line() << ":" << loc.column();
}

/* ************************************************************************* */

} // namespace shard

/* ************************************************************************* */

TEST(SourceIterator, def)
{
    SourceIterator it;
    EXPECT_FALSE(it.hasSource());
}

/* ************************************************************************* */

TEST(SourceIterator, basic)
{
    auto source = Source("Hello\r\nWorld!");

    auto it  = source.begin();
    auto end = source.end();

    ASSERT_TRUE(it.hasSource());
    ASSERT_TRUE(end.hasSource());
    EXPECT_EQ(&it.source(), &source);
    EXPECT_EQ(&end.source(), &source);

    ASSERT_NE(it, end);
    EXPECT_EQ(*it, 'H');
    EXPECT_EQ(it.location(), (SourceLocation{1, 1}));

    auto it2 = it++;
    ASSERT_NE(it2, end);
    ASSERT_NE(it2, it);
    ASSERT_EQ(it2, source.begin());

    ASSERT_NE(it, end);
    EXPECT_EQ(*it, 'e');
    EXPECT_EQ(it.location(), (SourceLocation{1, 2}));

    ++it;
    ASSERT_NE(it, end);
    EXPECT_EQ(*it, 'l');
    EXPECT_EQ(it.location(), (SourceLocation{1, 3}));

    ++it;
    ASSERT_NE(it, end);
    EXPECT_EQ(*it, 'l');
    EXPECT_EQ(it.location(), (SourceLocation{1, 4}));

    ++it;
    ASSERT_NE(it, end);
    EXPECT_EQ(*it, 'o');
    EXPECT_EQ(it.location(), (SourceLocation{1, 5}));

    ++it;
    ASSERT_NE(it, end);
    EXPECT_EQ(*it, '\n');
    EXPECT_EQ(it.location(), (SourceLocation{1, 6}));

    ++it;
    ASSERT_NE(it, end);
    EXPECT_EQ(*it, 'W');
    EXPECT_EQ(it.location(), (SourceLocation{2, 1}));

    ++it;
    ASSERT_NE(it, end);
    EXPECT_EQ(*it, 'o');
    EXPECT_EQ(it.location(), (SourceLocation{2, 2}));

    ++it;
    ASSERT_NE(it, end);
    EXPECT_EQ(*it, 'r');
    EXPECT_EQ(it.location(), (SourceLocation{2, 3}));

    ++it;
    ASSERT_NE(it, end);
    EXPECT_EQ(*it, 'l');
    EXPECT_EQ(it.location(), (SourceLocation{2, 4}));

    ++it;
    ASSERT_NE(it, end);
    EXPECT_EQ(*it, 'd');
    EXPECT_EQ(it.location(), (SourceLocation{2, 5}));

    ++it;
    ASSERT_NE(it, end);
    EXPECT_EQ(*it, '!');
    EXPECT_EQ(it.location(), (SourceLocation{2, 6}));

    ++it;
    ASSERT_EQ(it, end);
}

/* ************************************************************************* */

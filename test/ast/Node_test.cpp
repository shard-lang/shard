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
#include "shard/ast/Node.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

namespace {

/* ************************************************************************ */

struct TestNode : public Node
{
    constexpr TestNode(SourceRange range) noexcept
        : Node(range) {}
};

/* ************************************************************************ */

}

/* ************************************************************************ */

TEST(Node, basic)
{
    TestNode node{{SourceLocation{0, 0}, SourceLocation{10, 0}}};

    EXPECT_EQ(node.sourceRange().start(), (SourceLocation{0, 0}));
    EXPECT_EQ(node.sourceRange().end(), (SourceLocation{10, 0}));
}

/* ************************************************************************ */
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
#include "shard/ast/expr/IdentifierExpr.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

TEST(IdentifierExpr, base)
{
    {
        // id
        const IdentifierExpr expr("id");

        EXPECT_TRUE(expr.is<IdentifierExpr>());
        ASSERT_FALSE(expr.name().empty());
        EXPECT_EQ("id", expr.name());
    }

#if !defined(NDEBUG) && !defined(_WIN32)
    {
        // empty
        EXPECT_EXIT({ const IdentifierExpr expr(""); }, ::testing::KilledBySignal(SIGABRT), ".*");
    }
#endif

    {
        // id
        IdentifierExpr expr("id");

        EXPECT_TRUE(expr.is<IdentifierExpr>());
        ASSERT_FALSE(expr.name().empty());
        EXPECT_EQ("id", expr.name());

        expr.setName("my_id");
        EXPECT_EQ("my_id", expr.name());
    }

    {
        // id
        const auto expr = IdentifierExpr::make("id");
        ASSERT_NE(nullptr, expr);

        EXPECT_TRUE(expr->is<IdentifierExpr>());
        ASSERT_FALSE(expr->name().empty());
        EXPECT_EQ("id", expr->name());
    }
}

/* ************************************************************************ */
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
#include "shard/ast/stmt/ReturnStmt.hpp"
#include "shard/ast/expr/BoolLiteralExpr.hpp"
#include "shard/ast/expr/FloatLiteralExpr.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

TEST(ReturnStmt, base)
{
    {
        // return;
        const ReturnStmt stmt;

        EXPECT_TRUE(stmt.is<ReturnStmt>());
        ASSERT_EQ(nullptr, stmt.resExpr());
    }

    {
        // return true;
        const ReturnStmt stmt(BoolLiteralExpr::make(true));

        EXPECT_TRUE(stmt.is<ReturnStmt>());
        ASSERT_NE(nullptr, stmt.resExpr());
        EXPECT_TRUE(stmt.resExpr()->is<BoolLiteralExpr>());
    }


    {
        // return;
        ReturnStmt stmt;

        EXPECT_TRUE(stmt.is<ReturnStmt>());
        ASSERT_EQ(nullptr, stmt.resExpr());

        // return 1.1;
        stmt.setResExpr(FloatLiteralExpr::make(1.1));

        ASSERT_NE(nullptr, stmt.resExpr());
        EXPECT_TRUE(stmt.resExpr()->is<FloatLiteralExpr>());
    }

    {
        // return;
        const auto stmt = ReturnStmt::make(nullptr);

        EXPECT_TRUE(stmt->is<ReturnStmt>());
        ASSERT_EQ(nullptr, stmt->resExpr());
    }

}

/* ************************************************************************ */

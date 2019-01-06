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
#include "shard/ast/stmt/IfStmt.hpp"
#include "shard/ast/stmt/CompoundStmt.hpp"
#include "shard/ast/stmt/ExprStmt.hpp"
#include "shard/ast/stmt/ReturnStmt.hpp"
#include "shard/ast/expr/BoolLiteralExpr.hpp"
#include "shard/ast/expr/IntLiteralExpr.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

TEST(IfStmt, base)
{
    {
        // if (true) {}
        const IfStmt stmt(BoolLiteralExpr::make(true), CompoundStmt::make({}));

        EXPECT_TRUE(stmt.is<IfStmt>());
        ASSERT_NE(nullptr, stmt.condExpr());
        EXPECT_TRUE(stmt.condExpr()->is<BoolLiteralExpr>());
        ASSERT_NE(nullptr, stmt.thenStmt());
        EXPECT_TRUE(stmt.thenStmt()->is<CompoundStmt>());
        EXPECT_EQ(nullptr, stmt.elseStmt());
    }

    {
        // if (true) {} else ;
        const IfStmt stmt(BoolLiteralExpr::make(true), CompoundStmt::make({}), ExprStmt::make(nullptr));

        EXPECT_TRUE(stmt.is<IfStmt>());
        ASSERT_NE(nullptr, stmt.condExpr());
        EXPECT_TRUE(stmt.condExpr()->is<BoolLiteralExpr>());
        ASSERT_NE(nullptr, stmt.thenStmt());
        EXPECT_TRUE(stmt.thenStmt()->is<CompoundStmt>());
        ASSERT_NE(nullptr, stmt.elseStmt());
        EXPECT_TRUE(stmt.elseStmt()->is<ExprStmt>());
    }

    {
        // if (true) {} else ;
        IfStmt stmt(BoolLiteralExpr::make(true), CompoundStmt::make({}), ExprStmt::make(nullptr));

        EXPECT_TRUE(stmt.is<IfStmt>());
        ASSERT_NE(nullptr, stmt.condExpr());
        EXPECT_TRUE(stmt.condExpr()->is<BoolLiteralExpr>());
        ASSERT_NE(nullptr, stmt.thenStmt());
        EXPECT_TRUE(stmt.thenStmt()->is<CompoundStmt>());
        ASSERT_NE(nullptr, stmt.elseStmt());
        EXPECT_TRUE(stmt.elseStmt()->is<ExprStmt>());

        // if (1) return;
        stmt.setCondExpr(IntLiteralExpr::make(1));
        stmt.setThenStmt(ReturnStmt::make());
        stmt.setElseStmt(nullptr);

        ASSERT_NE(nullptr, stmt.condExpr());
        EXPECT_TRUE(stmt.condExpr()->is<IntLiteralExpr>());
        ASSERT_NE(nullptr, stmt.thenStmt());
        EXPECT_TRUE(stmt.thenStmt()->is<ReturnStmt>());
        ASSERT_EQ(nullptr, stmt.elseStmt());
    }

    {
        // if (true) {}
        const auto stmt = IfStmt::make(BoolLiteralExpr::make(true), CompoundStmt::make({}), nullptr);

        EXPECT_TRUE(stmt->is<IfStmt>());
        ASSERT_NE(nullptr, stmt->condExpr());
        EXPECT_TRUE(stmt->condExpr()->is<BoolLiteralExpr>());
        ASSERT_NE(nullptr, stmt->thenStmt());
        EXPECT_TRUE(stmt->thenStmt()->is<CompoundStmt>());
        EXPECT_EQ(nullptr, stmt->elseStmt());
    }
}

/* ************************************************************************ */

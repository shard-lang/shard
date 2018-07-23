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
#include "shard/ast/stmt/WhileStmt.hpp"
#include "shard/ast/stmt/ExprStmt.hpp"
#include "shard/ast/stmt/ContinueStmt.hpp"
#include "shard/ast/expr/BoolLiteralExpr.hpp"
#include "shard/ast/expr/IntLiteralExpr.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

TEST(WhileStmt, base)
{
    {
        // while (true);
        const WhileStmt stmt(BoolLiteralExpr::make(true), ExprStmt::make(nullptr));

        EXPECT_EQ(StmtKind::While, stmt.getKind());
        EXPECT_TRUE(stmt.is<WhileStmt>());
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(stmt.getCondExpr()->is<BoolLiteralExpr>());
        ASSERT_NE(nullptr, stmt.getBodyStmt());
        EXPECT_TRUE(stmt.getBodyStmt()->is<ExprStmt>());
    }

    {
        // while (true);
        WhileStmt stmt(BoolLiteralExpr::make(true), ExprStmt::make(nullptr));

        EXPECT_EQ(StmtKind::While, stmt.getKind());
        EXPECT_TRUE(stmt.is<WhileStmt>());
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(stmt.getCondExpr()->is<BoolLiteralExpr>());
        ASSERT_NE(nullptr, stmt.getBodyStmt());
        EXPECT_TRUE(stmt.getBodyStmt()->is<ExprStmt>());

        // while (1) continue;
        stmt.setCondExpr(IntLiteralExpr::make(1));
        stmt.setBodyStmt(ContinueStmt::make());

        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(stmt.getCondExpr()->is<IntLiteralExpr>());
        ASSERT_NE(nullptr, stmt.getBodyStmt());
        EXPECT_TRUE(stmt.getBodyStmt()->is<ContinueStmt>());
    }

    {
        // while (true);
        const auto stmt = WhileStmt::make(BoolLiteralExpr::make(true), ExprStmt::make(nullptr));

        EXPECT_EQ(StmtKind::While, stmt->getKind());
        EXPECT_TRUE(stmt->is<WhileStmt>());
        ASSERT_NE(nullptr, stmt->getCondExpr());
        EXPECT_TRUE(stmt->getCondExpr()->is<BoolLiteralExpr>());
        ASSERT_NE(nullptr, stmt->getBodyStmt());
        EXPECT_TRUE(stmt->getBodyStmt()->is<ExprStmt>());
    }
}

/* ************************************************************************ */

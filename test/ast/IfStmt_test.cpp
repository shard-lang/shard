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
#include "shard/ast/Stmt.hpp"
#include "shard/ast/Expr.hpp"
#include "shard/ast/Decl.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

TEST(IfStmt, base)
{
    {
        // if (true) {}
        const IfStmt stmt(BoolLiteralExpr::make(true), CompoundStmt::make());

        EXPECT_EQ(StmtKind::If, stmt.getKind());
        EXPECT_TRUE(stmt.is<IfStmt>());
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(stmt.getCondExpr()->is<BoolLiteralExpr>());
        ASSERT_NE(nullptr, stmt.getThenStmt());
        EXPECT_TRUE(stmt.getThenStmt()->is<CompoundStmt>());
        EXPECT_EQ(nullptr, stmt.getElseStmt());
    }

    {
        // if (true) {} else ;
        const IfStmt stmt(BoolLiteralExpr::make(true), CompoundStmt::make(), ExprStmt::make());

        EXPECT_EQ(StmtKind::If, stmt.getKind());
        EXPECT_TRUE(stmt.is<IfStmt>());
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(stmt.getCondExpr()->is<BoolLiteralExpr>());
        ASSERT_NE(nullptr, stmt.getThenStmt());
        EXPECT_TRUE(stmt.getThenStmt()->is<CompoundStmt>());
        ASSERT_NE(nullptr, stmt.getElseStmt());
        EXPECT_TRUE(stmt.getElseStmt()->is<ExprStmt>());
    }

    {
        // if (true) {} else ;
        IfStmt stmt(BoolLiteralExpr::make(true), CompoundStmt::make(), ExprStmt::make());

        EXPECT_EQ(StmtKind::If, stmt.getKind());
        EXPECT_TRUE(stmt.is<IfStmt>());
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(stmt.getCondExpr()->is<BoolLiteralExpr>());
        ASSERT_NE(nullptr, stmt.getThenStmt());
        EXPECT_TRUE(stmt.getThenStmt()->is<CompoundStmt>());
        ASSERT_NE(nullptr, stmt.getElseStmt());
        EXPECT_TRUE(stmt.getElseStmt()->is<ExprStmt>());

        // if (1) return;
        stmt.setCondExpr(IntLiteralExpr::make(1));
        stmt.setThenStmt(ReturnStmt::make());
        stmt.setElseStmt(nullptr);

        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(stmt.getCondExpr()->is<IntLiteralExpr>());
        ASSERT_NE(nullptr, stmt.getThenStmt());
        EXPECT_TRUE(stmt.getThenStmt()->is<ReturnStmt>());
        ASSERT_EQ(nullptr, stmt.getElseStmt());
    }

    {
        // if (true) {}
        const auto stmt = IfStmt::make(BoolLiteralExpr::make(true), CompoundStmt::make());

        EXPECT_EQ(StmtKind::If, stmt->getKind());
        EXPECT_TRUE(stmt->is<IfStmt>());
        ASSERT_NE(nullptr, stmt->getCondExpr());
        EXPECT_TRUE(stmt->getCondExpr()->is<BoolLiteralExpr>());
        ASSERT_NE(nullptr, stmt->getThenStmt());
        EXPECT_TRUE(stmt->getThenStmt()->is<CompoundStmt>());
        EXPECT_EQ(nullptr, stmt->getElseStmt());
    }
}

/* ************************************************************************ */

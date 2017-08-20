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

TEST(ForStmt, base)
{
    {
        // for (; true; ) {}
        const ForStmt stmt(ExprStmt::make(), BoolLiteralExpr::make(true), nullptr, CompoundStmt::make());

        EXPECT_EQ(StmtKind::For, stmt.getKind());
        EXPECT_TRUE(stmt.is<ForStmt>());
        ASSERT_NE(nullptr, stmt.getInitStmt());
        EXPECT_TRUE(stmt.getInitStmt()->is<ExprStmt>());
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(stmt.getCondExpr()->is<BoolLiteralExpr>());
        EXPECT_EQ(nullptr, stmt.getIncExpr());
        ASSERT_NE(nullptr, stmt.getBodyStmt());
        EXPECT_TRUE(stmt.getBodyStmt()->is<CompoundStmt>());
    }

    {
        // for (; true; 5) {}
        const ForStmt stmt(ExprStmt::make(), BoolLiteralExpr::make(true), IntLiteralExpr::make(5), CompoundStmt::make());

        EXPECT_EQ(StmtKind::For, stmt.getKind());
        EXPECT_TRUE(stmt.is<ForStmt>());
        ASSERT_NE(nullptr, stmt.getInitStmt());
        EXPECT_TRUE(stmt.getInitStmt()->is<ExprStmt>());
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(stmt.getCondExpr()->is<BoolLiteralExpr>());
        ASSERT_NE(nullptr, stmt.getIncExpr());
        EXPECT_TRUE(stmt.getIncExpr()->is<IntLiteralExpr>());
        ASSERT_NE(nullptr, stmt.getBodyStmt());
        EXPECT_TRUE(stmt.getBodyStmt()->is<CompoundStmt>());
    }

    {
        // for (; true; 5) {}
        ForStmt stmt(ExprStmt::make(), BoolLiteralExpr::make(true), IntLiteralExpr::make(5), CompoundStmt::make());

        EXPECT_EQ(StmtKind::For, stmt.getKind());
        EXPECT_TRUE(stmt.is<ForStmt>());
        ASSERT_NE(nullptr, stmt.getInitStmt());
        EXPECT_TRUE(stmt.getInitStmt()->is<ExprStmt>());
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(stmt.getCondExpr()->is<BoolLiteralExpr>());
        ASSERT_NE(nullptr, stmt.getIncExpr());
        EXPECT_TRUE(stmt.getIncExpr()->is<IntLiteralExpr>());
        ASSERT_NE(nullptr, stmt.getBodyStmt());
        EXPECT_TRUE(stmt.getBodyStmt()->is<CompoundStmt>());

        // for (int i; 1; 2) continue
        stmt.setInitStmt(DeclStmt::make(VariableDecl::make(TypeKind::Int, "i")));
        stmt.setCondExpr(IntLiteralExpr::make(1));
        stmt.setIncExpr(IntLiteralExpr::make(2));
        stmt.setBodyStmt(ContinueStmt::make());

        ASSERT_NE(nullptr, stmt.getInitStmt());
        EXPECT_TRUE(stmt.getInitStmt()->is<DeclStmt>());
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(stmt.getCondExpr()->is<IntLiteralExpr>());
        ASSERT_NE(nullptr, stmt.getIncExpr());
        EXPECT_TRUE(stmt.getIncExpr()->is<IntLiteralExpr>());
        ASSERT_NE(nullptr, stmt.getBodyStmt());
        EXPECT_TRUE(stmt.getBodyStmt()->is<ContinueStmt>());
    }

    {
        // for (; true; ) {}
        const auto stmt = ForStmt::make(ExprStmt::make(), BoolLiteralExpr::make(true), nullptr, CompoundStmt::make());

        EXPECT_EQ(StmtKind::For, stmt->getKind());
        EXPECT_TRUE(stmt->is<ForStmt>());
        ASSERT_NE(nullptr, stmt->getInitStmt());
        EXPECT_TRUE(stmt->getInitStmt()->is<ExprStmt>());
        ASSERT_NE(nullptr, stmt->getCondExpr());
        EXPECT_TRUE(stmt->getCondExpr()->is<BoolLiteralExpr>());
        EXPECT_EQ(nullptr, stmt->getIncExpr());
        ASSERT_NE(nullptr, stmt->getBodyStmt());
        EXPECT_TRUE(stmt->getBodyStmt()->is<CompoundStmt>());
    }
}

/* ************************************************************************ */

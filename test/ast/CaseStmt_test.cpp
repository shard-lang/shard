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

TEST(CaseStmt, base)
{
    {
        // case 0: ;
        CaseStmt stmt(IntLiteralExpr::make(0));

        stmt.addStmt(ExprStmt::make());

        EXPECT_EQ(StmtKind::Case, stmt.getKind());
        EXPECT_TRUE(stmt.is<CaseStmt>());
        ASSERT_NE(nullptr, stmt.getExpr());
        EXPECT_TRUE(stmt.getExpr()->is<IntLiteralExpr>());
        ASSERT_FALSE(stmt.getStmts().empty());
    }

    {
        // case 0: ;
        CaseStmt stmt(IntLiteralExpr::make(0));

        stmt.addStmt(ExprStmt::make());

        EXPECT_EQ(StmtKind::Case, stmt.getKind());
        EXPECT_TRUE(stmt.is<CaseStmt>());
        ASSERT_NE(nullptr, stmt.getExpr());
        EXPECT_TRUE(stmt.getExpr()->is<IntLiteralExpr>());
        ASSERT_FALSE(stmt.getStmts().empty());

        // case "val": break;
        stmt.setExpr(StringLiteralExpr::make("val"));
        stmt.addStmt(BreakStmt::make());

        ASSERT_NE(nullptr, stmt.getExpr());
        EXPECT_TRUE(stmt.getExpr()->is<StringLiteralExpr>());
        ASSERT_FALSE(stmt.getStmts().empty());
        EXPECT_EQ(2, stmt.getStmts().size());
    }

    {
        // case 0:
        CaseStmt stmt(IntLiteralExpr::make(0));

        EXPECT_EQ(StmtKind::Case, stmt.getKind());
        EXPECT_TRUE(stmt.is<CaseStmt>());
        ASSERT_NE(nullptr, stmt.getExpr());
        EXPECT_TRUE(stmt.getExpr()->is<IntLiteralExpr>());
        ASSERT_TRUE(stmt.getStmts().empty());

        PtrDynamicArray<Stmt> stmts;
        stmts.push_back(ExprStmt::make());

        // case 0: ;
        stmt.setStmts(moveValue(stmts));

        EXPECT_EQ(StmtKind::Case, stmt.getKind());
        EXPECT_TRUE(stmt.is<CaseStmt>());
        ASSERT_NE(nullptr, stmt.getExpr());
        EXPECT_TRUE(stmt.getExpr()->is<IntLiteralExpr>());
        ASSERT_FALSE(stmt.getStmts().empty());
        ASSERT_EQ(1, stmt.getStmts().size());
    }

    {
        // case 0: ;
        const auto stmt = CaseStmt::make(IntLiteralExpr::make(0));

        EXPECT_EQ(StmtKind::Case, stmt->getKind());
        EXPECT_TRUE(stmt->is<CaseStmt>());
        ASSERT_NE(nullptr, stmt->getExpr());
        EXPECT_TRUE(stmt->getExpr()->is<IntLiteralExpr>());
        ASSERT_TRUE(stmt->getStmts().empty());
    }
}

/* ************************************************************************ */

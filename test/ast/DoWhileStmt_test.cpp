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

TEST(DoWhileStmt, base)
{
    {
        // do {} while (true);
        const DoWhileStmt stmt(BoolLiteralExpr::make(true), CompoundStmt::make());

        EXPECT_EQ(StmtKind::DoWhile, stmt.getKind());
        EXPECT_TRUE(stmt.is<DoWhileStmt>());
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(stmt.getCondExpr()->is<BoolLiteralExpr>());
        ASSERT_NE(nullptr, stmt.getBodyStmt());
        EXPECT_TRUE(stmt.getBodyStmt()->is<CompoundStmt>());
    }

    {
        // do {} while (true);
        DoWhileStmt stmt(BoolLiteralExpr::make(true), CompoundStmt::make());

        EXPECT_EQ(StmtKind::DoWhile, stmt.getKind());
        EXPECT_TRUE(stmt.is<DoWhileStmt>());
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(stmt.getCondExpr()->is<BoolLiteralExpr>());
        ASSERT_NE(nullptr, stmt.getBodyStmt());
        EXPECT_TRUE(stmt.getBodyStmt()->is<CompoundStmt>());

        // do { break; } while (false);
        stmt.setCondExpr(BoolLiteralExpr::make(false));

        auto body = CompoundStmt::make();
        body->addStmt(BreakStmt::make());

        stmt.setBodyStmt(moveValue(body));

        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(stmt.getCondExpr()->is<BoolLiteralExpr>());
        EXPECT_FALSE(stmt.getCondExpr()->cast<BoolLiteralExpr>().getValue());
        ASSERT_NE(nullptr, stmt.getBodyStmt());
        EXPECT_TRUE(stmt.getBodyStmt()->is<CompoundStmt>());
        EXPECT_EQ(1, stmt.getBodyStmt()->getStmts().size());
    }

    {
        // do {} while (true);
        const auto stmt = DoWhileStmt::make(BoolLiteralExpr::make(true), CompoundStmt::make());

        EXPECT_EQ(StmtKind::DoWhile, stmt->getKind());
        EXPECT_TRUE(stmt->is<DoWhileStmt>());
        ASSERT_NE(nullptr, stmt->getCondExpr());
        EXPECT_TRUE(stmt->getCondExpr()->is<BoolLiteralExpr>());
        ASSERT_NE(nullptr, stmt->getBodyStmt());
        EXPECT_TRUE(stmt->getBodyStmt()->is<CompoundStmt>());
    }
}

/* ************************************************************************ */

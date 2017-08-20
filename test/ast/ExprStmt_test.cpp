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

TEST(ExprStmt, base)
{
    {
        // ;
        const ExprStmt stmt;

        EXPECT_EQ(StmtKind::Expr, stmt.getKind());
        EXPECT_TRUE(stmt.is<ExprStmt>());
        ASSERT_EQ(nullptr, stmt.getExpr());
    }

    {
        // 5;
        const ExprStmt stmt(IntLiteralExpr::make(5));

        EXPECT_EQ(StmtKind::Expr, stmt.getKind());
        EXPECT_TRUE(stmt.is<ExprStmt>());
        ASSERT_NE(nullptr, stmt.getExpr());
        EXPECT_TRUE(stmt.getExpr()->is<IntLiteralExpr>());
    }

    {
        // 5;
        ExprStmt stmt(IntLiteralExpr::make(5));

        EXPECT_EQ(StmtKind::Expr, stmt.getKind());
        EXPECT_TRUE(stmt.is<ExprStmt>());
        ASSERT_NE(nullptr, stmt.getExpr());
        EXPECT_TRUE(stmt.getExpr()->is<IntLiteralExpr>());

        // true;
        stmt.setExpr(BoolLiteralExpr::make(true));
        EXPECT_TRUE(stmt.is<ExprStmt>());
        ASSERT_NE(nullptr, stmt.getExpr());
        EXPECT_TRUE(stmt.getExpr()->is<BoolLiteralExpr>());
    }

    {
        // ;
        const auto stmt = ExprStmt::make();

        EXPECT_EQ(StmtKind::Expr, stmt->getKind());
        EXPECT_TRUE(stmt->is<ExprStmt>());
        ASSERT_EQ(nullptr, stmt->getExpr());
    }
}

/* ************************************************************************ */

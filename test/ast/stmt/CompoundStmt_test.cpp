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
#include "shard/ast/stmt/CompoundStmt.hpp"
#include "shard/ast/stmt/ExprStmt.hpp"
#include "shard/ast/expr/IntLiteralExpr.hpp"
#include "shard/ast/Decl.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

TEST(CompoundStmt, base)
{
    {
        // {}
        const CompoundStmt stmt;

        EXPECT_EQ(StmtKind::Compound, stmt.getKind());
        EXPECT_TRUE(stmt.is<CompoundStmt>());
        EXPECT_TRUE(stmt.getStmts().empty());
    }

    {
        PtrDynamicArray<Stmt> stmts;
        stmts.push_back(ExprStmt::make());
        stmts.push_back(ExprStmt::make(IntLiteralExpr::make(789)));

        // { ; 789; }
        const CompoundStmt stmt(moveValue(stmts));

        EXPECT_EQ(StmtKind::Compound, stmt.getKind());
        EXPECT_TRUE(stmt.is<CompoundStmt>());
        EXPECT_FALSE(stmt.getStmts().empty());
        EXPECT_EQ(2, stmt.getStmts().size());
    }

    {
        // {}
        CompoundStmt stmt;

        EXPECT_EQ(StmtKind::Compound, stmt.getKind());
        EXPECT_TRUE(stmt.is<CompoundStmt>());
        EXPECT_TRUE(stmt.getStmts().empty());

        // { ; 789; }
        stmt.addStmt(ExprStmt::make());
        stmt.addStmt(ExprStmt::make(IntLiteralExpr::make(789)));
        EXPECT_EQ(2, stmt.getStmts().size());
    }

    {
        // { }
        CompoundStmt stmt;

        EXPECT_EQ(StmtKind::Compound, stmt.getKind());
        EXPECT_TRUE(stmt.is<CompoundStmt>());
        EXPECT_TRUE(stmt.getStmts().empty());

        PtrDynamicArray<Stmt> stmts;
        stmts.push_back(ExprStmt::make());
        stmts.push_back(ExprStmt::make(IntLiteralExpr::make(789)));

        // { ; 789; }
        stmt.setStmts(moveValue(stmts));

        EXPECT_EQ(StmtKind::Compound, stmt.getKind());
        EXPECT_TRUE(stmt.is<CompoundStmt>());
        EXPECT_FALSE(stmt.getStmts().empty());
        EXPECT_EQ(2, stmt.getStmts().size());
    }

    {
        // {}
        const auto stmt = CompoundStmt::make();

        EXPECT_EQ(StmtKind::Compound, stmt->getKind());
        EXPECT_TRUE(stmt->is<CompoundStmt>());
   }
}

/* ************************************************************************ */

TEST(CompoundStmt, parent)
{
    {
        PtrDynamicArray<Stmt> stmts;
        stmts.push_back(ExprStmt::make());
        stmts.push_back(ExprStmt::make(IntLiteralExpr::make(789)));

        // { ; 789; }
        const CompoundStmt stmt(moveValue(stmts));

        EXPECT_FALSE(stmt.getStmts().empty());
        EXPECT_EQ(2, stmt.getStmts().size());
    }

    {
        PtrDynamicArray<Stmt> stmts;
        stmts.push_back(ExprStmt::make());
        stmts.push_back(ExprStmt::make(IntLiteralExpr::make(789)));

        // { ; 789; }
        CompoundStmt stmt(moveValue(stmts));

        EXPECT_FALSE(stmt.getStmts().empty());
        EXPECT_EQ(2, stmt.getStmts().size());

        stmt.addStmt(ExprStmt::make());
        EXPECT_FALSE(stmt.getStmts().empty());
        EXPECT_EQ(3, stmt.getStmts().size());
    }

    {
        // { ; 789; }
        const auto stmt = CompoundStmt::make();

        EXPECT_TRUE(stmt->getStmts().empty());
    }
}

/* ************************************************************************ */

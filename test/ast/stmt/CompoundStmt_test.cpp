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

        EXPECT_TRUE(stmt.is<CompoundStmt>());
        EXPECT_TRUE(stmt.stmts().empty());
    }

    {
        StmtPtrVector stmts;
        stmts.push_back(ExprStmt::make(nullptr));
        stmts.push_back(ExprStmt::make(IntLiteralExpr::make(789)));

        // { ; 789; }
        const CompoundStmt stmt(std::move(stmts));

        EXPECT_TRUE(stmt.is<CompoundStmt>());
        EXPECT_FALSE(stmt.stmts().empty());
        EXPECT_EQ(2, stmt.stmts().size());
    }

    {
        // {}
        CompoundStmt stmt;

        EXPECT_TRUE(stmt.is<CompoundStmt>());
        EXPECT_TRUE(stmt.stmts().empty());

        // { ; 789; }
        stmt.addStmt(ExprStmt::make(nullptr));
        stmt.addStmt(ExprStmt::make(IntLiteralExpr::make(789)));
        EXPECT_EQ(2, stmt.stmts().size());
    }

    {
        // { }
        CompoundStmt stmt;

        EXPECT_TRUE(stmt.is<CompoundStmt>());
        EXPECT_TRUE(stmt.stmts().empty());

        StmtPtrVector stmts;
        stmts.push_back(ExprStmt::make(nullptr));
        stmts.push_back(ExprStmt::make(IntLiteralExpr::make(789)));

        // { ; 789; }
        stmt.setStmts(std::move(stmts));

        EXPECT_TRUE(stmt.is<CompoundStmt>());
        EXPECT_FALSE(stmt.stmts().empty());
        EXPECT_EQ(2, stmt.stmts().size());
    }

    {
        // {}
        const auto stmt = CompoundStmt::make({});

        EXPECT_TRUE(stmt->is<CompoundStmt>());
   }
}

/* ************************************************************************ */

TEST(CompoundStmt, parent)
{
    {
        StmtPtrVector stmts;
        stmts.push_back(ExprStmt::make(nullptr));
        stmts.push_back(ExprStmt::make(IntLiteralExpr::make(789)));

        // { ; 789; }
        const CompoundStmt stmt(std::move(stmts));

        EXPECT_FALSE(stmt.stmts().empty());
        EXPECT_EQ(2, stmt.stmts().size());
    }

    {
        StmtPtrVector stmts;
        stmts.push_back(ExprStmt::make(nullptr));
        stmts.push_back(ExprStmt::make(IntLiteralExpr::make(789)));

        // { ; 789; }
        CompoundStmt stmt(std::move(stmts));

        EXPECT_FALSE(stmt.stmts().empty());
        EXPECT_EQ(2, stmt.stmts().size());

        stmt.addStmt(ExprStmt::make(nullptr));
        EXPECT_FALSE(stmt.stmts().empty());
        EXPECT_EQ(3, stmt.stmts().size());
    }

    {
        // { ; 789; }
        const auto stmt = CompoundStmt::make({});

        EXPECT_TRUE(stmt->stmts().empty());
    }
}

/* ************************************************************************ */

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
#include "shard/ast/stmt/DefaultStmt.hpp"
#include "shard/ast/stmt/ExprStmt.hpp"
#include "shard/ast/stmt/BreakStmt.hpp"
#include "shard/ast/Decl.hpp"
#include "shard/ast/Expr.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

TEST(DefaultStmt, base)
{
    {
        // default: ;
        const DefaultStmt stmt;

        EXPECT_EQ(StmtKind::Default, stmt.getKind());
        EXPECT_TRUE(stmt.is<DefaultStmt>());
        ASSERT_TRUE(stmt.getStmts().empty());
    }

    {
        // default: ;
        DefaultStmt stmt;

        stmt.addStmt(ExprStmt::make(nullptr));

        EXPECT_EQ(StmtKind::Default, stmt.getKind());
        EXPECT_TRUE(stmt.is<DefaultStmt>());
        ASSERT_FALSE(stmt.getStmts().empty());
        EXPECT_EQ(1, stmt.getStmts().size());
    }

    {
        // default: ;
        DefaultStmt stmt;

        stmt.addStmt(ExprStmt::make(nullptr));

        EXPECT_EQ(StmtKind::Default, stmt.getKind());
        EXPECT_TRUE(stmt.is<DefaultStmt>());
        ASSERT_FALSE(stmt.getStmts().empty());
        EXPECT_EQ(1, stmt.getStmts().size());

        // default: break;
        stmt.addStmt(BreakStmt::make());

        ASSERT_FALSE(stmt.getStmts().empty());
        EXPECT_EQ(2, stmt.getStmts().size());
    }

    {
        // default:
        DefaultStmt stmt;

        EXPECT_EQ(StmtKind::Default, stmt.getKind());
        EXPECT_TRUE(stmt.is<DefaultStmt>());
        ASSERT_TRUE(stmt.getStmts().empty());

        PtrVector<Stmt> stmts;
        stmts.push_back(ExprStmt::make(nullptr));

        // default: ;
        stmt.setStmts(std::move(stmts));

        EXPECT_EQ(StmtKind::Default, stmt.getKind());
        EXPECT_TRUE(stmt.is<DefaultStmt>());
        ASSERT_FALSE(stmt.getStmts().empty());
        ASSERT_EQ(1, stmt.getStmts().size());
    }

    {
        // default: ;
        const auto stmt = DefaultStmt::make();

        EXPECT_EQ(StmtKind::Default, stmt->getKind());
        EXPECT_TRUE(stmt->is<DefaultStmt>());
        ASSERT_TRUE(stmt->getStmts().empty());
    }
}

/* ************************************************************************ */

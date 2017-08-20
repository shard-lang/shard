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

TEST(DeclStmt, base)
{
    {
        // int foo;
        const DeclStmt stmt(VariableDecl::make(TypeKind::Int, "foo"));

        EXPECT_EQ(StmtKind::Decl, stmt.getKind());
        EXPECT_TRUE(stmt.is<DeclStmt>());
        ASSERT_NE(nullptr, stmt.getDecl());
        ASSERT_TRUE(stmt.getDecl()->is<VariableDecl>());
    }

    {
        // int foo;
        DeclStmt stmt(VariableDecl::make(TypeKind::Int, "foo"));

        EXPECT_EQ(StmtKind::Decl, stmt.getKind());
        EXPECT_TRUE(stmt.is<DeclStmt>());
        ASSERT_NE(nullptr, stmt.getDecl());
        ASSERT_TRUE(stmt.getDecl()->is<VariableDecl>());
        ASSERT_EQ("foo", stmt.getDecl()->cast<VariableDecl>().getName());
        ASSERT_EQ(TypeKind::Int, stmt.getDecl()->cast<VariableDecl>().getType());

        // float bar;
        stmt.setDecl(VariableDecl::make(TypeKind::Float, "bar"));
        EXPECT_TRUE(stmt.is<DeclStmt>());
        ASSERT_NE(nullptr, stmt.getDecl());
        ASSERT_TRUE(stmt.getDecl()->is<VariableDecl>());
        ASSERT_EQ("bar", stmt.getDecl()->cast<VariableDecl>().getName());
        ASSERT_EQ(TypeKind::Float, stmt.getDecl()->cast<VariableDecl>().getType());
    }

    {
        // int foo;
        const auto stmt = DeclStmt::make(VariableDecl::make(TypeKind::Int, "foo"));

        EXPECT_EQ(StmtKind::Decl, stmt->getKind());
        EXPECT_TRUE(stmt->is<DeclStmt>());
        ASSERT_NE(nullptr, stmt->getDecl());
        ASSERT_TRUE(stmt->getDecl()->is<VariableDecl>());
    }
}

/* ************************************************************************ */

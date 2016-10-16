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

TEST(ExprStmt, construction)
{
    {
        const ExprStmt stmt(makeUnique<IntLiteralExpr>(5));

        EXPECT_EQ(StmtKind::Expr, stmt.getKind());
        EXPECT_TRUE(ExprStmt::is(stmt));
        ASSERT_TRUE(stmt.getExpr());
        ASSERT_TRUE(IntLiteralExpr::is(stmt.getExpr()));
    }
}

/* ************************************************************************ */

TEST(DeclStmt, construction)
{
    {
        const DeclStmt stmt(makeUnique<VariableDecl>(nullptr, "foo", TypeInfo{&TYPE_BUILTIN_INT}));

        EXPECT_EQ(StmtKind::Decl, stmt.getKind());
        EXPECT_TRUE(DeclStmt::is(stmt));
        ASSERT_TRUE(stmt.getDecl());
        ASSERT_TRUE(VariableDecl::is(stmt.getDecl()));
    }
}

/* ************************************************************************ */

TEST(CompoundStmt, construction)
{
    {
        const CompoundStmt stmt;

        EXPECT_EQ(StmtKind::Compound, stmt.getKind());
        EXPECT_TRUE(CompoundStmt::is(stmt));
        EXPECT_TRUE(stmt.isEmpty());
    }
}

/* ************************************************************************ */

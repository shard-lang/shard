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
        // ;
        const ExprStmt stmt;

        EXPECT_EQ(StmtKind::Expr, stmt.getKind());
        EXPECT_TRUE(ExprStmt::is(stmt));
        ASSERT_FALSE(stmt.getExpr());
    }

    {
        // 5;
        const ExprStmt stmt(makeUnique<IntLiteralExpr>(5));

        EXPECT_EQ(StmtKind::Expr, stmt.getKind());
        EXPECT_TRUE(ExprStmt::is(stmt));
        ASSERT_TRUE(stmt.getExpr());
        EXPECT_TRUE(IntLiteralExpr::is(stmt.getExpr()));
    }
}

/* ************************************************************************ */

TEST(DeclStmt, construction)
{
    {
        // int foo;
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
        // {}
        const CompoundStmt stmt;

        EXPECT_EQ(StmtKind::Compound, stmt.getKind());
        EXPECT_TRUE(CompoundStmt::is(stmt));
        EXPECT_TRUE(stmt.isEmpty());
    }

    {
        DynamicArray<UniquePtr<Stmt>> stmts;
        stmts.push_back(makeUnique<ExprStmt>());
        stmts.push_back(makeUnique<ExprStmt>(makeUnique<IntLiteralExpr>(789)));

        // { ; 789; }
        const CompoundStmt stmt(moveValue(stmts));

        EXPECT_EQ(StmtKind::Compound, stmt.getKind());
        EXPECT_TRUE(CompoundStmt::is(stmt));
        EXPECT_FALSE(stmt.isEmpty());
        EXPECT_EQ(2, stmt.getCount());
    }
}

/* ************************************************************************ */

TEST(IfStmt, construction)
{
    {
        // if (true) {}
        const IfStmt stmt(makeUnique<BoolLiteralExpr>(true), makeUnique<CompoundStmt>());

        EXPECT_EQ(StmtKind::If, stmt.getKind());
        EXPECT_TRUE(IfStmt::is(stmt));
        ASSERT_TRUE(stmt.getCondExpr());
        EXPECT_TRUE(BoolLiteralExpr::is(stmt.getCondExpr()));
        ASSERT_TRUE(stmt.getThenStmt());
        EXPECT_TRUE(CompoundStmt::is(stmt.getThenStmt()));
        EXPECT_FALSE(stmt.getElseStmt());
    }

    {
        // if (true) {} else ;
        const IfStmt stmt(makeUnique<BoolLiteralExpr>(true), makeUnique<CompoundStmt>(), makeUnique<ExprStmt>());

        EXPECT_EQ(StmtKind::If, stmt.getKind());
        EXPECT_TRUE(IfStmt::is(stmt));
        ASSERT_TRUE(stmt.getCondExpr());
        EXPECT_TRUE(BoolLiteralExpr::is(stmt.getCondExpr()));
        ASSERT_TRUE(stmt.getThenStmt());
        EXPECT_TRUE(CompoundStmt::is(stmt.getThenStmt()));
        ASSERT_TRUE(stmt.getElseStmt());
        EXPECT_TRUE(ExprStmt::is(stmt.getElseStmt()));
    }
}

/* ************************************************************************ */

TEST(WhileStmt, construction)
{
    {
        // while (true);
        const WhileStmt stmt(makeUnique<BoolLiteralExpr>(true), makeUnique<ExprStmt>());

        EXPECT_EQ(StmtKind::While, stmt.getKind());
        EXPECT_TRUE(WhileStmt::is(stmt));
        ASSERT_TRUE(stmt.getCondExpr());
        EXPECT_TRUE(BoolLiteralExpr::is(stmt.getCondExpr()));
        ASSERT_TRUE(stmt.getBodyStmt());
        EXPECT_TRUE(ExprStmt::is(stmt.getBodyStmt()));
    }
}

/* ************************************************************************ */

TEST(DoWhileStmt, construction)
{
    {
        // do {} while (true);
        const DoWhileStmt stmt(makeUnique<BoolLiteralExpr>(true), makeUnique<CompoundStmt>());

        EXPECT_EQ(StmtKind::DoWhile, stmt.getKind());
        EXPECT_TRUE(DoWhileStmt::is(stmt));
        ASSERT_TRUE(stmt.getCondExpr());
        EXPECT_TRUE(BoolLiteralExpr::is(stmt.getCondExpr()));
        ASSERT_TRUE(stmt.getBodyStmt());
        EXPECT_TRUE(CompoundStmt::is(stmt.getBodyStmt()));
    }
}

/* ************************************************************************ */

TEST(ForStmt, construction)
{
    {
        // for (; true; ) {}
        const ForStmt stmt(makeUnique<ExprStmt>(), makeUnique<BoolLiteralExpr>(true), nullptr, makeUnique<CompoundStmt>());

        EXPECT_EQ(StmtKind::For, stmt.getKind());
        EXPECT_TRUE(ForStmt::is(stmt));
        ASSERT_TRUE(stmt.getInitStmt());
        EXPECT_TRUE(ExprStmt::is(stmt.getInitStmt()));
        ASSERT_TRUE(stmt.getCondExpr());
        EXPECT_TRUE(BoolLiteralExpr::is(stmt.getCondExpr()));
        EXPECT_FALSE(stmt.getIncExpr());
        ASSERT_TRUE(stmt.getBodyStmt());
        EXPECT_TRUE(CompoundStmt::is(stmt.getBodyStmt()));
    }

    {
        // for (; true; 5) {}
        const ForStmt stmt(makeUnique<ExprStmt>(), makeUnique<BoolLiteralExpr>(true), makeUnique<IntLiteralExpr>(5), makeUnique<CompoundStmt>());

        EXPECT_EQ(StmtKind::For, stmt.getKind());
        EXPECT_TRUE(ForStmt::is(stmt));
        ASSERT_TRUE(stmt.getInitStmt());
        EXPECT_TRUE(ExprStmt::is(stmt.getInitStmt()));
        ASSERT_TRUE(stmt.getCondExpr());
        EXPECT_TRUE(BoolLiteralExpr::is(stmt.getCondExpr()));
        ASSERT_TRUE(stmt.getIncExpr());
        EXPECT_TRUE(IntLiteralExpr::is(stmt.getIncExpr()));
        ASSERT_TRUE(stmt.getBodyStmt());
        EXPECT_TRUE(CompoundStmt::is(stmt.getBodyStmt()));
    }
}

/* ************************************************************************ */

TEST(SwitchStmt, construction)
{
    {
        // switch (id) {}
        const SwitchStmt stmt(makeUnique<IdentifierExpr>("id"), makeUnique<CompoundStmt>());

        EXPECT_EQ(StmtKind::Switch, stmt.getKind());
        EXPECT_TRUE(SwitchStmt::is(stmt));
        ASSERT_TRUE(stmt.getCondExpr());
        EXPECT_TRUE(IdentifierExpr::is(stmt.getCondExpr()));
        ASSERT_TRUE(stmt.getBodyStmt());
        EXPECT_TRUE(CompoundStmt::is(stmt.getBodyStmt()));
    }
}

/* ************************************************************************ */

TEST(CaseStmt, construction)
{
    {
        // case 0: ;
        const CaseStmt stmt(makeUnique<IntLiteralExpr>(0), makeUnique<ExprStmt>());

        EXPECT_EQ(StmtKind::Case, stmt.getKind());
        EXPECT_TRUE(CaseStmt::is(stmt));
        ASSERT_TRUE(stmt.getExpr());
        EXPECT_TRUE(IntLiteralExpr::is(stmt.getExpr()));
        ASSERT_TRUE(stmt.getBodyStmt());
        EXPECT_TRUE(ExprStmt::is(stmt.getBodyStmt()));
    }
}

/* ************************************************************************ */

TEST(DefaultStmt, construction)
{
    {
        // case 0: ;
        const DefaultStmt stmt(makeUnique<ExprStmt>());

        EXPECT_EQ(StmtKind::Default, stmt.getKind());
        EXPECT_TRUE(DefaultStmt::is(stmt));
        ASSERT_TRUE(stmt.getBodyStmt());
        EXPECT_TRUE(ExprStmt::is(stmt.getBodyStmt()));
    }
}

/* ************************************************************************ */

TEST(ContinueStmt, construction)
{
    {
        // continue;
        const ContinueStmt stmt;

        EXPECT_EQ(StmtKind::Continue, stmt.getKind());
        EXPECT_TRUE(ContinueStmt::is(stmt));
    }
}

/* ************************************************************************ */

TEST(BreakStmt, construction)
{
    {
        // break;
        const BreakStmt stmt;

        EXPECT_EQ(StmtKind::Break, stmt.getKind());
        EXPECT_TRUE(BreakStmt::is(stmt));
    }
}

/* ************************************************************************ */

TEST(ReturnStmt, construction)
{
    {
        // return;
        const ReturnStmt stmt;

        EXPECT_EQ(StmtKind::Return, stmt.getKind());
        EXPECT_TRUE(ReturnStmt::is(stmt));
    }

    {
        // return true;
        const ReturnStmt stmt(makeUnique<BoolLiteralExpr>(true));

        EXPECT_EQ(StmtKind::Return, stmt.getKind());
        EXPECT_TRUE(ReturnStmt::is(stmt));
        ASSERT_TRUE(stmt.getResExpr());
        EXPECT_TRUE(BoolLiteralExpr::is(stmt.getResExpr()));
    }
}

/* ************************************************************************ */

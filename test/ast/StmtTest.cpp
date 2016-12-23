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

TEST(IfStmt, base)
{
    {
        // if (true) {}
        const IfStmt stmt(BoolLiteralExpr::make(true), CompoundStmt::make());

        EXPECT_EQ(StmtKind::If, stmt.getKind());
        EXPECT_TRUE(stmt.is<IfStmt>());
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(stmt.getCondExpr()->is<BoolLiteralExpr>());
        ASSERT_NE(nullptr, stmt.getThenStmt());
        EXPECT_TRUE(stmt.getThenStmt()->is<CompoundStmt>());
        EXPECT_EQ(nullptr, stmt.getElseStmt());
    }

    {
        // if (true) {} else ;
        const IfStmt stmt(BoolLiteralExpr::make(true), CompoundStmt::make(), ExprStmt::make());

        EXPECT_EQ(StmtKind::If, stmt.getKind());
        EXPECT_TRUE(stmt.is<IfStmt>());
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(stmt.getCondExpr()->is<BoolLiteralExpr>());
        ASSERT_NE(nullptr, stmt.getThenStmt());
        EXPECT_TRUE(stmt.getThenStmt()->is<CompoundStmt>());
        ASSERT_NE(nullptr, stmt.getElseStmt());
        EXPECT_TRUE(stmt.getElseStmt()->is<ExprStmt>());
    }

    {
        // if (true) {} else ;
        IfStmt stmt(BoolLiteralExpr::make(true), CompoundStmt::make(), ExprStmt::make());

        EXPECT_EQ(StmtKind::If, stmt.getKind());
        EXPECT_TRUE(stmt.is<IfStmt>());
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(stmt.getCondExpr()->is<BoolLiteralExpr>());
        ASSERT_NE(nullptr, stmt.getThenStmt());
        EXPECT_TRUE(stmt.getThenStmt()->is<CompoundStmt>());
        ASSERT_NE(nullptr, stmt.getElseStmt());
        EXPECT_TRUE(stmt.getElseStmt()->is<ExprStmt>());

        // if (1) return;
        stmt.setCondExpr(IntLiteralExpr::make(1));
        stmt.setThenStmt(ReturnStmt::make());
        stmt.setElseStmt(nullptr);

        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(stmt.getCondExpr()->is<IntLiteralExpr>());
        ASSERT_NE(nullptr, stmt.getThenStmt());
        EXPECT_TRUE(stmt.getThenStmt()->is<ReturnStmt>());
        ASSERT_EQ(nullptr, stmt.getElseStmt());
    }

    {
        // if (true) {}
        const auto stmt = IfStmt::make(BoolLiteralExpr::make(true), CompoundStmt::make());

        EXPECT_EQ(StmtKind::If, stmt->getKind());
        EXPECT_TRUE(stmt->is<IfStmt>());
        ASSERT_NE(nullptr, stmt->getCondExpr());
        EXPECT_TRUE(stmt->getCondExpr()->is<BoolLiteralExpr>());
        ASSERT_NE(nullptr, stmt->getThenStmt());
        EXPECT_TRUE(stmt->getThenStmt()->is<CompoundStmt>());
        EXPECT_EQ(nullptr, stmt->getElseStmt());
    }
}

/* ************************************************************************ */

TEST(WhileStmt, base)
{
    {
        // while (true);
        const WhileStmt stmt(BoolLiteralExpr::make(true), ExprStmt::make());

        EXPECT_EQ(StmtKind::While, stmt.getKind());
        EXPECT_TRUE(stmt.is<WhileStmt>());
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(stmt.getCondExpr()->is<BoolLiteralExpr>());
        ASSERT_NE(nullptr, stmt.getBodyStmt());
        EXPECT_TRUE(stmt.getBodyStmt()->is<ExprStmt>());
    }

    {
        // while (true);
        WhileStmt stmt(BoolLiteralExpr::make(true), ExprStmt::make());

        EXPECT_EQ(StmtKind::While, stmt.getKind());
        EXPECT_TRUE(stmt.is<WhileStmt>());
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(stmt.getCondExpr()->is<BoolLiteralExpr>());
        ASSERT_NE(nullptr, stmt.getBodyStmt());
        EXPECT_TRUE(stmt.getBodyStmt()->is<ExprStmt>());

        // while (1) continue;
        stmt.setCondExpr(IntLiteralExpr::make(1));
        stmt.setBodyStmt(ContinueStmt::make());

        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(stmt.getCondExpr()->is<IntLiteralExpr>());
        ASSERT_NE(nullptr, stmt.getBodyStmt());
        EXPECT_TRUE(stmt.getBodyStmt()->is<ContinueStmt>());
    }

    {
        // while (true);
        const auto stmt = WhileStmt::make(BoolLiteralExpr::make(true), ExprStmt::make());

        EXPECT_EQ(StmtKind::While, stmt->getKind());
        EXPECT_TRUE(stmt->is<WhileStmt>());
        ASSERT_NE(nullptr, stmt->getCondExpr());
        EXPECT_TRUE(stmt->getCondExpr()->is<BoolLiteralExpr>());
        ASSERT_NE(nullptr, stmt->getBodyStmt());
        EXPECT_TRUE(stmt->getBodyStmt()->is<ExprStmt>());
    }
}

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

TEST(SwitchStmt, base)
{
    {
        // switch (id) {}
        const SwitchStmt stmt(IdentifierExpr::make("id"), CompoundStmt::make());

        EXPECT_EQ(StmtKind::Switch, stmt.getKind());
        EXPECT_TRUE(stmt.is<SwitchStmt>());
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(stmt.getCondExpr()->is<IdentifierExpr>());
        ASSERT_NE(nullptr, stmt.getBodyStmt());
        EXPECT_TRUE(stmt.getBodyStmt()->is<CompoundStmt>());
    }

    {
        // switch (id) {}
        SwitchStmt stmt(IdentifierExpr::make("id"), CompoundStmt::make());

        EXPECT_EQ(StmtKind::Switch, stmt.getKind());
        EXPECT_TRUE(stmt.is<SwitchStmt>());
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(stmt.getCondExpr()->is<IdentifierExpr>());
        ASSERT_NE(nullptr, stmt.getBodyStmt());
        EXPECT_TRUE(stmt.getBodyStmt()->is<CompoundStmt>());

        // swich (type) { case 1: break; }
        stmt.setCondExpr(IdentifierExpr::make("type"));

        auto body = CompoundStmt::make();
        auto caseStmt = CaseStmt::make(IntLiteralExpr::make(1));

        caseStmt->addStmt(BreakStmt::make());

        body->addStmt(moveValue(caseStmt));

        stmt.setBodyStmt(moveValue(body));

        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(stmt.getCondExpr()->is<IdentifierExpr>());
        ASSERT_NE(nullptr, stmt.getBodyStmt());
        EXPECT_TRUE(stmt.getBodyStmt()->is<CompoundStmt>());
        EXPECT_EQ(1, stmt.getBodyStmt()->getStmts().size());
    }

    {
        // switch (id) {}
        const auto stmt = SwitchStmt::make(IdentifierExpr::make("id"), CompoundStmt::make());

        EXPECT_EQ(StmtKind::Switch, stmt->getKind());
        EXPECT_TRUE(stmt->is<SwitchStmt>());
        ASSERT_NE(nullptr, stmt->getCondExpr());
        EXPECT_TRUE(stmt->getCondExpr()->is<IdentifierExpr>());
        ASSERT_NE(nullptr, stmt->getBodyStmt());
        EXPECT_TRUE(stmt->getBodyStmt()->is<CompoundStmt>());
    }
}

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

        stmt.addStmt(ExprStmt::make());

        EXPECT_EQ(StmtKind::Default, stmt.getKind());
        EXPECT_TRUE(stmt.is<DefaultStmt>());
        ASSERT_FALSE(stmt.getStmts().empty());
        EXPECT_EQ(1, stmt.getStmts().size());
    }

    {
        // default: ;
        DefaultStmt stmt;

        stmt.addStmt(ExprStmt::make());

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

        PtrDynamicArray<Stmt> stmts;
        stmts.push_back(ExprStmt::make());

        // default: ;
        stmt.setStmts(moveValue(stmts));

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

TEST(ContinueStmt, base)
{
    {
        // continue;
        const ContinueStmt stmt;

        EXPECT_EQ(StmtKind::Continue, stmt.getKind());
        EXPECT_TRUE(stmt.is<ContinueStmt>());
    }

    {
        // continue;
        const auto stmt = ContinueStmt::make();

        EXPECT_EQ(StmtKind::Continue, stmt->getKind());
        EXPECT_TRUE(stmt->is<ContinueStmt>());
    }
}

/* ************************************************************************ */

TEST(BreakStmt, base)
{
    {
        // break;
        const BreakStmt stmt;

        EXPECT_EQ(StmtKind::Break, stmt.getKind());
        EXPECT_TRUE(stmt.is<BreakStmt>());
    }

    {
        // break;
        const auto stmt = BreakStmt::make();

        EXPECT_EQ(StmtKind::Break, stmt->getKind());
        EXPECT_TRUE(stmt->is<BreakStmt>());
    }
}

/* ************************************************************************ */

TEST(ReturnStmt, base)
{
    {
        // return;
        const ReturnStmt stmt;

        EXPECT_EQ(StmtKind::Return, stmt.getKind());
        EXPECT_TRUE(stmt.is<ReturnStmt>());
        ASSERT_EQ(nullptr, stmt.getResExpr());
    }

    {
        // return true;
        const ReturnStmt stmt(BoolLiteralExpr::make(true));

        EXPECT_EQ(StmtKind::Return, stmt.getKind());
        EXPECT_TRUE(stmt.is<ReturnStmt>());
        ASSERT_NE(nullptr, stmt.getResExpr());
        EXPECT_TRUE(stmt.getResExpr()->is<BoolLiteralExpr>());
    }


    {
        // return;
        ReturnStmt stmt;

        EXPECT_EQ(StmtKind::Return, stmt.getKind());
        EXPECT_TRUE(stmt.is<ReturnStmt>());
        ASSERT_EQ(nullptr, stmt.getResExpr());

        // return 1.1;
        stmt.setResExpr(FloatLiteralExpr::make(1.1));

        ASSERT_NE(nullptr, stmt.getResExpr());
        EXPECT_TRUE(stmt.getResExpr()->is<FloatLiteralExpr>());
    }

    {
        // return;
        const auto stmt = ReturnStmt::make();

        EXPECT_EQ(StmtKind::Return, stmt->getKind());
        EXPECT_TRUE(stmt->is<ReturnStmt>());
        ASSERT_EQ(nullptr, stmt->getResExpr());
    }

}

/* ************************************************************************ */

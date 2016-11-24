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
        EXPECT_TRUE(ExprStmt::is(stmt));
        ASSERT_EQ(nullptr, stmt.getExpr());
    }

    {
        // 5;
        const ExprStmt stmt(IntLiteralExpr::make(5));

        EXPECT_EQ(StmtKind::Expr, stmt.getKind());
        EXPECT_TRUE(ExprStmt::is(stmt));
        ASSERT_NE(nullptr, stmt.getExpr());
        EXPECT_TRUE(IntLiteralExpr::is(stmt.getExpr()));
    }

    {
        // 5;
        ExprStmt stmt(IntLiteralExpr::make(5));

        EXPECT_EQ(StmtKind::Expr, stmt.getKind());
        EXPECT_TRUE(ExprStmt::is(stmt));
        ASSERT_NE(nullptr, stmt.getExpr());
        EXPECT_TRUE(IntLiteralExpr::is(stmt.getExpr()));

        // true;
        stmt.setExpr(BoolLiteralExpr::make(true));
        EXPECT_TRUE(ExprStmt::is(stmt));
        ASSERT_NE(nullptr, stmt.getExpr());
        EXPECT_TRUE(BoolLiteralExpr::is(stmt.getExpr()));
    }
}

/* ************************************************************************ */

TEST(DeclStmt, base)
{
    {
        // int foo;
        const DeclStmt stmt(VariableDecl::make(nullptr, TypeInfo{&TYPE_BUILTIN_INT}, "foo"));

        EXPECT_EQ(StmtKind::Decl, stmt.getKind());
        EXPECT_TRUE(DeclStmt::is(stmt));
        ASSERT_NE(nullptr, stmt.getDecl());
        ASSERT_TRUE(VariableDecl::is(stmt.getDecl()));
    }

    {
        // int foo;
        DeclStmt stmt(VariableDecl::make(nullptr, TypeInfo{&TYPE_BUILTIN_INT}, "foo"));

        EXPECT_EQ(StmtKind::Decl, stmt.getKind());
        EXPECT_TRUE(DeclStmt::is(stmt));
        ASSERT_NE(nullptr, stmt.getDecl());
        ASSERT_TRUE(VariableDecl::is(stmt.getDecl()));
        ASSERT_EQ("foo", VariableDecl::cast(stmt.getDecl())->getName());
        ASSERT_EQ(&TYPE_BUILTIN_INT, VariableDecl::cast(stmt.getDecl())->getType());

        // float bar;
        stmt.setDecl(VariableDecl::make(nullptr, TypeInfo{&TYPE_BUILTIN_FLOAT}, "bar"));
        EXPECT_TRUE(DeclStmt::is(stmt));
        ASSERT_NE(nullptr, stmt.getDecl());
        ASSERT_TRUE(VariableDecl::is(stmt.getDecl()));
        ASSERT_EQ("bar", VariableDecl::cast(stmt.getDecl())->getName());
        ASSERT_EQ(&TYPE_BUILTIN_FLOAT, VariableDecl::cast(stmt.getDecl())->getType());
    }
}

/* ************************************************************************ */

TEST(CompoundStmt, base)
{
    {
        // {}
        const CompoundStmt stmt;

        EXPECT_EQ(StmtKind::Compound, stmt.getKind());
        EXPECT_TRUE(CompoundStmt::is(stmt));
        EXPECT_TRUE(stmt.isEmpty());
    }

    {
        PtrDynamicArray<Stmt> stmts;
        stmts.push_back(ExprStmt::make());
        stmts.push_back(ExprStmt::make(IntLiteralExpr::make(789)));

        // { ; 789; }
        const CompoundStmt stmt(moveValue(stmts));

        EXPECT_EQ(StmtKind::Compound, stmt.getKind());
        EXPECT_TRUE(CompoundStmt::is(stmt));
        EXPECT_FALSE(stmt.isEmpty());
        EXPECT_EQ(2, stmt.getCount());
    }

    {
        // {}
        CompoundStmt stmt;

        EXPECT_EQ(StmtKind::Compound, stmt.getKind());
        EXPECT_TRUE(CompoundStmt::is(stmt));
        EXPECT_TRUE(stmt.isEmpty());

        // { ; 789; }
        stmt.addStatement(ExprStmt::make());
        stmt.addStatement(ExprStmt::make(IntLiteralExpr::make(789)));
        EXPECT_EQ(2, stmt.getCount());
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

        EXPECT_FALSE(stmt.isEmpty());
        EXPECT_EQ(2, stmt.getCount());
        EXPECT_EQ(2, stmt.getStatements().size());

        int count = 0;

        // begin/end
        for (auto it = stmt.begin(); it != stmt.end(); ++it)
        {
            ++count;
        }

        EXPECT_EQ(2, count);

        count = 0;

        // begin/end
        for (auto it = stmt.cbegin(); it != stmt.cend(); ++it)
        {
            ++count;
        }

        EXPECT_EQ(2, count);
    }

    {
        PtrDynamicArray<Stmt> stmts;
        stmts.push_back(ExprStmt::make());
        stmts.push_back(ExprStmt::make(IntLiteralExpr::make(789)));

        // { ; 789; }
        CompoundStmt stmt(moveValue(stmts));

        EXPECT_FALSE(stmt.isEmpty());
        EXPECT_EQ(2, stmt.getCount());
        EXPECT_EQ(2, stmt.getStatements().size());

        int count = 0;

        // begin/end
        for (auto it = stmt.begin(); it != stmt.end(); ++it)
        {
            ++count;
        }

        EXPECT_EQ(2, count);

        count = 0;

        // begin/end
        for (auto it = stmt.cbegin(); it != stmt.cend(); ++it)
        {
            ++count;
        }

        EXPECT_EQ(2, count);

        stmt.addStatement(ExprStmt::make());
        EXPECT_FALSE(stmt.isEmpty());
        EXPECT_EQ(3, stmt.getCount());
        EXPECT_EQ(3, stmt.getStatements().size());
    }
}

/* ************************************************************************ */

TEST(IfStmt, base)
{
    {
        // if (true) {}
        const IfStmt stmt(BoolLiteralExpr::make(true), CompoundStmt::make());

        EXPECT_EQ(StmtKind::If, stmt.getKind());
        EXPECT_TRUE(IfStmt::is(stmt));
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(BoolLiteralExpr::is(stmt.getCondExpr()));
        ASSERT_NE(nullptr, stmt.getThenStmt());
        EXPECT_TRUE(CompoundStmt::is(stmt.getThenStmt()));
        EXPECT_EQ(nullptr, stmt.getElseStmt());
    }

    {
        // if (true) {} else ;
        const IfStmt stmt(BoolLiteralExpr::make(true), CompoundStmt::make(), ExprStmt::make());

        EXPECT_EQ(StmtKind::If, stmt.getKind());
        EXPECT_TRUE(IfStmt::is(stmt));
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(BoolLiteralExpr::is(stmt.getCondExpr()));
        ASSERT_NE(nullptr, stmt.getThenStmt());
        EXPECT_TRUE(CompoundStmt::is(stmt.getThenStmt()));
        ASSERT_NE(nullptr, stmt.getElseStmt());
        EXPECT_TRUE(ExprStmt::is(stmt.getElseStmt()));
    }

    {
        // if (true) {} else ;
        IfStmt stmt(BoolLiteralExpr::make(true), CompoundStmt::make(), ExprStmt::make());

        EXPECT_EQ(StmtKind::If, stmt.getKind());
        EXPECT_TRUE(IfStmt::is(stmt));
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(BoolLiteralExpr::is(stmt.getCondExpr()));
        ASSERT_NE(nullptr, stmt.getThenStmt());
        EXPECT_TRUE(CompoundStmt::is(stmt.getThenStmt()));
        ASSERT_NE(nullptr, stmt.getElseStmt());
        EXPECT_TRUE(ExprStmt::is(stmt.getElseStmt()));

        // if (1) return;
        stmt.setCondExpr(IntLiteralExpr::make(1));
        stmt.setThenStmt(ReturnStmt::make());
        stmt.setElseStmt(nullptr);

        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(IntLiteralExpr::is(stmt.getCondExpr()));
        ASSERT_NE(nullptr, stmt.getThenStmt());
        EXPECT_TRUE(ReturnStmt::is(stmt.getThenStmt()));
        ASSERT_EQ(nullptr, stmt.getElseStmt());
    }
}

/* ************************************************************************ */

TEST(WhileStmt, base)
{
    {
        // while (true);
        const WhileStmt stmt(BoolLiteralExpr::make(true), ExprStmt::make());

        EXPECT_EQ(StmtKind::While, stmt.getKind());
        EXPECT_TRUE(WhileStmt::is(stmt));
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(BoolLiteralExpr::is(stmt.getCondExpr()));
        ASSERT_NE(nullptr, stmt.getBodyStmt());
        EXPECT_TRUE(ExprStmt::is(stmt.getBodyStmt()));
    }

    {
        // while (true);
        WhileStmt stmt(BoolLiteralExpr::make(true), ExprStmt::make());

        EXPECT_EQ(StmtKind::While, stmt.getKind());
        EXPECT_TRUE(WhileStmt::is(stmt));
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(BoolLiteralExpr::is(stmt.getCondExpr()));
        ASSERT_NE(nullptr, stmt.getBodyStmt());
        EXPECT_TRUE(ExprStmt::is(stmt.getBodyStmt()));

        // while (1) continue;
        stmt.setCondExpr(IntLiteralExpr::make(1));
        stmt.setBodyStmt(ContinueStmt::make());

        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(IntLiteralExpr::is(stmt.getCondExpr()));
        ASSERT_NE(nullptr, stmt.getBodyStmt());
        EXPECT_TRUE(ContinueStmt::is(stmt.getBodyStmt()));
    }
}

/* ************************************************************************ */

TEST(DoWhileStmt, base)
{
    {
        // do {} while (true);
        const DoWhileStmt stmt(BoolLiteralExpr::make(true), CompoundStmt::make());

        EXPECT_EQ(StmtKind::DoWhile, stmt.getKind());
        EXPECT_TRUE(DoWhileStmt::is(stmt));
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(BoolLiteralExpr::is(stmt.getCondExpr()));
        ASSERT_NE(nullptr, stmt.getBodyStmt());
        EXPECT_TRUE(CompoundStmt::is(stmt.getBodyStmt()));
    }

    {
        // do {} while (true);
        DoWhileStmt stmt(BoolLiteralExpr::make(true), CompoundStmt::make());

        EXPECT_EQ(StmtKind::DoWhile, stmt.getKind());
        EXPECT_TRUE(DoWhileStmt::is(stmt));
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(BoolLiteralExpr::is(stmt.getCondExpr()));
        ASSERT_NE(nullptr, stmt.getBodyStmt());
        EXPECT_TRUE(CompoundStmt::is(stmt.getBodyStmt()));

        // do { break; } while (false);
        stmt.setCondExpr(BoolLiteralExpr::make(false));

        auto body = CompoundStmt::make();
        body->addStatement(BreakStmt::make());

        stmt.setBodyStmt(moveValue(body));

        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(BoolLiteralExpr::is(stmt.getCondExpr()));
        EXPECT_FALSE(BoolLiteralExpr::cast(stmt.getCondExpr())->getValue());
        ASSERT_NE(nullptr, stmt.getBodyStmt());
        EXPECT_TRUE(CompoundStmt::is(stmt.getBodyStmt()));
        EXPECT_EQ(1, stmt.getBodyStmt()->getStatements().size());
    }
}

/* ************************************************************************ */

TEST(ForStmt, base)
{
    {
        // for (; true; ) {}
        const ForStmt stmt(ExprStmt::make(), BoolLiteralExpr::make(true), nullptr, CompoundStmt::make());

        EXPECT_EQ(StmtKind::For, stmt.getKind());
        EXPECT_TRUE(ForStmt::is(stmt));
        ASSERT_NE(nullptr, stmt.getInitStmt());
        EXPECT_TRUE(ExprStmt::is(stmt.getInitStmt()));
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(BoolLiteralExpr::is(stmt.getCondExpr()));
        EXPECT_EQ(nullptr, stmt.getIncExpr());
        ASSERT_TRUE(stmt.getBodyStmt());
        EXPECT_TRUE(CompoundStmt::is(stmt.getBodyStmt()));
    }

    {
        // for (; true; 5) {}
        const ForStmt stmt(ExprStmt::make(), BoolLiteralExpr::make(true), IntLiteralExpr::make(5), CompoundStmt::make());

        EXPECT_EQ(StmtKind::For, stmt.getKind());
        EXPECT_TRUE(ForStmt::is(stmt));
        ASSERT_NE(nullptr, stmt.getInitStmt());
        EXPECT_TRUE(ExprStmt::is(stmt.getInitStmt()));
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(BoolLiteralExpr::is(stmt.getCondExpr()));
        ASSERT_NE(nullptr, stmt.getIncExpr());
        EXPECT_TRUE(IntLiteralExpr::is(stmt.getIncExpr()));
        ASSERT_NE(nullptr, stmt.getBodyStmt());
        EXPECT_TRUE(CompoundStmt::is(stmt.getBodyStmt()));
    }

    {
        // for (; true; 5) {}
        ForStmt stmt(ExprStmt::make(), BoolLiteralExpr::make(true), IntLiteralExpr::make(5), CompoundStmt::make());

        EXPECT_EQ(StmtKind::For, stmt.getKind());
        EXPECT_TRUE(ForStmt::is(stmt));
        ASSERT_NE(nullptr, stmt.getInitStmt());
        EXPECT_TRUE(ExprStmt::is(stmt.getInitStmt()));
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(BoolLiteralExpr::is(stmt.getCondExpr()));
        ASSERT_NE(nullptr, stmt.getIncExpr());
        EXPECT_TRUE(IntLiteralExpr::is(stmt.getIncExpr()));
        ASSERT_NE(nullptr, stmt.getBodyStmt());
        EXPECT_TRUE(CompoundStmt::is(stmt.getBodyStmt()));

        // for (int i; 1; 2) continue
        stmt.setInitStmt(DeclStmt::make(VariableDecl::make(nullptr, &TYPE_BUILTIN_INT, "i")));
        stmt.setCondExpr(IntLiteralExpr::make(1));
        stmt.setIncExpr(IntLiteralExpr::make(2));
        stmt.setBodyStmt(ContinueStmt::make());

        ASSERT_NE(nullptr, stmt.getInitStmt());
        EXPECT_TRUE(DeclStmt::is(stmt.getInitStmt()));
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(IntLiteralExpr::is(stmt.getCondExpr()));
        ASSERT_NE(nullptr, stmt.getIncExpr());
        EXPECT_TRUE(IntLiteralExpr::is(stmt.getIncExpr()));
        ASSERT_NE(nullptr, stmt.getBodyStmt());
        EXPECT_TRUE(ContinueStmt::is(stmt.getBodyStmt()));
    }
}

/* ************************************************************************ */

TEST(SwitchStmt, base)
{
    {
        // switch (id) {}
        const SwitchStmt stmt(IdentifierExpr::make("id"), CompoundStmt::make());

        EXPECT_EQ(StmtKind::Switch, stmt.getKind());
        EXPECT_TRUE(SwitchStmt::is(stmt));
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(IdentifierExpr::is(stmt.getCondExpr()));
        ASSERT_NE(nullptr, stmt.getBodyStmt());
        EXPECT_TRUE(CompoundStmt::is(stmt.getBodyStmt()));
    }

    {
        // switch (id) {}
        SwitchStmt stmt(IdentifierExpr::make("id"), CompoundStmt::make());

        EXPECT_EQ(StmtKind::Switch, stmt.getKind());
        EXPECT_TRUE(SwitchStmt::is(stmt));
        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(IdentifierExpr::is(stmt.getCondExpr()));
        ASSERT_NE(nullptr, stmt.getBodyStmt());
        EXPECT_TRUE(CompoundStmt::is(stmt.getBodyStmt()));

        // swich (type) { case 1: break; }
        stmt.setCondExpr(IdentifierExpr::make("type"));

        auto body = CompoundStmt::make();
        auto caseStmt = CaseStmt::make(IntLiteralExpr::make(1));

        caseStmt->addStmt(BreakStmt::make());

        body->addStatement(moveValue(caseStmt));

        stmt.setBodyStmt(moveValue(body));

        ASSERT_NE(nullptr, stmt.getCondExpr());
        EXPECT_TRUE(IdentifierExpr::is(stmt.getCondExpr()));
        ASSERT_NE(nullptr, stmt.getBodyStmt());
        EXPECT_TRUE(CompoundStmt::is(stmt.getBodyStmt()));
        EXPECT_EQ(1, stmt.getBodyStmt()->getStatements().size());
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
        EXPECT_TRUE(CaseStmt::is(stmt));
        ASSERT_NE(nullptr, stmt.getExpr());
        EXPECT_TRUE(IntLiteralExpr::is(stmt.getExpr()));
        ASSERT_NE(nullptr, stmt.getBody());
        //EXPECT_TRUE(ExprStmt::is(stmt.getBody()));
    }

    {
        // case 0: ;
        CaseStmt stmt(IntLiteralExpr::make(0));

        stmt.addStmt(ExprStmt::make());

        EXPECT_EQ(StmtKind::Case, stmt.getKind());
        EXPECT_TRUE(CaseStmt::is(stmt));
        ASSERT_NE(nullptr, stmt.getExpr());
        EXPECT_TRUE(IntLiteralExpr::is(stmt.getExpr()));
        ASSERT_NE(nullptr, stmt.getBody());
        //EXPECT_TRUE(ExprStmt::is(stmt.getBody()));

        // case "val": break;
        stmt.setExpr(StringLiteralExpr::make("val"));
        stmt.addStmt(BreakStmt::make());

        ASSERT_NE(nullptr, stmt.getExpr());
        EXPECT_TRUE(StringLiteralExpr::is(stmt.getExpr()));
        ASSERT_NE(nullptr, stmt.getBody());
        //EXPECT_TRUE(BreakStmt::is(stmt.getBody()));
        EXPECT_EQ(2, stmt.getBody()->size());
    }
}

/* ************************************************************************ */

TEST(DefaultStmt, base)
{
    {
        // default: ;
        DefaultStmt stmt;

        stmt.addStmt(ExprStmt::make());

        EXPECT_EQ(StmtKind::Default, stmt.getKind());
        EXPECT_TRUE(DefaultStmt::is(stmt));
        ASSERT_NE(nullptr, stmt.getBody());
        //EXPECT_TRUE(ExprStmt::is(stmt.getBody()));
    }

    {
        // default: ;
        DefaultStmt stmt;

        stmt.addStmt(ExprStmt::make());

        EXPECT_EQ(StmtKind::Default, stmt.getKind());
        EXPECT_TRUE(DefaultStmt::is(stmt));
        ASSERT_NE(nullptr, stmt.getBody());
        //EXPECT_TRUE(ExprStmt::is(stmt.getBody()));

        // default: break;
        stmt.addStmt(BreakStmt::make());

        ASSERT_NE(nullptr, stmt.getBody());
        //EXPECT_TRUE(BreakStmt::is(stmt.getBody()));
        EXPECT_EQ(2, stmt.getBody()->size());
    }
}

/* ************************************************************************ */

TEST(ContinueStmt, base)
{
    {
        // continue;
        const ContinueStmt stmt;

        EXPECT_EQ(StmtKind::Continue, stmt.getKind());
        EXPECT_TRUE(ContinueStmt::is(stmt));
    }
}

/* ************************************************************************ */

TEST(BreakStmt, base)
{
    {
        // break;
        const BreakStmt stmt;

        EXPECT_EQ(StmtKind::Break, stmt.getKind());
        EXPECT_TRUE(BreakStmt::is(stmt));
    }
}

/* ************************************************************************ */

TEST(ReturnStmt, base)
{
    {
        // return;
        const ReturnStmt stmt;

        EXPECT_EQ(StmtKind::Return, stmt.getKind());
        EXPECT_TRUE(ReturnStmt::is(stmt));
        ASSERT_EQ(nullptr, stmt.getResExpr());
    }

    {
        // return true;
        const ReturnStmt stmt(BoolLiteralExpr::make(true));

        EXPECT_EQ(StmtKind::Return, stmt.getKind());
        EXPECT_TRUE(ReturnStmt::is(stmt));
        ASSERT_NE(nullptr, stmt.getResExpr());
        EXPECT_TRUE(BoolLiteralExpr::is(stmt.getResExpr()));
    }


    {
        // return;
        ReturnStmt stmt;

        EXPECT_EQ(StmtKind::Return, stmt.getKind());
        EXPECT_TRUE(ReturnStmt::is(stmt));
        ASSERT_EQ(nullptr, stmt.getResExpr());

        // return 1.1;
        stmt.setResExpr(FloatLiteralExpr::make(1.1));

        ASSERT_NE(nullptr, stmt.getResExpr());
        EXPECT_TRUE(FloatLiteralExpr::is(stmt.getResExpr()));
    }
}

/* ************************************************************************ */

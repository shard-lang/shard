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
#include "shard/ast/stmt/SwitchStmt.hpp"
#include "shard/ast/stmt/CompoundStmt.hpp"
#include "shard/ast/stmt/CaseStmt.hpp"
#include "shard/ast/stmt/BreakStmt.hpp"
#include "shard/ast/expr/IdentifierExpr.hpp"
#include "shard/ast/expr/IntLiteralExpr.hpp"
#include "shard/ast/Decl.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

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

        body->addStmt(std::move(caseStmt));

        stmt.setBodyStmt(std::move(body));

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

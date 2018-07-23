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
#include "shard/ast/Source.hpp"
#include "shard/ast/utility.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

namespace {

/* ************************************************************************ */

struct TestStmt : public Stmt, public PtrBuilder<TestStmt>
{
    TestStmt(SourceRange range = {}) noexcept
        : Stmt(StmtKind::Expr, range) {}
};

/* ************************************************************************ */

struct TestStmt2 : public Stmt, public PtrBuilder<TestStmt2>
{
    TestStmt2(SourceRange range = {}) noexcept
        : Stmt(StmtKind::Expr, range) {}
};

/* ************************************************************************ */

}

/* ************************************************************************ */

TEST(Source, basic)
{
    Source source;

    source.addStmt(TestStmt::make());
    source.addStmt(TestStmt2::make());

    ASSERT_EQ(2, source.stmts().size());
    EXPECT_TRUE(source.stmts()[0]->is<TestStmt>());
    EXPECT_TRUE(source.stmts()[1]->is<TestStmt2>());

    StmtPtrVector stmts;
    stmts.push_back(TestStmt2::make());

    source = Source(std::move(stmts));

    ASSERT_EQ(1, source.stmts().size());
    EXPECT_TRUE(source.stmts()[0]->is<TestStmt2>());

    stmts.push_back(TestStmt::make());

    source.setStmts(std::move(stmts));

    ASSERT_EQ(1, source.stmts().size());
    EXPECT_TRUE(source.stmts()[0]->is<TestStmt>());
}

/* ************************************************************************ */
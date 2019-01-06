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
        : Stmt(range)
    {
        // Nothing
    }
};

/* ************************************************************************ */

struct TestStmt2 : public Stmt
{
    // Nothing
};

/* ************************************************************************ */

} // namespace

/* ************************************************************************ */

TEST(Stmt, basic)
{
    TestStmt stmt;

    EXPECT_TRUE(stmt.is<TestStmt>());
    EXPECT_FALSE(stmt.is<TestStmt2>());
}

/* ************************************************************************ */

TEST(Stmt, vtable)
{
    StmtPtr stmt = TestStmt::make();

    EXPECT_TRUE(stmt->is<TestStmt>());
    EXPECT_FALSE(stmt->is<TestStmt2>());
}

/* ************************************************************************ */
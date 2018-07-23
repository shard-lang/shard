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
#include "shard/ast/stmt/DeclStmt.hpp"
#include "shard/ast/Expr.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

namespace {

/* ************************************************************************ */

struct TestDecl : Decl, public PtrBuilder<TestDecl, String>
{
    TestDecl(String name, SourceRange range) : Decl(DeclKind::Variable, std::move(name), range) {}
};

/* ************************************************************************ */

struct TestDecl2 : Decl
{

};

/* ************************************************************************ */

}

/* ************************************************************************ */

TEST(DeclStmt, base)
{
    {
        // int foo;
        const DeclStmt stmt(TestDecl::make("foo"));

        EXPECT_TRUE(stmt.is<DeclStmt>());
        ASSERT_NE(nullptr, stmt.decl());
        ASSERT_TRUE(stmt.decl()->is<TestDecl>());
        ASSERT_FALSE(stmt.decl()->is<TestDecl2>());
    }

    {
        DeclStmt stmt(TestDecl::make("foo"));

        EXPECT_TRUE(stmt.is<DeclStmt>());
        ASSERT_NE(nullptr, stmt.decl());
        ASSERT_TRUE(stmt.decl()->is<TestDecl>());
        ASSERT_EQ("foo", stmt.decl()->cast<TestDecl>().name());
        ASSERT_EQ("foo", stmt.decl<TestDecl>().name());
    }

    {
        const auto stmt = DeclStmt::make(TestDecl::make("foo"));

        EXPECT_TRUE(stmt->is<DeclStmt>());
        ASSERT_NE(nullptr, stmt->decl());
        ASSERT_TRUE(stmt->decl()->is<TestDecl>());
    }
}

/* ************************************************************************ */

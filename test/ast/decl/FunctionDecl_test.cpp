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
#include "shard/ast/Expr.hpp"
#include "shard/ast/decl/FunctionDecl.hpp"
#include "shard/ast/decl/VariableDecl.hpp"
#include "shard/ast/stmt/CompoundStmt.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

TEST(FunctionDecl, base)
{
    {
        // int foo() {}
        const FunctionDecl decl("int", "foo", makeUnique<CompoundStmt>(), {});

        EXPECT_TRUE(decl.is<FunctionDecl>());
        EXPECT_EQ("foo", decl.name());
        EXPECT_EQ("int", decl.retType());
        EXPECT_TRUE(decl.parameters().empty());
        ASSERT_NE(nullptr, decl.bodyStmt());
        EXPECT_TRUE(decl.bodyStmt()->is<CompoundStmt>());
    }

    {
        // int foo() {}
        FunctionDecl decl("int", "foo", makeUnique<CompoundStmt>());

        EXPECT_TRUE(decl.is<FunctionDecl>());
        EXPECT_EQ("foo", decl.name());
        EXPECT_EQ("int", decl.retType());
        EXPECT_TRUE(decl.parameters().empty());
        ASSERT_NE(nullptr, decl.bodyStmt());
        EXPECT_TRUE(decl.bodyStmt()->is<CompoundStmt>());

        // int bar() {}
        decl.setName("bar");
        EXPECT_EQ("bar", decl.name());
        EXPECT_EQ("int", decl.retType());
        EXPECT_TRUE(decl.parameters().empty());
        ASSERT_NE(nullptr, decl.bodyStmt());
        EXPECT_TRUE(decl.bodyStmt()->is<CompoundStmt>());

        // void bar() {}
        decl.setRetType("void");
        EXPECT_EQ("bar", decl.name());
        EXPECT_EQ("void", decl.retType());
        EXPECT_TRUE(decl.parameters().empty());
        ASSERT_NE(nullptr, decl.bodyStmt());
        EXPECT_TRUE(decl.bodyStmt()->is<CompoundStmt>());

        // void bar(int x, int y) {}
        PtrVector<VariableDecl> params;
        params.push_back(VariableDecl::make("int", "x", nullptr));
        params.push_back(VariableDecl::make("int", "y", nullptr));
        decl.setParameters(std::move(params));
        EXPECT_EQ("bar", decl.name());
        EXPECT_EQ("void", decl.retType());
        EXPECT_FALSE(decl.parameters().empty());
        ASSERT_EQ(2, decl.parameters().size());
        ASSERT_TRUE(decl.parameters()[0]->is<VariableDecl>());
        ASSERT_TRUE(decl.parameters()[1]->is<VariableDecl>());
        EXPECT_EQ("x", decl.parameters()[0]->name());
        EXPECT_EQ("y", decl.parameters()[1]->name());

        decl.setBodyStmt(makeUnique<CompoundStmt>());
        ASSERT_NE(nullptr, decl.bodyStmt());
        EXPECT_TRUE(decl.bodyStmt()->is<CompoundStmt>());
    }

    {
        // int foo() {}
        const auto decl =
            FunctionDecl::make("int", "foo", makeUnique<CompoundStmt>(), {});

        EXPECT_TRUE(decl->is<FunctionDecl>());
        EXPECT_EQ("foo", decl->name());
        EXPECT_EQ("int", decl->retType());
        EXPECT_TRUE(decl->parameters().empty());
        ASSERT_NE(nullptr, decl->bodyStmt());
        EXPECT_TRUE(decl->bodyStmt()->is<CompoundStmt>());
    }
}

/* ************************************************************************ */

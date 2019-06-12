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
#include "shard/ast/decl/VariableDecl.hpp"
#include "shard/ast/expr/StringLiteralExpr.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

TEST(VariableDecl, base)
{
    {
        // int foo;
        const VariableDecl decl("int", "foo");

        EXPECT_TRUE(decl.is<VariableDecl>());
        EXPECT_EQ("foo", decl.name());
        EXPECT_EQ("int", decl.type());
    }

    {
        // string foo = "bar";
        const VariableDecl decl(
            "string", "foo2", StringLiteralExpr::make("bar"));

        EXPECT_TRUE(decl.is<VariableDecl>());
        EXPECT_EQ("foo2", decl.name());
        EXPECT_EQ("string", decl.type());
        ASSERT_NE(nullptr, decl.initExpr());
        ASSERT_TRUE(decl.initExpr()->is<StringLiteralExpr>());
        EXPECT_EQ("bar", decl.initExpr<StringLiteralExpr>().value());
    }

    {
        // int foo;
        VariableDecl decl("int", "foo");

        EXPECT_TRUE(decl.is<VariableDecl>());
        EXPECT_EQ("foo", decl.name());
        EXPECT_EQ("int", decl.type());
        EXPECT_EQ(nullptr, decl.initExpr());

        // int foo2;
        decl.setName("foo2");
        EXPECT_EQ("foo2", decl.name());
        EXPECT_EQ("int", decl.type());
        EXPECT_EQ(nullptr, decl.initExpr());

        // float foo2;
        decl.setType("float");
        EXPECT_EQ("foo2", decl.name());
        EXPECT_EQ("float", decl.type());
        EXPECT_EQ(nullptr, decl.initExpr());

        // string foo2;
        decl.setType("string");
        EXPECT_EQ("foo2", decl.name());
        EXPECT_EQ("string", decl.type());
        EXPECT_EQ(nullptr, decl.initExpr());

        // string foo2 = "Hello";
        decl.setInitExpr(StringLiteralExpr::make("Hello"));
        ASSERT_NE(nullptr, decl.initExpr());
        ASSERT_TRUE(decl.initExpr()->is<StringLiteralExpr>());
        EXPECT_EQ("Hello", decl.initExpr<StringLiteralExpr>().value());
    }

    {
        // int foo;
        const auto decl = VariableDecl::make("int", "foo", nullptr);

        EXPECT_TRUE(decl->is<VariableDecl>());
        EXPECT_EQ("foo", decl->name());
        EXPECT_EQ("int", decl->type());
    }
}

/* ************************************************************************ */

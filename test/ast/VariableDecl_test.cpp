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
#include "shard/ast/VariableDecl.hpp"
#include "shard/ast/Type.hpp"
#include "shard/ast/Expr.hpp"
#include "shard/ast/Stmt.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

TEST(VariableDecl, base)
{
    {
        // int foo;
        const VariableDecl decl(TypeKind::Int, "foo");

        EXPECT_EQ(DeclKind::Variable, decl.getKind());
        EXPECT_TRUE(decl.is<VariableDecl>());
        EXPECT_EQ("foo", decl.getName());
        EXPECT_EQ(TypeKind::Int, decl.getType());
    }

    {
        // string foo = "bar";
        const VariableDecl decl(TypeKind::String, "foo2", StringLiteralExpr::make("bar"));

        EXPECT_EQ(DeclKind::Variable, decl.getKind());
        EXPECT_TRUE(decl.is<VariableDecl>());
        EXPECT_EQ("foo2", decl.getName());
        EXPECT_EQ(TypeKind::String, decl.getType());
        ASSERT_NE(nullptr, decl.getInitExpr());
        ASSERT_TRUE(decl.getInitExpr()->is<StringLiteralExpr>());
        EXPECT_EQ("bar", decl.getInitExpr()->cast<StringLiteralExpr>().getValue());
    }

    {
        // int foo;
        VariableDecl decl(TypeKind::Int, "foo");

        EXPECT_EQ(DeclKind::Variable, decl.getKind());
        EXPECT_TRUE(decl.is<VariableDecl>());
        EXPECT_EQ("foo", decl.getName());
        EXPECT_EQ(TypeKind::Int, decl.getType());
        EXPECT_EQ(nullptr, decl.getInitExpr());

        // int foo2;
        decl.setName("foo2");
        EXPECT_EQ("foo2", decl.getName());
        EXPECT_EQ(TypeKind::Int, decl.getType());
        EXPECT_EQ(nullptr, decl.getInitExpr());

        // float foo2;
        decl.setType(TypeKind::Float);
        EXPECT_EQ("foo2", decl.getName());
        EXPECT_EQ(TypeKind::Float, decl.getType());
        EXPECT_EQ(nullptr, decl.getInitExpr());

        // string foo2;
        decl.setType(TypeKind::String);
        EXPECT_EQ("foo2", decl.getName());
        EXPECT_EQ(TypeKind::String, decl.getType());
        EXPECT_EQ(nullptr, decl.getInitExpr());

        // string foo2 = "Hello";
        decl.setInitExpr(StringLiteralExpr::make("Hello"));
        ASSERT_NE(nullptr, decl.getInitExpr());
        ASSERT_TRUE(decl.getInitExpr()->is<StringLiteralExpr>());
        EXPECT_EQ("Hello", decl.getInitExpr()->cast<StringLiteralExpr>().getValue());
    }

    {
        // int foo;
        const auto decl = VariableDecl::make(TypeKind::Int, "foo");

        EXPECT_EQ(DeclKind::Variable, decl->getKind());
        EXPECT_TRUE(decl->is<VariableDecl>());
        EXPECT_EQ("foo", decl->getName());
        EXPECT_EQ(TypeKind::Int, decl->getType());
    }
}

/* ************************************************************************ */

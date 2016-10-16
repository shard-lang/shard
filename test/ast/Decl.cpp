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
#include "shard/ast/Decl.hpp"
#include "shard/ast/DeclContext.hpp"
#include "shard/ast/Type.hpp"
#include "shard/ast/Expr.hpp"
#include "shard/ast/Stmt.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

TEST(VariableDecl, construction)
{
    {
        // int foo;
        DeclContext ctx;
        const VariableDecl decl(&ctx, "foo", {&TYPE_BUILTIN_INT});

        EXPECT_EQ(DeclKind::Variable, decl.getKind());
        EXPECT_TRUE(NamedDecl::is(decl));
        EXPECT_TRUE(VariableDecl::is(decl));
        EXPECT_EQ("foo", decl.getName());
        EXPECT_EQ(&TYPE_BUILTIN_INT, decl.getType());

        // Find declaration
        auto dcl = ctx.findDeclaration("foo");
        ASSERT_TRUE(dcl);
        EXPECT_TRUE(NamedDecl::is(dcl));
        EXPECT_TRUE(VariableDecl::is(dcl));
        EXPECT_EQ("foo", dcl->getName());
        EXPECT_EQ(&decl, dcl);
    }

    {
        // string foo = "bar";
        const VariableDecl decl(nullptr, "foo2", {&TYPE_BUILTIN_STRING}, makeUnique<StringLiteralExpr>("bar"));

        EXPECT_EQ(DeclKind::Variable, decl.getKind());
        EXPECT_TRUE(VariableDecl::is(decl));
        EXPECT_EQ("foo2", decl.getName());
        EXPECT_EQ(&TYPE_BUILTIN_STRING, decl.getType());
        ASSERT_TRUE(decl.getInitializer());
        ASSERT_TRUE(StringLiteralExpr::is(decl.getInitializer()));
        EXPECT_EQ("bar", StringLiteralExpr::cast(decl.getInitializer())->getValue());
    }
}

/* ************************************************************************ */

TEST(FunctionDecl, construction)
{
    {
        // int foo() {}
        DeclContext ctx;
        const FunctionDecl decl(&ctx, "foo", {&TYPE_BUILTIN_INT}, {}, makeUnique<CompoundStmt>());

        EXPECT_EQ(DeclKind::Function, decl.getKind());
        EXPECT_TRUE(NamedDecl::is(decl));
        EXPECT_TRUE(FunctionDecl::is(decl));
        EXPECT_EQ("foo", decl.getName());
        EXPECT_EQ(&TYPE_BUILTIN_INT, decl.getRetType());

        // Find declaration
        auto dcl = ctx.findDeclaration("foo");
        ASSERT_TRUE(dcl);
        EXPECT_TRUE(NamedDecl::is(dcl));
        EXPECT_TRUE(FunctionDecl::is(dcl));
        EXPECT_EQ("foo", dcl->getName());
        EXPECT_EQ(&decl, dcl);
    }
}

/* ************************************************************************ */

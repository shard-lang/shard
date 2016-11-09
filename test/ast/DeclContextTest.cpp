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
#include "shard/ast/DeclContext.hpp"
#include "shard/ast/Decl.hpp"
#include "shard/ast/Expr.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

TEST(DeclContext, construction)
{
    DeclContext ctx;
    DeclContext ctx2(makeView(&ctx));

    EXPECT_EQ(nullptr, ctx.getParent());
    EXPECT_EQ(0, ctx.getDeclarations().size());

    EXPECT_EQ(&ctx, ctx2.getParent());
    EXPECT_EQ(0, ctx2.getDeclarations().size());
}

/* ************************************************************************ */

TEST(DeclContext, declarations)
{
    DeclContext ctx;
    DeclContext ctx2(makeView(&ctx));

    // int foo;
    ctx.createDeclaration<VariableDecl>("foo", TypeInfo{&TYPE_BUILTIN_INT});

    // int bar;
    ctx2.createDeclaration<VariableDecl>("bar", TypeInfo{&TYPE_BUILTIN_INT});

    EXPECT_EQ(1, ctx.getDeclarations().size());
    EXPECT_EQ(1, ctx2.getDeclarations().size());

    // Find declarations
    auto foo = ctx.findDeclaration("foo");
    ASSERT_NE(nullptr, foo);
    EXPECT_TRUE(VariableDecl::is(foo));
    EXPECT_EQ("foo", foo->getName());

    // Not defined in ctx
    ASSERT_EQ(nullptr, ctx.findDeclaration("bar"));

    auto bar = ctx2.findDeclaration("bar");
    ASSERT_NE(nullptr, bar);
    EXPECT_TRUE(VariableDecl::is(bar));
    EXPECT_EQ("bar", bar->getName());

    // Recursive search
    auto foo2 = ctx2.findDeclaration("foo");
    ASSERT_NE(nullptr, foo2);
    EXPECT_EQ(foo, foo2);
    EXPECT_TRUE(VariableDecl::is(foo2));
    EXPECT_EQ("foo", foo2->getName());

    // Remove declaration
    ctx.removeDeclaration(foo);
    ASSERT_EQ(nullptr, ctx.findDeclaration("foo"));
    ASSERT_EQ(nullptr, ctx2.findDeclaration("foo"));
}

/* ************************************************************************ */

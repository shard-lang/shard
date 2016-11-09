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
        const VariableDecl decl(nullptr, "foo", {&TYPE_BUILTIN_INT});

        EXPECT_EQ(DeclKind::Variable, decl.getKind());
        EXPECT_TRUE(NamedDecl::is(decl));
        EXPECT_TRUE(VariableDecl::is(decl));
        EXPECT_EQ("foo", decl.getName());
        EXPECT_EQ(&TYPE_BUILTIN_INT, decl.getType());
    }

    {
        // string foo = "bar";
        const VariableDecl decl(nullptr, "foo2", {&TYPE_BUILTIN_STRING}, makeUnique<StringLiteralExpr>("bar"));

        EXPECT_EQ(DeclKind::Variable, decl.getKind());
        EXPECT_TRUE(VariableDecl::is(decl));
        EXPECT_EQ("foo2", decl.getName());
        EXPECT_EQ(&TYPE_BUILTIN_STRING, decl.getType());
        ASSERT_NE(nullptr, decl.getInitExpr());
        ASSERT_TRUE(StringLiteralExpr::is(decl.getInitExpr()));
        EXPECT_EQ("bar", StringLiteralExpr::cast(decl.getInitExpr())->getValue());
    }
}

/* ************************************************************************ */

TEST(VariableDecl, modify)
{
    // int foo;
    VariableDecl decl(nullptr, "foo", {&TYPE_BUILTIN_INT});

    EXPECT_EQ(DeclKind::Variable, decl.getKind());
    EXPECT_TRUE(NamedDecl::is(decl));
    EXPECT_TRUE(VariableDecl::is(decl));
    EXPECT_EQ("foo", decl.getName());
    EXPECT_EQ(&TYPE_BUILTIN_INT, decl.getType());
    ASSERT_EQ(nullptr, decl.getInitExpr());

    // int foo2;
    decl.setName("foo2");
    EXPECT_EQ("foo2", decl.getName());

    // float foo2;
    decl.setTypeInfo({&TYPE_BUILTIN_FLOAT});
    EXPECT_EQ(&TYPE_BUILTIN_FLOAT, decl.getType());

    // string foo2;
    decl.setType(&TYPE_BUILTIN_STRING);
    EXPECT_EQ(&TYPE_BUILTIN_STRING, decl.getType());

    // string foo2 = "Hello";
    decl.setInitExpr(makeUnique<StringLiteralExpr>("Hello"));
    ASSERT_NE(nullptr, decl.getInitExpr());
    ASSERT_TRUE(StringLiteralExpr::is(decl.getInitExpr()));
    EXPECT_EQ("Hello", StringLiteralExpr::cast(decl.getInitExpr())->getValue());
}

/* ************************************************************************ */

TEST(FunctionDecl, construction)
{
    {
        // int foo() {}
        const FunctionDecl decl(nullptr, "foo", TypeInfo{&TYPE_BUILTIN_INT}, makeUnique<CompoundStmt>());

        EXPECT_EQ(DeclKind::Function, decl.getKind());
        EXPECT_TRUE(NamedDecl::is(decl));
        EXPECT_TRUE(FunctionDecl::is(decl));
        EXPECT_EQ("foo", decl.getName());
        EXPECT_EQ(&TYPE_BUILTIN_INT, decl.getRetType());
    }
}

/* ************************************************************************ */

TEST(ClassDecl, construction)
{
    {
        // class Foo {}
        const ClassDecl decl(nullptr, "Foo");

        EXPECT_EQ(DeclKind::Class, decl.getKind());
        EXPECT_TRUE(NamedDecl::is(decl));
        EXPECT_TRUE(ClassDecl::is(decl));
        EXPECT_EQ("Foo", decl.getName());
    }
}

/* ************************************************************************ */

TEST(ClassDecl, declarations)
{
    {
        // class Point { int x; int y; }
        ClassDecl decl(nullptr, "Point");

        decl.createDeclaration<VariableDecl>("x", TypeInfo{&TYPE_BUILTIN_INT});
        decl.createDeclaration<VariableDecl>("y", TypeInfo{&TYPE_BUILTIN_INT});

        EXPECT_EQ(2, decl.getDeclarations().size());
    }
}

/* ************************************************************************ */

TEST(NamespaceDecl, construction)
{
    {
        // namespace foo {}
        // namespace foo:
        const NamespaceDecl decl(nullptr, "foo");

        EXPECT_EQ(DeclKind::Namespace, decl.getKind());
        EXPECT_TRUE(NamedDecl::is(decl));
        EXPECT_TRUE(NamespaceDecl::is(decl));
        EXPECT_EQ("foo", decl.getName());
    }
}

/* ************************************************************************ */

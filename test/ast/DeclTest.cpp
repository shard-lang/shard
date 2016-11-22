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

TEST(VariableDecl, base)
{
    {
        // int foo;
        const VariableDecl decl(nullptr, TypeInfo{&TYPE_BUILTIN_INT}, "foo");

        EXPECT_EQ(nullptr, decl.getContext());
        EXPECT_EQ(DeclKind::Variable, decl.getKind());
        EXPECT_TRUE(NamedDecl::is(decl));
        EXPECT_TRUE(VariableDecl::is(decl));
        EXPECT_EQ("foo", decl.getName());
        EXPECT_EQ(&TYPE_BUILTIN_INT, decl.getTypeInfo().getType());
        EXPECT_EQ(&TYPE_BUILTIN_INT, decl.getType());
    }

    {
        // string foo = "bar";
        const VariableDecl decl(nullptr, &TYPE_BUILTIN_STRING, "foo2", StringLiteralExpr::make("bar"));

        EXPECT_EQ(nullptr, decl.getContext());
        EXPECT_EQ(DeclKind::Variable, decl.getKind());
        EXPECT_TRUE(VariableDecl::is(decl));
        EXPECT_EQ("foo2", decl.getName());
        EXPECT_EQ(&TYPE_BUILTIN_STRING, decl.getTypeInfo().getType());
        EXPECT_EQ(&TYPE_BUILTIN_STRING, decl.getType());
        ASSERT_NE(nullptr, decl.getInitExpr());
        ASSERT_TRUE(StringLiteralExpr::is(decl.getInitExpr()));
        EXPECT_EQ("bar", StringLiteralExpr::cast(decl.getInitExpr())->getValue());
    }

    {
        // int foo;
        VariableDecl decl(nullptr, &TYPE_BUILTIN_INT, "foo");

        EXPECT_EQ(nullptr, decl.getContext());
        EXPECT_EQ(DeclKind::Variable, decl.getKind());
        EXPECT_TRUE(NamedDecl::is(decl));
        EXPECT_TRUE(VariableDecl::is(decl));
        EXPECT_EQ("foo", decl.getName());
        EXPECT_EQ(&TYPE_BUILTIN_INT, decl.getType());
        EXPECT_EQ(nullptr, decl.getInitExpr());

        // int foo2;
        decl.setName("foo2");
        EXPECT_EQ("foo2", decl.getName());
        EXPECT_EQ(&TYPE_BUILTIN_INT, decl.getType());
        EXPECT_EQ(nullptr, decl.getInitExpr());

        // float foo2;
        decl.setTypeInfo({&TYPE_BUILTIN_FLOAT});
        EXPECT_EQ("foo2", decl.getName());
        EXPECT_EQ(&TYPE_BUILTIN_FLOAT, decl.getType());
        EXPECT_EQ(nullptr, decl.getInitExpr());

        // string foo2;
        decl.setType(&TYPE_BUILTIN_STRING);
        EXPECT_EQ("foo2", decl.getName());
        EXPECT_EQ(&TYPE_BUILTIN_STRING, decl.getType());
        EXPECT_EQ(nullptr, decl.getInitExpr());

        // string foo2 = "Hello";
        decl.setInitExpr(StringLiteralExpr::make("Hello"));
        ASSERT_NE(nullptr, decl.getInitExpr());
        ASSERT_TRUE(StringLiteralExpr::is(decl.getInitExpr()));
        EXPECT_EQ("Hello", StringLiteralExpr::cast(decl.getInitExpr())->getValue());
    }
}

/* ************************************************************************ */

TEST(FunctionDecl, base)
{
    {
        // int foo() {}
        const FunctionDecl decl(nullptr, TypeInfo{&TYPE_BUILTIN_INT}, "foo", makeUnique<CompoundStmt>());

        EXPECT_EQ(DeclKind::Function, decl.getKind());
        EXPECT_TRUE(NamedDecl::is(decl));
        EXPECT_TRUE(FunctionDecl::is(decl));
        EXPECT_EQ("foo", decl.getName());
        EXPECT_EQ(&TYPE_BUILTIN_INT, decl.getRetType());
        EXPECT_EQ(&TYPE_BUILTIN_INT, decl.getRetTypeInfo().getType());
        EXPECT_TRUE(decl.getParameters().empty());
        ASSERT_NE(nullptr, decl.getBodyStmt());
        EXPECT_TRUE(CompoundStmt::is(decl.getBodyStmt()));
    }

    {
        // int foo() {}
        FunctionDecl decl(nullptr, TypeInfo{&TYPE_BUILTIN_INT}, "foo", makeUnique<CompoundStmt>());

        EXPECT_EQ(DeclKind::Function, decl.getKind());
        EXPECT_TRUE(NamedDecl::is(decl));
        EXPECT_TRUE(FunctionDecl::is(decl));
        EXPECT_EQ("foo", decl.getName());
        EXPECT_EQ(&TYPE_BUILTIN_INT, decl.getRetTypeInfo().getType());
        EXPECT_EQ(&TYPE_BUILTIN_INT, decl.getRetType());
        EXPECT_TRUE(decl.getParameters().empty());
        ASSERT_NE(nullptr, decl.getBodyStmt());
        EXPECT_TRUE(CompoundStmt::is(decl.getBodyStmt()));

        // int bar() {}
        decl.setName("bar");
        EXPECT_EQ("bar", decl.getName());
        EXPECT_EQ(&TYPE_BUILTIN_INT, decl.getRetTypeInfo().getType());
        EXPECT_EQ(&TYPE_BUILTIN_INT, decl.getRetType());
        EXPECT_TRUE(decl.getParameters().empty());
        ASSERT_NE(nullptr, decl.getBodyStmt());
        EXPECT_TRUE(CompoundStmt::is(decl.getBodyStmt()));

        // void bar() {}
        decl.setRetType(&TYPE_BUILTIN_VOID);
        EXPECT_EQ("bar", decl.getName());
        EXPECT_EQ(&TYPE_BUILTIN_VOID, decl.getRetTypeInfo().getType());
        EXPECT_EQ(&TYPE_BUILTIN_VOID, decl.getRetType());
        EXPECT_TRUE(decl.getParameters().empty());
        ASSERT_NE(nullptr, decl.getBodyStmt());
        EXPECT_TRUE(CompoundStmt::is(decl.getBodyStmt()));

        // void bar() {}
        decl.setRetTypeInfo({&TYPE_BUILTIN_VOID});
        EXPECT_EQ("bar", decl.getName());
        EXPECT_EQ(&TYPE_BUILTIN_VOID, decl.getRetType());
        EXPECT_TRUE(decl.getParameters().empty());
        ASSERT_NE(nullptr, decl.getBodyStmt());
        EXPECT_TRUE(CompoundStmt::is(decl.getBodyStmt()));

        // void bar(int x, int y) {}
        PtrDynamicArray<VariableDecl> params;
        params.push_back(VariableDecl::make(nullptr, &TYPE_BUILTIN_INT, "x"));
        params.push_back(VariableDecl::make(nullptr, &TYPE_BUILTIN_INT, "y"));
        decl.setParameters(moveValue(params));
        EXPECT_EQ("bar", decl.getName());
        EXPECT_EQ(&TYPE_BUILTIN_VOID, decl.getRetType());
        EXPECT_FALSE(decl.getParameters().empty());
        ASSERT_EQ(2, decl.getParameters().size());
        ASSERT_TRUE(VariableDecl::is(decl.getParameters()[0]));
        ASSERT_TRUE(VariableDecl::is(decl.getParameters()[1]));
        //EXPECT_EQ("x", VariableDecl::cast(decl.getParameters()[0])->getName());
        //EXPECT_EQ("y", VariableDecl::cast(decl.getParameters()[1])->getName());

        decl.setBodyStmt(makeUnique<CompoundStmt>());
        ASSERT_NE(nullptr, decl.getBodyStmt());
        EXPECT_TRUE(CompoundStmt::is(decl.getBodyStmt()));
    }
}

/* ************************************************************************ */

TEST(ClassDecl, base)
{
    {
        // class Foo {}
        const ClassDecl decl(nullptr, "Foo");

        EXPECT_EQ(DeclKind::Class, decl.getKind());
        EXPECT_TRUE(NamedDecl::is(decl));
        EXPECT_TRUE(ClassDecl::is(decl));
        EXPECT_EQ("Foo", decl.getName());
    }

    {
        // class Point { int x; int y; }
        ClassDecl decl(nullptr, "Point");

        decl.createDeclaration<VariableDecl>(&TYPE_BUILTIN_INT, "x");
        decl.createDeclaration<VariableDecl>(&TYPE_BUILTIN_INT, "y");

        ASSERT_EQ(2, decl.getDeclarations().size());
        ASSERT_TRUE(VariableDecl::is(decl.getDeclarations()[0]));
        ASSERT_TRUE(VariableDecl::is(decl.getDeclarations()[1]));
        //EXPECT_EQ("x", VariableDecl::cast(decl.getDeclarations()[0])->getName());
        //EXPECT_EQ("y", VariableDecl::cast(decl.getDeclarations()[1])->getName());

        // class Point {}
        decl.removeDeclarations();
        ASSERT_TRUE(decl.getDeclarations().empty());

        // class Point { float x; }
        decl.createDeclaration<VariableDecl>(&TYPE_BUILTIN_FLOAT, "x");
        ASSERT_EQ(1, decl.getDeclarations().size());
        ASSERT_TRUE(VariableDecl::is(decl.getDeclarations()[0]));
    }
}

/* ************************************************************************ */

// TEST(NamespaceDecl, base)
// {
//     {
//         // namespace foo {}
//         // namespace foo:
//         const NamespaceDecl decl(nullptr, "foo");

//         EXPECT_EQ(DeclKind::Namespace, decl.getKind());
//         EXPECT_TRUE(NamedDecl::is(decl));
//         EXPECT_TRUE(NamespaceDecl::is(decl));
//         EXPECT_EQ("foo", decl.getName());
//     }
// }

/* ************************************************************************ */

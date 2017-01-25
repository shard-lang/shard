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

TEST(FunctionDecl, base)
{
    {
        // int foo() {}
        const FunctionDecl decl(TypeKind::Int, "foo", makeUnique<CompoundStmt>());

        EXPECT_EQ(DeclKind::Function, decl.getKind());
        EXPECT_TRUE(decl.is<FunctionDecl>());
        EXPECT_EQ("foo", decl.getName());
        EXPECT_EQ(TypeKind::Int, decl.getRetType());
        EXPECT_TRUE(decl.getParameters().empty());
        ASSERT_NE(nullptr, decl.getBodyStmt());
        EXPECT_TRUE(decl.getBodyStmt()->is<CompoundStmt>());
    }

    {
        // int foo() {}
        FunctionDecl decl(TypeKind::Int, "foo", makeUnique<CompoundStmt>());

        EXPECT_EQ(DeclKind::Function, decl.getKind());
        EXPECT_TRUE(decl.is<FunctionDecl>());
        EXPECT_EQ("foo", decl.getName());
        EXPECT_EQ(TypeKind::Int, decl.getRetType());
        EXPECT_TRUE(decl.getParameters().empty());
        ASSERT_NE(nullptr, decl.getBodyStmt());
        EXPECT_TRUE(decl.getBodyStmt()->is<CompoundStmt>());

        // int bar() {}
        decl.setName("bar");
        EXPECT_EQ("bar", decl.getName());
        EXPECT_EQ(TypeKind::Int, decl.getRetType());
        EXPECT_TRUE(decl.getParameters().empty());
        ASSERT_NE(nullptr, decl.getBodyStmt());
        EXPECT_TRUE(decl.getBodyStmt()->is<CompoundStmt>());

        // void bar() {}
        decl.setRetType(TypeKind::Void);
        EXPECT_EQ("bar", decl.getName());
        EXPECT_EQ(TypeKind::Void, decl.getRetType());
        EXPECT_TRUE(decl.getParameters().empty());
        ASSERT_NE(nullptr, decl.getBodyStmt());
        EXPECT_TRUE(decl.getBodyStmt()->is<CompoundStmt>());

        // void bar(int x, int y) {}
        PtrDynamicArray<VariableDecl> params;
        params.push_back(VariableDecl::make(TypeKind::Int, "x"));
        params.push_back(VariableDecl::make(TypeKind::Int, "y"));
        decl.setParameters(moveValue(params));
        EXPECT_EQ("bar", decl.getName());
        EXPECT_EQ(TypeKind::Void, decl.getRetType());
        EXPECT_FALSE(decl.getParameters().empty());
        ASSERT_EQ(2, decl.getParameters().size());
        ASSERT_TRUE(decl.getParameters()[0]->is<VariableDecl>());
        ASSERT_TRUE(decl.getParameters()[1]->is<VariableDecl>());
        EXPECT_EQ("x", decl.getParameters()[0]->getName());
        EXPECT_EQ("y", decl.getParameters()[1]->getName());

        decl.setBodyStmt(makeUnique<CompoundStmt>());
        ASSERT_NE(nullptr, decl.getBodyStmt());
        EXPECT_TRUE(decl.getBodyStmt()->is<CompoundStmt>());
    }

    {
        // int foo() {}
        const auto decl = FunctionDecl::make(TypeKind::Int, "foo", makeUnique<CompoundStmt>());

        EXPECT_EQ(DeclKind::Function, decl->getKind());
        EXPECT_TRUE(decl->is<FunctionDecl>());
        EXPECT_EQ("foo", decl->getName());
        EXPECT_EQ(TypeKind::Int, decl->getRetType());
        EXPECT_TRUE(decl->getParameters().empty());
        ASSERT_NE(nullptr, decl->getBodyStmt());
        EXPECT_TRUE(decl->getBodyStmt()->is<CompoundStmt>());
    }

}

/* ************************************************************************ */

TEST(ClassDecl, base)
{
    {
        // class Foo {}
        const ClassDecl decl("Foo");

        EXPECT_EQ(DeclKind::Class, decl.getKind());
        EXPECT_TRUE(decl.is<ClassDecl>());
        EXPECT_EQ("Foo", decl.getName());
    }

    {
        // class Point { int x; int y; }
        ClassDecl decl("Point");

        decl.addDecl(VariableDecl::make(TypeKind::Int, "x"));
        decl.addDecl(VariableDecl::make(TypeKind::Int, "y"));

        ASSERT_EQ(2, decl.getDecls().size());
        ASSERT_TRUE(decl.getDecls()[0]->is<VariableDecl>());
        ASSERT_TRUE(decl.getDecls()[1]->is<VariableDecl>());
        EXPECT_EQ("x", decl.getDecls()[0]->cast<VariableDecl>().getName());
        EXPECT_EQ("y", decl.getDecls()[1]->cast<VariableDecl>().getName());
    }

    {
        // class Point { }
        ClassDecl decl("Point");

        EXPECT_EQ(DeclKind::Class, decl.getKind());
        EXPECT_TRUE(decl.is<ClassDecl>());
        EXPECT_EQ("Point", decl.getName());
        EXPECT_TRUE(decl.getDecls().empty());

        PtrDynamicArray<Decl> decls;
        decls.push_back(VariableDecl::make(TypeKind::Int, "x"));
        decls.push_back(VariableDecl::make(TypeKind::Int, "y"));

        // class Point { int x; int y; }
        decl.setDecls(moveValue(decls));

        EXPECT_FALSE(decl.getDecls().empty());
        ASSERT_EQ(2, decl.getDecls().size());
        ASSERT_TRUE(decl.getDecls()[0]->is<VariableDecl>());
        ASSERT_TRUE(decl.getDecls()[1]->is<VariableDecl>());
        EXPECT_EQ("x", decl.getDecls()[0]->cast<VariableDecl>().getName());
        EXPECT_EQ("y", decl.getDecls()[1]->cast<VariableDecl>().getName());
    }

    {
        // class Foo {}
        const auto decl = ClassDecl::make("Foo");

        EXPECT_EQ(DeclKind::Class, decl->getKind());
        EXPECT_TRUE(decl->is<ClassDecl>());
        EXPECT_EQ("Foo", decl->getName());
    }

}

/* ************************************************************************ */

TEST(NamespaceDecl, base)
{
    {
        // namespace foo {}
        const NamespaceDecl decl("foo");

        EXPECT_EQ(DeclKind::Namespace, decl.getKind());
        EXPECT_TRUE(decl.is<NamespaceDecl>());
        EXPECT_EQ("foo", decl.getName());
    }

    {
        // namespace foo { int x; int y; }
        NamespaceDecl decl("foo");

        decl.addDecl(VariableDecl::make(TypeKind::Int, "x"));
        decl.addDecl(VariableDecl::make(TypeKind::Int, "y"));

        ASSERT_EQ(2, decl.getDecls().size());
        ASSERT_TRUE(decl.getDecls()[0]->is<VariableDecl>());
        ASSERT_TRUE(decl.getDecls()[1]->is<VariableDecl>());
        EXPECT_EQ("x", decl.getDecls()[0]->cast<VariableDecl>().getName());
        EXPECT_EQ("y", decl.getDecls()[1]->cast<VariableDecl>().getName());
    }

    {
        // namespace foo { }
        NamespaceDecl decl("foo");

        EXPECT_EQ(DeclKind::Namespace, decl.getKind());
        EXPECT_TRUE(decl.is<NamespaceDecl>());
        EXPECT_EQ("foo", decl.getName());
        EXPECT_TRUE(decl.getDecls().empty());

        PtrDynamicArray<Decl> decls;
        decls.push_back(VariableDecl::make(TypeKind::Int, "x"));
        decls.push_back(VariableDecl::make(TypeKind::Int, "y"));

        // namespace foo { int x; int y; }
        decl.setDecls(moveValue(decls));

        EXPECT_FALSE(decl.getDecls().empty());
        ASSERT_EQ(2, decl.getDecls().size());
        ASSERT_TRUE(decl.getDecls()[0]->is<VariableDecl>());
        ASSERT_TRUE(decl.getDecls()[1]->is<VariableDecl>());
        EXPECT_EQ("x", decl.getDecls()[0]->cast<VariableDecl>().getName());
        EXPECT_EQ("y", decl.getDecls()[1]->cast<VariableDecl>().getName());
    }

    {
        // namespace foo {}
        const auto decl = NamespaceDecl::make("foo");

        EXPECT_EQ(DeclKind::Namespace, decl->getKind());
        EXPECT_TRUE(decl->is<NamespaceDecl>());
        EXPECT_EQ("foo", decl->getName());
    }

}

/* ************************************************************************ */

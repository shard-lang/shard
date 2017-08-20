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

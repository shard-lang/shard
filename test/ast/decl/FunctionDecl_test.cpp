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
#include "shard/ast/decl/FunctionDecl.hpp"
#include "shard/ast/decl/VariableDecl.hpp"
#include "shard/ast/Type.hpp"
#include "shard/ast/Expr.hpp"
#include "shard/ast/stmt/CompoundStmt.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

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

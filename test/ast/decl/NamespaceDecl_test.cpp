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
#include "shard/ast/decl/NamespaceDecl.hpp"
#include "shard/ast/decl/VariableDecl.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

TEST(NamespaceDecl, base)
{
    {
        // namespace foo {}
        const NamespaceDecl decl("foo");

        EXPECT_TRUE(decl.is<NamespaceDecl>());
        EXPECT_EQ("foo", decl.name());
    }

    {
        // namespace foo { int x; int y; }
        NamespaceDecl decl("foo");

        decl.addDecl(VariableDecl::make("int", "x", nullptr));
        decl.addDecl(VariableDecl::make("int", "y", nullptr));

        ASSERT_EQ(2, decl.decls().size());
        ASSERT_TRUE(decl.decls()[0]->is<VariableDecl>());
        ASSERT_TRUE(decl.decls()[1]->is<VariableDecl>());
        EXPECT_EQ("x", decl.decls()[0]->cast<VariableDecl>().name());
        EXPECT_EQ("y", decl.decls()[1]->cast<VariableDecl>().name());
    }

    {
        // namespace foo { }
        NamespaceDecl decl("foo");

        EXPECT_TRUE(decl.is<NamespaceDecl>());
        EXPECT_EQ("foo", decl.name());
        EXPECT_TRUE(decl.decls().empty());

        DeclPtrVector decls;
        decls.push_back(VariableDecl::make("int", "x", nullptr));
        decls.push_back(VariableDecl::make("int", "y", nullptr));

        // namespace foo { int x; int y; }
        decl.setDecls(std::move(decls));

        EXPECT_FALSE(decl.decls().empty());
        ASSERT_EQ(2, decl.decls().size());
        ASSERT_TRUE(decl.decls()[0]->is<VariableDecl>());
        ASSERT_TRUE(decl.decls()[1]->is<VariableDecl>());
        EXPECT_EQ("x", decl.decls()[0]->cast<VariableDecl>().name());
        EXPECT_EQ("y", decl.decls()[1]->cast<VariableDecl>().name());
    }

    {
        // namespace foo {}
        const auto decl = NamespaceDecl::make("foo", {});

        EXPECT_TRUE(decl->is<NamespaceDecl>());
        EXPECT_EQ("foo", decl->name());
    }
}

/* ************************************************************************ */

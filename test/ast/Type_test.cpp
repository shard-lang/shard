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
#include "shard/ast/Type.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

TEST(TypeInfo, construction)
{
    {
        const Type type(TypeKind::Any);
        EXPECT_EQ(TypeKind::Any, type.getKind());
    }

    {
        const Type type(TypeKind::Auto);
        EXPECT_EQ(TypeKind::Auto, type.getKind());
    }

    {
        const Type type("MyClass");
        EXPECT_EQ(TypeKind::Typename, type.getKind());
        EXPECT_EQ("MyClass", type.getName());
    }
}

/* ************************************************************************ */

TEST(TypeInfo, compare)
{
    {
        const Type type1(TypeKind::Any);
        const Type type2(TypeKind::Any);

        EXPECT_EQ(type1, type2);
    }

    {
        const Type type1(TypeKind::Int);
        const Type type2(TypeKind::Float);

        EXPECT_NE(type1, type2);
    }

    {
        const Type type1("MyClass");
        const Type type2("MyClass");

        EXPECT_EQ(type1, type2);
    }

    {
        const Type type1("MyClass1");
        const Type type2("MyClass2");

        EXPECT_NE(type1, type2);
    }
}

/* ************************************************************************ */

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

TEST(Type, builtins)
{
    EXPECT_EQ(TypeKind::Void,   TYPE_BUILTIN_VOID.getKind());
    EXPECT_EQ(TypeKind::Int,    TYPE_BUILTIN_INT.getKind());
    EXPECT_EQ(TypeKind::Float,  TYPE_BUILTIN_FLOAT.getKind());
    EXPECT_EQ(TypeKind::Char,   TYPE_BUILTIN_CHAR.getKind());
    EXPECT_EQ(TypeKind::String, TYPE_BUILTIN_STRING.getKind());
    EXPECT_EQ(TypeKind::Var,    TYPE_BUILTIN_VAR.getKind());
}

/* ************************************************************************ */

TEST(TypeInfo, construction)
{
    {
        const TypeInfo info(&TYPE_BUILTIN_VAR);

        EXPECT_EQ(&TYPE_BUILTIN_VAR, info.getType());
    }

    {
        const TypeInfo info(&TYPE_BUILTIN_VOID);

        EXPECT_EQ(&TYPE_BUILTIN_VOID, info.getType());
    }
}

/* ************************************************************************ */

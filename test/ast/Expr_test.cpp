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

// C++
#include <limits>

// Shard
#include "shard/ast/Expr.hpp"
#include "shard/ast/expr/IdentifierExpr.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

TEST(Expr, vtable)
{
    UniquePtr<Expr> expr = IdentifierExpr::make("variable");

    EXPECT_EQ(ExprKind::Identifier, expr->getKind());
    EXPECT_TRUE(expr->is<IdentifierExpr>());
    ASSERT_FALSE(expr->cast<IdentifierExpr>().getName().empty());
    EXPECT_EQ("variable", expr->cast<IdentifierExpr>().getName());
}

/* ************************************************************************ */
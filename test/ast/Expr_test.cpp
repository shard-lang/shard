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
#include "shard/ast/utility.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

namespace {

/* ************************************************************************ */

struct TestExpr : public Expr, public PtrBuilder<TestExpr>
{
    explicit TestExpr(SourceRange range = {}) noexcept
        : Expr(range) {}
};

/* ************************************************************************ */

struct TestExpr2 : public Expr
{

};

/* ************************************************************************ */

}

/* ************************************************************************ */

TEST(Expr, basic)
{
    TestExpr expr;

    EXPECT_TRUE(expr.is<TestExpr>());
    EXPECT_FALSE(expr.is<TestExpr2>());
}

/* ************************************************************************ */

TEST(Expr, vtable)
{
    ExprPtr expr = TestExpr::make();

    EXPECT_TRUE(expr->is<TestExpr>());
    EXPECT_FALSE(expr->is<TestExpr2>());
}

/* ************************************************************************ */
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
#include "shard/interpreter/Context.hpp"
#include "shard/interpreter/Interpreter.hpp"
#include "shard/ast/expr/IntLiteralExpr.hpp"
#include "shard/ast/expr/BinaryExpr.hpp"
#include "shard/ast/stmt/CompoundStmt.hpp"
#include "shard/ast/Unit.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;
using namespace shard::interpreter;

/* ************************************************************************ */

TEST(Interpreter, expression)
{
    {
        auto ctx = Context();

        // 5
        auto expr = IntLiteralExpr::make(5);

        // Interpret expression
        auto res = interpret(makeView(expr), ctx);

        ASSERT_EQ(res.getKind(), ValueKind::Int);
        EXPECT_EQ(res.asInt(), 5);
    }

    {
        auto ctx = Context();

        // 5 + 18
        auto expr = BinaryExpr::make(
            BinaryExpr::OpKind::Add,
            IntLiteralExpr::make(5),
            IntLiteralExpr::make(18)
        );

        // Interpret expression
        auto res = interpret(makeView(expr), ctx);

        ASSERT_EQ(res.getKind(), ValueKind::Int);
        EXPECT_EQ(res.asInt(), 5 + 18);
    }
}

/* ************************************************************************ */

TEST(Interpreter, compoundStmt)
{
    {
        auto ctx = Context();
        auto mainScope = ctx.getCurrent();

        auto stmt = CompoundStmt::make();

        // Interpret statement
        interpret(makeView(stmt), ctx);

        // Same scope as starting
        EXPECT_EQ(ctx.getCurrent(), mainScope);
    }
}

/* ************************************************************************ */

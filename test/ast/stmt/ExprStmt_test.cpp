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
#include "shard/ast/stmt/ExprStmt.hpp"
#include "shard/ast/expr/IntLiteralExpr.hpp"
#include "shard/ast/expr/BoolLiteralExpr.hpp"

/* ************************************************************************ */

using namespace shard;
using namespace shard::ast;

/* ************************************************************************ */

TEST(ExprStmt, base)
{
    {
        // ;
        const ExprStmt stmt;

        EXPECT_TRUE(stmt.is<ExprStmt>());
        ASSERT_EQ(nullptr, stmt.expr());
    }

    {
        // 5;
        const ExprStmt stmt(IntLiteralExpr::make(5));

        EXPECT_TRUE(stmt.is<ExprStmt>());
        ASSERT_NE(nullptr, stmt.expr());
        EXPECT_TRUE(stmt.expr()->is<IntLiteralExpr>());
    }

    {
        // 5;
        ExprStmt stmt(IntLiteralExpr::make(5));

        EXPECT_TRUE(stmt.is<ExprStmt>());
        ASSERT_NE(nullptr, stmt.expr());
        EXPECT_TRUE(stmt.expr()->is<IntLiteralExpr>());

        // true;
        stmt.setExpr(BoolLiteralExpr::make(true));
        EXPECT_TRUE(stmt.is<ExprStmt>());
        ASSERT_NE(nullptr, stmt.expr());
        EXPECT_TRUE(stmt.expr()->is<BoolLiteralExpr>());
    }

    {
        // ;
        const auto stmt = ExprStmt::make(nullptr);

        EXPECT_TRUE(stmt->is<ExprStmt>());
        ASSERT_EQ(nullptr, stmt->expr());
    }
}

/* ************************************************************************ */

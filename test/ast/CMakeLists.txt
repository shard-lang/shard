# ************************************************************************* #
# This file is part of Shard.                                               #
#                                                                           #
# Shard is free software: you can redistribute it and/or modify             #
# it under the terms of the GNU Affero General Public License as            #
# published by the Free Software Foundation.                                #
#                                                                           #
# This program is distributed in the hope that it will be useful,           #
# but WITHOUT ANY WARRANTY; without even the implied warranty of            #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the              #
# GNU Affero General Public License for more details.                       #
#                                                                           #
# You should have received a copy of the GNU Affero General Public License  #
# along with this program. If not, see <http://www.gnu.org/licenses/>.      #
# ************************************************************************* #

if (NOT SHARD_BUILD_AST)
    return ()
endif ()

# ************************************************************************* #

# Create test executable
add_executable(shard-ast_test
    Type_test.cpp

    # Expr
    Expr_test.cpp
    expr/BinaryExpr_test.cpp
    expr/BoolLiteralExpr_test.cpp
    expr/CharLiteralExpr_test.cpp
    expr/FloatLiteralExpr_test.cpp
    expr/FunctionCallExpr_test.cpp
    expr/IdentifierExpr_test.cpp
    expr/IntLiteralExpr_test.cpp
    expr/MemberAccessExpr_test.cpp
    expr/NullLiteralExpr_test.cpp
    expr/ParenExpr_test.cpp
    expr/StringLiteralExpr_test.cpp
    expr/SubscriptExpr_test.cpp
    expr/UnaryExpr_test.cpp

    # Decl
    decl/ClassDecl_test.cpp
    decl/FunctionDecl_test.cpp
    decl/NamespaceDecl_test.cpp
    decl/VariableDecl_test.cpp

    # Stmt
    stmt/BreakStmt_test.cpp
    stmt/CaseStmt_test.cpp
    stmt/CompoundStmt_test.cpp
    stmt/ContinueStmt_test.cpp
    stmt/DeclStmt_test.cpp
    stmt/DefaultStmt_test.cpp
    stmt/DoWhileStmt_test.cpp
    stmt/ExprStmt_test.cpp
    stmt/ForStmt_test.cpp
    stmt/IfStmt_test.cpp
    stmt/ReturnStmt_test.cpp
    stmt/SwitchStmt_test.cpp
    stmt/WhileStmt_test.cpp
)

# Required C++ features (see CMAKE_CXX_KNOWN_FEATURES)
target_compile_features(shard-ast_test
    PUBLIC cxx_std_17
)

target_link_libraries(shard-ast_test
    PRIVATE shard-ast
    PRIVATE gtest_main
)

if (SHARD_COVERAGE)
    include(Coverage)
    target_coverage(shard-ast_test)
endif ()

# ************************************************************************* #

add_test(shard-ast_test shard-ast_test)

# ************************************************************************* #

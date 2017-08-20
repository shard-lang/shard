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
    BinaryExpr_test.cpp
    BoolLiteralExpr_test.cpp
    CharLiteralExpr_test.cpp
    Expr_test.cpp
    FloatLiteralExpr_test.cpp
    FunctionCallExpr_test.cpp
    IdentifierExpr_test.cpp
    IntLiteralExpr_test.cpp
    MemberAccessExpr_test.cpp
    NullLiteralExpr_test.cpp
    ParenExpr_test.cpp
    StringLiteralExpr_test.cpp
    SubscriptExpr_test.cpp
    UnaryExpr_test.cpp

    # Decl
    ClassDecl_test.cpp
    FunctionDecl_test.cpp
    NamespaceDecl_test.cpp
    VariableDecl_test.cpp

    # Stmt
    BreakStmt_test.cpp
    CaseStmt_test.cpp
    CompoundStmt_test.cpp
    ContinueStmt_test.cpp
    DeclStmt_test.cpp
    DefaultStmt_test.cpp
    DoWhileStmt_test.cpp
    ExprStmt_test.cpp
    ForStmt_test.cpp
    IfStmt_test.cpp
    ReturnStmt_test.cpp
    SwitchStmt_test.cpp
    WhileStmt_test.cpp
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

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

# Build AST part
option(SHARD_BUILD_AST "Build AST" On)

# ************************************************************************* #

if (NOT SHARD_BUILD_AST)
    return ()
endif ()

# ************************************************************************* #

# Create Shard part
add_library(shard-ast
    # Decl
    decl/ClassDecl.cpp
    decl/CompoundDecl.cpp
    decl/FunctionDecl.cpp
    decl/NamespaceDecl.cpp
    decl/VariableDecl.cpp

    # Stmt
    stmt/BreakStmt.cpp
    stmt/ContinueStmt.cpp
    stmt/IfStmt.cpp
    stmt/ReturnStmt.cpp
    stmt/WhileStmt.cpp
)

# Include directories
target_include_directories(shard-ast
    PUBLIC ../../include
)

# Required C++ features (see CMAKE_CXX_KNOWN_FEATURES)
target_compile_features(shard-ast
    PUBLIC cxx_std_17
)

# Link to libraries
target_link_libraries(shard-ast
    PUBLIC shard-core
)

# Enable coverage
if (SHARD_COVERAGE)
    include(Coverage)
    target_coverage(shard-ast)
endif ()

# ************************************************************************* #
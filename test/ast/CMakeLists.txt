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
    TypeTest.cpp
    ExprTest.cpp
    DeclTest.cpp
    StmtTest.cpp
)

# Required C++ features (see CMAKE_CXX_KNOWN_FEATURES)
target_compile_features(shard-ast_test
    PUBLIC cxx_std_17
)

target_link_libraries(shard-ast_test
    PRIVATE shard-ast
    PRIVATE gtest_main
)

target_coverage(shard-ast_test)

add_test(shard-ast_test shard-ast_test)

# ************************************************************************* #

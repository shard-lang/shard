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

option(SHARD_BUILD_TESTS "Build unit tests" Off)

if (SHARD_BUILD_TESTS AND CMAKE_COMPILER_IS_GNUCXX)
    option(SHARD_COVERAGE "Enable code coverage generation" Off)
endif ()

# ************************************************************************* #

if (NOT SHARD_BUILD_TESTS)
    return ()
endif ()

# ************************************************************************* #

# Create test executable
add_executable(shard-core_test
    SourceLocation_test.cpp
    ViewPtr_test.cpp
)

# Required C++ features (see CMAKE_CXX_KNOWN_FEATURES)
target_compile_features(shard-core_test
    PUBLIC cxx_std_17
)

target_link_libraries(shard-core_test
    PRIVATE shard-core
    PRIVATE gtest_main
)

if (SHARD_COVERAGE)
    include(Coverage)
    target_coverage(shard-core_test)
endif ()

# ************************************************************************* #

add_test(shard-core_test shard-core_test)

# ************************************************************************* #

add_subdirectory(tokenizer)
add_subdirectory(ast)
add_subdirectory(parser)
add_subdirectory(ir)

# ************************************************************************* #

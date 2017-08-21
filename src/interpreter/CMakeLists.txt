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

# Build Interpreter part
option(SHARD_BUILD_INTERPRETER "Build interpreter" On)

# ************************************************************************* #

if (NOT SHARD_BUILD_INTERPRETER)
    return ()
endif ()

# ************************************************************************* #

# Check conditions
if (NOT SHARD_BUILD_PARSER OR NOT SHARD_BUILD_AST)
    message(WARNING "Option to build interpreter requires building AST and parser, turning interpreter off.")
    set(SHARD_BUILD_INTERPRETER Off)
    return ()
endif()

# ************************************************************************* #

# Create Shard part
add_library(shard-interpreter
    Context.cpp
    Interpreter.cpp
    Symbol.cpp
    Value.cpp
    Scope.cpp
)

# Include directories
target_include_directories(shard-interpreter
    PUBLIC ../../include
)

# Required C++ features (see CMAKE_CXX_KNOWN_FEATURES)
target_compile_features(shard-interpreter
    PUBLIC cxx_std_17
)

# Link to libraries
target_link_libraries(shard-interpreter
    PUBLIC shard-core
    PUBLIC shard-ast
)

# Enable coverage
if (SHARD_COVERAGE)
    include(Coverage)
    target_coverage(shard-interpreter)
endif ()

# ************************************************************************* #
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

# Build parser part
option(SHARD_BUILD_PARSER "Build parser" On)

# ************************************************************************* #

if (NOT SHARD_BUILD_PARSER)
    return ()
endif ()

# ************************************************************************* #

# Check conditions
if (NOT SHARD_BUILD_TOKENIZER OR NOT SHARD_BUILD_AST)
    message(WARNING "Option to build Parser requires building AST and Tokenizer, turning Parser off.")
    set(SHARD_BUILD_PARSER Off)
    return ()
endif()

# ************************************************************************* #

# Create Shard part
add_library(shard-parser
    Parser.cpp
)

# Include directories
target_include_directories(shard-parser
    PUBLIC ../../include
)

# Required C++ features (see CMAKE_CXX_KNOWN_FEATURES)
target_compile_features(shard-parser
    PUBLIC cxx_std_17
)

# Link to libraries
target_link_libraries(shard-parser
    PUBLIC shard-core
    PUBLIC shard-tokenizer
    PUBLIC shard-ast
)

# Enable coverage
if (SHARD_COVERAGE)
    include(Coverage)
    target_coverage(shard-parser)
endif ()

# ************************************************************************* #
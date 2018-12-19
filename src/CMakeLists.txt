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

# Create Shard core
add_library(shard-core
    error.cpp
)

# Include directories
target_include_directories(shard-core
    PUBLIC ../include
)

# Required C++ features (see CMAKE_CXX_KNOWN_FEATURES)
target_compile_features(shard-core
    PUBLIC cxx_std_17
)

# Link libraries
target_link_libraries(shard-core
    INTERFACE stdc++fs
)

# Enable coverage
if (SHARD_COVERAGE)
    include(Coverage)
    target_coverage(shard-core)
endif ()

# ************************************************************************* #

# Parts
add_subdirectory(tokenizer)
add_subdirectory(ast)
add_subdirectory(parser)
add_subdirectory(ir)
add_subdirectory(interpreter)

# ************************************************************************* #

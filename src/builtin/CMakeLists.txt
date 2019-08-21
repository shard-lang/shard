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

# Build builtin part
option(SHARD_BUILD_BUILTIN "Build builtin extensions" On)

# ************************************************************************* #

if (NOT SHARD_BUILD_BUILTIN)
    return ()
endif ()

# ************************************************************************* #

# Create Shard part
add_library(shard-builtin
    Parser.cpp
)

# Include directories
target_include_directories(shard-builtin
    PUBLIC ../../include
)

# Required C++ features (see CMAKE_CXX_KNOWN_FEATURES)
target_compile_features(shard-builtin
    PUBLIC cxx_std_17
)

# Link to libraries
target_link_libraries(shard-builtin
    PUBLIC shard-core
    PUBLIC shard-parser
)

# Enable coverage
if (SHARD_COVERAGE)
    include(Coverage)
    target_coverage(shard-builtin)
endif ()

# ************************************************************************* #
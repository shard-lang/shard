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

# Build IR part
option(SHARD_BUILD_IR "Build IR" On)

# ************************************************************************* #

if (NOT SHARD_BUILD_IR)
    return ()
endif ()

# ************************************************************************* #

# Create Shard part
add_library(shard-ir
    Function.cpp
    Module.cpp
    Serializer_read.cpp
    Serializer_write.cpp
)

# Include directories
target_include_directories(shard-ir
    PUBLIC ../../include
)

# Required C++ features (see CMAKE_CXX_KNOWN_FEATURES)
target_compile_features(shard-ir
    PUBLIC cxx_std_17
)

# Link to libraries
target_link_libraries(shard-ir
    PUBLIC shard-core
)

# Enable coverage
if (SHARD_COVERAGE)
    include(Coverage)
    target_coverage(shard-ir)
endif ()

# ************************************************************************* #
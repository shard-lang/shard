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

cmake_minimum_required(VERSION 3.1)

# ************************************************************************* #

option(SHARD_BUILD_TESTS "Build unit tests" Off)
option(SHARD_BUILD_TOKENIZER "Build tokenizer" On)

# ************************************************************************* #

function (add_shard_library NAME)
    include(CMakeParseArguments)
    cmake_parse_arguments(ARG "" "" "HEADERS;SOURCES;LIBRARIES" ${ARGN})

    add_library(${NAME} ${ARG_SOURCES})

    set_target_properties(${NAME} PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED On
        CXX_EXTENSIONS Off
    )

    target_include_directories(${NAME}
        PUBLIC ${CMAKE_SOURCE_DIR}/include
    )
endfunction ()

# ************************************************************************* #

# Add source files
add_subdirectory(src)

# ************************************************************************* #

# Build tests
if (SHARD_BUILD_TESTS)
    enable_testing()
    add_subdirectory(vendor/googletest)
    add_subdirectory(test)
endif ()

# ************************************************************************* #

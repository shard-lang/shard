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

set(CURRENT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

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
        PUBLIC ${CURRENT_DIR}/include
    )
endfunction ()

# ************************************************************************* #

# Add source files
add_subdirectory(src)

# ************************************************************************* #

# Build tests
if (SHARD_BUILD_TESTS)
    # CTest support
    enable_testing()

    function (add_shard_test NAME)
        include(CMakeParseArguments)
        cmake_parse_arguments(ARG "" "" "HEADERS;SOURCES;LIBRARIES" ${ARGN})

        add_executable(${NAME} ${ARG_SOURCES})

        set_target_properties(${NAME} PROPERTIES
            CXX_STANDARD 14
            CXX_STANDARD_REQUIRED On
            CXX_EXTENSIONS Off
        )

        target_include_directories(${NAME}
            PUBLIC ${CURRENT_DIR}/include
        )

        target_link_libraries(${NAME}
            ${ARG_LIBRARIES}
            gtest_main
        )

        add_test(${NAME} ${NAME})
    endfunction ()

    # Init google test submodule
    if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vendor/googletest/CMakeLists.txt")
        find_package(Git REQUIRED)
        execute_process(
            COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive vendor/googletest
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
    endif ()

    # Build google test
    set(BUILD_GMOCK Off CACHE BOOL "" FORCE)
    set(BUILD_GTEST On CACHE BOOL "" FORCE)
    set(gtest_force_shared_crt On CACHE BOOL "" FORCE)
    mark_as_advanced(BUILD_GMOCK BUILD_GTEST gtest_build_samples gtest_build_tests gtest_disable_pthreads gtest_hide_internal_symbols gtest_force_shared_crt)
    add_subdirectory(vendor/googletest)

    # Add shard tests
    add_subdirectory(test)
endif ()

# ************************************************************************* #

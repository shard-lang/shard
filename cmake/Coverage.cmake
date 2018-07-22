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

##
## Add target for coverage
##
function (add_coverage_target NAME)
    if (NOT TARGET coverage)
        # Required program
        find_program(LCOV lcov)

        # Add custom target for gcov
        add_custom_target(coverage
            # Cleanup lcov
            COMMAND ${LCOV} --directory . --zerocounters

            # Run tests
            COMMAND ctest

            # Capturing lcov counters and generating report
            COMMAND ${LCOV} --directory . --capture --output-file coverage0.info
            COMMAND ${LCOV}
                -r coverage0.info
                '*/vendor/*'
                '*/test/*'
                '/usr/*'
                'Token.def'
                --output-file coverage.info

            DEPENDS ${NAME}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Resetting code coverage counters to zero.\nProcessing code coverage counters."
        )
    else ()
        # Add target as dependency
        add_dependencies(coverage ${NAME})
    endif ()
endfunction ()

##
## Add target for HTML coverage output.
##
function (add_coverage_html_target)
    if (NOT TARGET coverage-html)
        # Find genhtml program
        find_program(GENHTML genhtml)

        # Add custom target for gcov html report
        add_custom_target(coverage-html
            # Capturing lcov counters and generating report
            COMMAND ${GENHTML} --demangle-cpp -o coverage coverage.info
            COMMAND ${CMAKE_COMMAND} -E remove coverage.info

            DEPENDS coverage
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Generate coverage report."
        )
    endif ()
endfunction ()

##
## Enables code coverage for given target.
##
## param: NAME target name.
##
function (target_coverage NAME)
    # Only GCC is supported now
    if (CMAKE_COMPILER_IS_GNUCXX)
        target_compile_options(${NAME} PRIVATE --coverage)
        target_link_libraries(${NAME} PRIVATE --coverage)

        add_coverage_target(${NAME})
        add_coverage_html_target()
    endif ()
endfunction ()

# ************************************************************************* #
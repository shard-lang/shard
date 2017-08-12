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
## Enables code coverage for given target.
##
## param: NAME target name.
##
function (target_coverage NAME)
    # Only GCC is supported now
    if (CMAKE_COMPILER_IS_GNUCXX)
        target_compile_options(${NAME} PRIVATE --coverage)
        target_link_libraries(${NAME} PRIVATE --coverage)
    endif ()
endfunction ()

# ************************************************************************* #
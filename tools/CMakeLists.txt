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

option(SHARD_BUILD_TOOLS "Build tools" On)

# ************************************************************************* #

if (NOT SHARD_BUILD_TOOLS)
    return ()
endif ()

# ************************************************************************* #

if (SHARD_BUILD_INTERPRETER)
    add_subdirectory(interpreter)
endif()

if (SHARD_BUILD_AST)
    add_subdirectory(astdump)
endif ()

if (SHARD_BUILD_IR)
    add_subdirectory(irdump)
endif ()

# ************************************************************************* #
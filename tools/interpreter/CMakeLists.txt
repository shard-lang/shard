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

add_executable(shard-interpreter-cli main.cpp)
target_link_libraries(shard-interpreter-cli shard-interpreter shard-parser shard-ast shard-tokenizer stdc++fs)
set_target_properties(shard-interpreter-cli PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    OUTPUT_NAME shard-interpreter
)

# ************************************************************************* #
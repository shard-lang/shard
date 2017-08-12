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

# Create shard interpreter
add_executable(shard-interpreter-cli
    main.cpp
)

target_link_libraries(shard-interpreter-cli
    PUBLIC shard-interpreter
    PUBLIC shard-parser
    PUBLIC shard-ast
    PUBLIC shard-tokenizer
)

# Required C++ features (see CMAKE_CXX_KNOWN_FEATURES)
target_compile_features(shard-core
    PUBLIC cxx_std_17
)

set_target_properties(shard-interpreter-cli PROPERTIES
    OUTPUT_NAME shard
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

# ************************************************************************* #
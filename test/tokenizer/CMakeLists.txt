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

if (NOT SHARD_BUILD_TOKENIZER)
    return ()
endif ()

# ************************************************************************* #

# Create test executable
add_executable(shard-tokenizer_test
    TokenizerTest.cpp
    SourceTest.cpp
)

# Required C++ features (see CMAKE_CXX_KNOWN_FEATURES)
target_compile_features(shard-tokenizer_test
    PUBLIC cxx_std_17
)

target_link_libraries(shard-tokenizer_test
    PRIVATE shard-tokenizer
    PRIVATE gtest_main
)

target_coverage(shard-tokenizer_test)

add_test(shard-tokenizer_test shard-tokenizer_test)

# ************************************************************************* #

# Copy test files
file(COPY
    SourceTest-file_empty.txt
    SourceTest-file_basic.txt
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)

# ************************************************************************* #
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
    exceptions_test.cpp
    Token_test.cpp
    Source_test.cpp
    SourceIterator_test.cpp
    Tokenizer_test.cpp
    TokenizerIterator_test.cpp
    TokenFilterIterator_test.cpp
)

# Required C++ features (see CMAKE_CXX_KNOWN_FEATURES)
target_compile_features(shard-tokenizer_test
    PUBLIC cxx_std_17
)

target_link_libraries(shard-tokenizer_test
    PRIVATE shard-tokenizer
    PRIVATE gtest_main
)

if (SHARD_COVERAGE)
    include(Coverage)
    target_coverage(shard-tokenizer_test)
endif ()

# ************************************************************************* #

add_test(shard-tokenizer_test shard-tokenizer_test)

# ************************************************************************* #
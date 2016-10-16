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

add_library(shard-tokenizer
    Tokenizer.hpp
    Tokenizer.cpp
    Token.hpp
    TokenType.hpp
    KeywordType.hpp
    TokenizerException.hpp
    Source.hpp
)

# ************************************************************************* #

set_target_properties(shard-tokenizer PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
)

target_include_directories(shard-tokenizer
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../..
)

target_link_libraries(shard-tokenizer
    shard-core
)

# ************************************************************************* #
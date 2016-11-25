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

add_shard_library(shard-core
    HEADERS
        Any.hpp
        Assert.hpp
        Byte.hpp
        DynamicArray.hpp
        Exception.hpp
        FilePath.hpp
        FixedArray.hpp
        HashMap.hpp
        Map.hpp
        SharedPtr.hpp
        SourceLocation.hpp
        SourceRange.hpp
        String.hpp
        StringView.hpp
        UniquePtr.hpp
        ViewPtr.hpp
        error.hpp
        utility.hpp
    SOURCES
        error.cpp
)

# ************************************************************************* #

if (SHARD_BUILD_TOKENIZER)
    add_subdirectory(tokenizer)
endif ()

if (SHARD_BUILD_AST)
    add_subdirectory(ast)
endif ()

if (SHARD_BUILD_PARSER)
    add_subdirectory(parser)
endif ()

# ************************************************************************* #

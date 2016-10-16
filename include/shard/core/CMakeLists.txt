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

add_library(shard-core
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
    error.cpp
    utility.hpp
)

# ************************************************************************* #

set_target_properties(shard-core PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
)

target_include_directories(shard-core
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..
)

# ************************************************************************* #

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

add_shard_library(shard-ast
    HEADERS
        Decl.hpp
        Expr.hpp
        Stmt.hpp
        StmtContainer.hpp
        Type.hpp
        utility.hpp
        Unit.hpp
    SOURCES
        Decl.cpp
        Expr.cpp
        Stmt.cpp
        StmtContainer.cpp
        Type.cpp
        Unit.cpp
    LIBRARIES
        shard-core
)

# ************************************************************************* #
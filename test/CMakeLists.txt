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

enable_testing()

add_executable(tokenizer-test tokenizer-test.cpp)
target_link_libraries(tokenizer-test gtest gtest_main)
target_link_libraries(tokenizer-test shard-tokenizer)

add_executable(source-test source-test.cpp)
target_link_libraries(source-test gtest gtest_main)
target_link_libraries(source-test shard-tokenizer stdc++fs)

add_test(tokenizer-test tokenizer-test)
add_test(source-test source-test)

# ************************************************************************* #
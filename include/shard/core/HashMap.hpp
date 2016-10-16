/* ************************************************************************* */
/* This file is part of Shard.                                               */
/*                                                                           */
/* Shard is free software: you can redistribute it and/or modify             */
/* it under the terms of the GNU Affero General Public License as            */
/* published by the Free Software Foundation.                                */
/*                                                                           */
/* This program is distributed in the hope that it will be useful,           */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the              */
/* GNU Affero General Public License for more details.                       */
/*                                                                           */
/* You should have received a copy of the GNU Affero General Public License  */
/* along with this program. If not, see <http://www.gnu.org/licenses/>.      */
/* ************************************************************************* */

#pragma once

/* ************************************************************************* */

// C++
#include <unordered_map>

/* ************************************************************************* */

namespace shard {
inline namespace v1 {

/* ************************************************************************* */

/**
 * @brief Hash map.
 * @tparam Key Key type.
 * @tparam T Value type.
 * @tparam Compare
 * @tparam Allocator
 */
template<typename Key, typename T, typename Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T>>>
using HashMap = std::unordered_map<Key, T, Compare, Allocator>;

/* ************************************************************************* */

}
}

/* ************************************************************************* */

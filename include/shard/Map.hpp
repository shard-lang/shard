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
#include <map>

/* ************************************************************************* */

namespace shard {

/* ************************************************************************* */

/**
 * @brief      Map type.
 *
 * @tparam     Key   Key type.
 * @tparam     T     Value type.
 */
template<typename Key, typename T>
using Map = std::map<Key, T>;

/* ************************************************************************* */

} // namespace shard

/* ************************************************************************* */

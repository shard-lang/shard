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
#include <string>
#include <type_traits>

/* ************************************************************************* */

namespace shard {
inline namespace v1 {

/* ************************************************************************* */

/**
 * @brief Basic string.
 */
using String = std::string;

/* ************************************************************************* */

/**
 * @brief Convert arithmetic value to string.
 * @param value
 */
template<typename T, typename = std::enable_if_t<std::is_arithmetic<T>::value>>
String toString(T value)
{
    return std::to_string(value);
}

/* ************************************************************************* */

}
}

/* ************************************************************************* */

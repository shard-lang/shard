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
#include <memory>

/* ************************************************************************* */

namespace shard {
inline namespace v1 {

/* ************************************************************************* */

/**
 * @brief Shared pointer.
 * @tparam T Type the pointer points to.
 */
template<typename T>
using SharedPtr = std::shared_ptr<T>;

/* ************************************************************************* */

/**
 * @brief Constructs an object of type T and wraps it in a SharedPtr using args as the parameter list for the constructor of T.
 * @tparam T
 * @param args List of arguments with which an instance of T will be constructed.
 * @return SharedPtr of an instance of type T.
 */
template<typename T, typename... Args>
SharedPtr<T> makeShared(Args&&... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

/* ************************************************************************* */

}
}

/* ************************************************************************* */

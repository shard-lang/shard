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
#include <type_traits>

/* ************************************************************************* */

namespace shard {

/* ************************************************************************* */

/**
 * @brief      Mark object as `move from`.
 * @see        std::move
 * @tparam     The   object type.
 * @param      The   object to be moved.
 * @return     Rvalue reference.
 */
template<typename T>
[[deprecated("use std::move")]] constexpr
    typename std::remove_reference<T>::type&&
    moveValue(T&& t) noexcept
{
    return static_cast<typename std::remove_reference<T>::type&&>(t);
}

/* ************************************************************************* */

/**
 * @brief      When used according to the following recipe in a function
 *             template, forwards the argument to another function with the
 *             value category it had when passed to the calling function.
 * @param      t     The object to be forwarded.
 * @return     Reference.
 */
template<typename T>
[[deprecated("use std::forward")]] constexpr T&& forwardValue(
    typename std::remove_reference<T>::type& t) noexcept
{
    return static_cast<T&&>(t);
}

/* ************************************************************************* */

/**
 * @brief      When used according to the following recipe in a function
 *             template, forwards the argument to another function with the
 *             value category it had when passed to the calling function.
 * @param      t     The object to be forwarded.
 * @return     Reference.
 */
template<typename T>
[[deprecated("use std::forward")]] constexpr T&& forwardValue(
    typename std::remove_reference<T>::type&& t) noexcept
{
    return static_cast<T&&>(t);
}

/* ************************************************************************* */

/**
 * @brief      Variable contains number of template arguments.
 * @tparam     ...   Args Types to count.
 */
template<typename... Args>
constexpr unsigned int ARG_COUNT = sizeof...(Args);

/* ************************************************************************* */

} // namespace shard

/* ************************************************************************* */

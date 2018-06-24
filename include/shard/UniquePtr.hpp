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

/* ************************************************************************* */

/**
 * @brief      RAII pointer wrapper.
 *
 * @tparam     T     Type the pointer points to.
 */
template<typename T>
using UniquePtr = std::unique_ptr<T>;

/* ************************************************************************* */

/**
 * @brief      Helper function for UniquePtr creation.
 *
 * @param      args       List of arguments with which an instance of T will
 *                        be constructed.
 *
 * @tparam     T          Constructed object type.
 * @tparam     Args       Construction arguments types.
 *
 * @return     UniquePtr of an instance of type T.
 */
template<typename T, typename... Args>
UniquePtr<T> makeUnique(Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

/* ************************************************************************* */

template<typename T>
class ViewPtr;

/* ************************************************************************* */

/**
 * @brief      Create view from unique pointer.
 *
 * @param      ptr   Unique pointer.
 *
 * @tparam     T     Object type.
 *
 * @return     View pointer.
 */
template<typename T>
ViewPtr<T> makeView(const UniquePtr<T>& ptr) noexcept
{
    return ViewPtr<T>(ptr.get());
}

/* ************************************************************************* */

} // namespace shard

/* ************************************************************************* */

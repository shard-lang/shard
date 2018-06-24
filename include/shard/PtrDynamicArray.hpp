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

// Shard
#include "shard/PtrVector.hpp"

/* ************************************************************************* */

namespace shard {

/* ************************************************************************* */

/**
 * @brief      Free storage allocated dynamic array of unique pointers.
 *
 * @tparam     T          Element type.
 * @tparam     Allocator  Allocator type.
 *
 * @deprecated "use PtrVector instead
 */
template<typename T>
using PtrDynamicArray [[deprecated("use PtrVector instead")]] = PtrVector<T>;

/* ************************************************************************* */

} // namespace shard

/* ************************************************************************* */

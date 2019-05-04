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
#include <utility>

// Shard
#include "shard/SourceRange.hpp"
#include "shard/UniquePtr.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

/**
 * @brief      Helper class for UniquePtr builder.
 *
 * @tparam     T     Node type.
 * @tparam     Args  Arguments.
 */
template<typename T, typename... Args>
struct PtrBuilder
{
    /**
     * @brief      Build Node function.
     *
     * @param      args   The arguments.
     * @param      range  The range.
     *
     * @return     UniquePtr<T>.
     */
    static UniquePtr<T> make(Args&&... args, SourceRange range = {})
    {
        return makeUnique<T>(std::forward<Args>(args)..., range);
    }
};

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

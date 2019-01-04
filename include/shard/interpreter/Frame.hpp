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
#include "shard/Map.hpp"
#include "shard/ir/Value.hpp"
#include "shard/interpreter/Value.hpp"

/* ************************************************************************* */

namespace shard::interpreter {

/* ************************************************************************* */

/**
 * @brief      Stack frame.
 */
class Frame
{

public:
    // Operations

    /**
     * @brief      Returns frame value.
     *
     * @param      val   IR value.
     *
     * @return     Reference to value.
     */
    Value& value(const ir::Value& val)
    {
        return m_values[&val];
    }

    /**
     * @brief      Returns frame result value.
     *
     * @return     Reference to value.
     */
    Value& result() noexcept
    {
        return m_result;
    }

private:
    // Data Members

    /// Frame values.
    Map<ViewPtr<const ir::Value>, Value> m_values;

    /// Result value.
    Value m_result;
};

/* ************************************************************************* */

} // namespace shard::interpreter

/* ************************************************************************* */

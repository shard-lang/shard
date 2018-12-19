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
#include <iosfwd>

// Shard
#include "shard/ir/Module.hpp"

/* ************************************************************************* */

namespace shard::ir {

/* ************************************************************************* */

/**
 * @brief      Write a module into output stream.
 *
 * @note       Be sure the output stream is open in binary mode.
 *
 * @param      output  The output stream.
 * @param      module  The module.
 */
void serialize(std::ostream& output, const Module& module);

/* ************************************************************************* */

/**
 * @brief      Read module from input stream.
 *
 * @note       Be sure the output stream is open in binary mode.
 *
 * @param      input  The input stream.
 *
 * @return     The loaded module.
 */
Module deserialize(std::istream& input);

/* ************************************************************************* */

} // namespace shard::ir

/* ************************************************************************* */

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

// Declaration
#include "shard/ir/Function.hpp"

/* ************************************************************************* */

namespace shard::ir {

/* ************************************************************************* */

Function::Function(
    String name,
    ViewPtr<Type> returnType,
    Vector<ViewPtr<Type>> parameterTypes)
    : m_name(std::move(name))
    , m_returnType(std::move(returnType))
    , m_parameterTypes(std::move(parameterTypes))
{
    m_arguments.resize(m_parameterTypes.size());

    for (size_t i = 0; i < m_parameterTypes.size(); ++i)
        m_arguments[i] = makeUnique<Value>(m_parameterTypes[i]);
}

/* ************************************************************************* */

} // namespace shard::ir

/* ************************************************************************* */

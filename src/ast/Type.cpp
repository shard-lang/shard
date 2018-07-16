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
#include "shard/ast/Type.hpp"

// Shard
#include "shard/Assert.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

Type::Type(TypeKind kind) noexcept
    : m_kind(kind)
{
    SHARD_ASSERT(m_kind != TypeKind::Typename);
}

/* ************************************************************************* */

Type::Type(String name)
    : m_kind(TypeKind::Typename)
    , m_name(std::move(name))
{
    // Nothing to do
}

/* ************************************************************************* */

bool operator==(const Type& lhs, const Type& rhs) noexcept
{
    if (!lhs.isBuiltin() && !rhs.isBuiltin())
        return lhs.getName() == rhs.getName();

    return lhs.getKind() == rhs.getKind();
}

/* ************************************************************************* */

}

/* ************************************************************************* */

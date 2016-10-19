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

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

Type::~Type() = default;

/* ************************************************************************* */

const Type TYPE_BUILTIN_VOID(TypeKind::Void);
const Type TYPE_BUILTIN_INT(TypeKind::Int);
const Type TYPE_BUILTIN_FLOAT(TypeKind::Float);
const Type TYPE_BUILTIN_CHAR(TypeKind::Char);
const Type TYPE_BUILTIN_STRING(TypeKind::String);
const Type TYPE_BUILTIN_VAR(TypeKind::Var);

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

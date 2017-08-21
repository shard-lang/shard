
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
#include "shard/interpreter/Symbol.hpp"

// Shard
#include "shard/Assert.hpp"
#include "shard/ast/Expr.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace interpreter {

/* ************************************************************************* */

Symbol::Symbol(ViewPtr<Scope> scope, SymbolKind kind) noexcept
    : m_scope(scope)
    , m_kind(kind)
    , m_value{}
{
    // Nothing to do
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

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
#include "shard/ast/decl/FunctionDecl.hpp"

// C++
#include <ostream>

// Shard
#include "shard/ast/DumpContext.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

void FunctionDecl::dump(const DumpContext& context) const
{
    context.header(this, "FunctionDecl")
        << " " << name() << " '(";

    for (size_t i = 0; i < m_parameters.size(); ++i)
    {
        if (i > 0)
            context << ", ";

        context << m_parameters[i]->type();
    }

    context << ") -> " << m_retType << "'\n";

    m_bodyStmt->dump(context.child());
}

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

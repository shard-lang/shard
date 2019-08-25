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
#include "shard/ast/decl/VariableDecl.hpp"

// C++
#include <ostream>

// Shard
#include "shard/ast/AnalysisContext.hpp"
#include "shard/ast/DumpContext.hpp"
#include "shard/ast/exceptions.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

void VariableDecl::analyse(AnalysisContext& context)
{
    auto decl = context.findDecl(name());

    if (decl)
        throw SemanticError(
            "redefinition of '" + name() + "'", sourceRange().start());

    context.addDecl(this);
}

/* ************************************************************************* */

void VariableDecl::dump(const DumpContext& context) const
{
    context.header(this, "VariableDecl")
        << " " << name() << " '" << m_type << "'"
        << "\n";

    if (m_initExpr)
        m_initExpr->dump(context.child());
}

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

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
#include "shard/ast/AnalysisContext.hpp"
#include "shard/ast/DumpContext.hpp"
#include "shard/ast/exceptions.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

void FunctionDecl::analyse(AnalysisContext& context)
{
    auto decl = context.findDecl(name());

    if (decl)
        throw SemanticError(
            "redefinition of '" + name() + "'", sourceRange().start());

    // Add declaration
    context.addDecl(this);

    auto ctx = context.push();

    for (auto& param : m_parameters)
        ctx.addDecl(param.get());

    m_bodyStmt->analyse(ctx);
}

/* ************************************************************************* */

void FunctionDecl::dump(const DumpContext& context) const
{
    context.header(this, "FunctionDecl") << " " << name() << " '(";

    for (size_t i = 0; i < m_parameters.size(); ++i)
    {
        if (i > 0)
            context << ", ";

        context << m_parameters[i]->type();
    }

    context << ") -> " << m_retType << "'\n";

    for (const auto& param : m_parameters)
        param->dump(context.child());

    m_bodyStmt->dump(context.child());
}

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

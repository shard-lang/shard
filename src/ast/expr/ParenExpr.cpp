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
#include "shard/ast/expr/ParenExpr.hpp"

// C++
#include <ostream>

// Shard
#include "shard/ast/DumpContext.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

void ParenExpr::analyse(AnalysisContext& context)
{
    m_expr->analyse(context);
}

/* ************************************************************************* */

void ParenExpr::dump(const DumpContext& context) const
{
    context.header(this, "ParenExpr") << "\n";

    m_expr->dump(context.child());
}

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

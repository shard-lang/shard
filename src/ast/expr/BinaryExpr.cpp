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
#include "shard/ast/expr/BinaryExpr.hpp"

// C++
#include <ostream>

// Shard
#include "shard/ast/DumpContext.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

void BinaryExpr::analyse(AnalysisContext& context)
{
    // TODO: analyse operator

    m_lhs->analyse(context);
    m_rhs->analyse(context);
}

/* ************************************************************************* */

void BinaryExpr::dump(const DumpContext& context) const
{
    context.header(this, "BinaryExpr") << " '" << m_operator << "' \n";

    m_lhs->dump(context.child());
    m_rhs->dump(context.child());
}

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

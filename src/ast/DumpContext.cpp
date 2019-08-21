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
#include "shard/ast/DumpContext.hpp"

// C++
#include <ostream>

// Shard
#include "shard/ast/Node.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

const DumpContext& DumpContext::operator<<(const SourceRange& range) const
    noexcept
{
    m_output << "<" << range.start().line() << ":" << range.start().column()
             << " -> " << range.end().line() << ":" << range.end().column()
             << ">";

    return *this;
}

/* ************************************************************************* */

const DumpContext& DumpContext::prefix() const noexcept
{
    for (int i = 0; i < m_level; ++i)
        m_output << " ";

    m_output << "-";

    return *this;
}

/* ************************************************************************* */

const DumpContext& DumpContext::header(
    ViewPtr<const Node> ptr,
    const char* name) const noexcept
{
    return prefix() << name << " " << this << " " << ptr->sourceRange();
}

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

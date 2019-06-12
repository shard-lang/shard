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

#include "shard/tokenizer/Source.hpp"

/* ************************************************************************* */

// C++
#include <algorithm>

/* ************************************************************************* */

namespace shard::tokenizer {

/* ************************************************************************* */

void Source::process(const String& source)
{
    // Result size will be same or smaller than source
    m_source.reserve(source.size());

    // First line starts at position 0
    m_lines.push_back(0);

    // Foreach characters
    for (std::size_t i = 0; i < source.size(); ++i)
    {
        // NOTE: Is safe when `i` is last character, the standard specifies the
        // following character will be `\0`.
        if (source[i] == '\r' && source[i + 1] == '\n')
        {
            // Store new line and advance
            m_source.push_back('\n');
            ++i;
            m_lines.push_back(m_source.size());
        }
        else if (source[i] == '\n')
        {
            m_source.push_back(source[i]);
            m_lines.push_back(m_source.size());
        }
        else
        {
            m_source.push_back(source[i]);
        }
    }
}

/* ************************************************************************* */

SourceLocation Source::location(std::size_t position) const noexcept
{
    // The array contains sorted positions. At first it will find first element
    // which is greater than position so we need to get the previous one.
    auto it =
        std::prev(std::upper_bound(m_lines.begin(), m_lines.end(), position));

    // Line is index in the array + 1
    const int line   = std::distance(m_lines.begin(), it) + 1;
    const int column = position - *it + 1;

    return SourceLocation{line, column};
}

/* ************************************************************************* */

} // namespace shard::tokenizer

/* ************************************************************************* */

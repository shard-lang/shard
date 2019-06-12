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

#include "shard/tokenizer/SourceIterator.hpp"

/* ************************************************************************* */

// Shard
#include "shard/tokenizer/Source.hpp"

/* ************************************************************************* */

namespace shard::tokenizer {

/* ************************************************************************* */

char SourceIterator::operator*() const noexcept
{
    return (*m_source)[m_position];
}

/* ************************************************************************* */

SourceLocation SourceIterator::location() const noexcept
{
    return m_source->location(m_position);
}

/* ************************************************************************* */

} // namespace shard::tokenizer

/* ************************************************************************* */

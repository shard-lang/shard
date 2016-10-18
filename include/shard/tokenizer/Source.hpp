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

#pragma once

/* ************************************************************************* */

#include <fstream>

// Shard
#include "shard/Path.hpp"
#include "shard/String.hpp"
#include "shard/UniquePtr.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace tokenizer {

/* ************************************************************************* */

using ReadMode = char;

class Source
{
    UniquePtr<std::basic_streambuf<ReadMode>> m_sb;

public:

    /**
     * @brief input from file
     */
    explicit Source (const Path& path):
            m_sb([](const auto& l_path)
            {
                auto ptr = makeUnique<std::basic_filebuf<ReadMode>>();
                ptr->open(l_path, std::ios_base::in | std::ios_base::binary);
                return ptr;
            }(path)) {}

    /**
     * @brief input from string
     */
    explicit Source (const String& source):
            m_sb(makeUnique<std::basic_stringbuf<ReadMode>>(source)) {}

/* ************************************************************************* */

public:

    /**
     * @brief returns if imput is empty
     */
    inline bool empty()
    {
        return getCurrent() == std::char_traits<ReadMode>::eof();
        //return m_sb->in_avail() <= 0;
    }

    /**
     * @brief read current character
     */
    inline ReadMode getCurrent()
    {
        return (ReadMode) m_sb->sgetc();
    }

    /**
     * @brief read current character and move to next
     */
    inline ReadMode extract()
    {
        return (ReadMode) m_sb->sbumpc();
    }

    /**
     * @brief move to next character and read it
     */
    inline ReadMode getNext()
    {
        return (ReadMode) m_sb->snextc();
    }
};

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

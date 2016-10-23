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
#include "shard/ViewPtr.hpp"
#include "shard/UniquePtr.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace tokenizer {

/* ************************************************************************* */

using ReadMode = char;

/* ************************************************************************* */

class Source; //FWD declaration

/* ************************************************************************* */

class SourceIterator
{

protected:

    ViewPtr<Source> m_source;

public:

    /**
     * @brief constructs empty SourceIterator.
     */
    SourceIterator() = default;

    /**
     * @brief constructs SourceIterator for given Source.
     */
    explicit SourceIterator(ViewPtr<Source> source):
        m_source(source) {}

    inline ReadMode operator*() const;
    inline SourceIterator& operator++();
    inline SourceIterator operator++(int);

    /**
     * @brief returns pointer to related Source.
     */
    inline ViewPtr<Source> getSource() const noexcept
    {
        return m_source;
    }
};

/* ************************************************************************* */

inline bool operator==(const SourceIterator& lhs, const SourceIterator& rhs)
{
    return (lhs.getSource() == nullptr || (*lhs) == std::char_traits<ReadMode>::eof())
        && (rhs.getSource() == nullptr || (*rhs) == std::char_traits<ReadMode>::eof());
}

inline bool operator!=(const SourceIterator& lhs, const SourceIterator& rhs)
{
    return !(lhs == rhs);
}

/* ************************************************************************* */

class Source
{

protected:

    UniquePtr<std::basic_streambuf<ReadMode>> m_sb;

public:

    /**
     * @brief constructs Source with input from file.
     */
    explicit Source (const Path& path):
            m_sb([](const auto& l_path)
            {
                auto ptr = makeUnique<std::basic_filebuf<ReadMode>>();
                ptr->open(l_path, std::ios_base::in | std::ios_base::binary);
                return ptr;
            }(path)) {}

    /**
     * @brief constructs Source with input from string.
     */
    explicit Source (const String& source):
            m_sb(makeUnique<std::basic_stringbuf<ReadMode>>(source)) {}

/* ************************************************************************* */

public:

    /**
     * @brief returns if input is empty.
     */
    inline bool empty()
    {
        return get() == std::char_traits<ReadMode>::eof();
        //return m_sb->in_avail() <= 0;
    }

    /**
     * @brief read current character.
     */
    inline int get()
    {
        return m_sb->sgetc();
    }

    /**
     * @brief read current character and move to next.
     */
    inline int extract()
    {
        return m_sb->sbumpc();
    }

    /**
     * @brief move to next character and read it.
     */
    inline int getNext()
    {
        return m_sb->snextc();
    }

    /**
     * @brief return to previous character and read it.
     */
    inline int unget()
    {
        return m_sb->sungetc();
    }

    /* ************************************************************************* */

public:

    /**
     * @brief returns tokenizer iterator pointing to currect token.
     */
    inline SourceIterator begin() noexcept
    {
        return SourceIterator(this);
    }

    /**
     * @brief returns tokenizer iterator pointing to token with end.
     */
    inline SourceIterator end() noexcept
    {
        return SourceIterator(nullptr);
    }
};

/* ************************************************************************* */

inline int SourceIterator::operator*() const
{
    return m_source->get();
}

inline SourceIterator& SourceIterator::operator++()
{
    m_source->extract();
    return *this;
}

inline SourceIterator SourceIterator::operator++(int)
{
    SourceIterator tmp(*this);
    operator++();
    return tmp;
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

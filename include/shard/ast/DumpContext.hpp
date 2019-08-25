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

// C++
#include <iosfwd>

// Shard
#include "shard/Set.hpp"
#include "shard/SourceLocation.hpp"
#include "shard/SourceRange.hpp"
#include "shard/ViewPtr.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

class Node;

/* ************************************************************************* */

/**
 * @brief      Helper class for dumping AST to stream.
 */
class DumpContext
{
public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      output  The output stream.
     * @param      level   The level.
     */
    explicit DumpContext(std::ostream& output, int level = 0) noexcept
        : m_output(output)
        , m_level(level)
    {
        // Nothing to do
    }

public:
    // Operators

    /**
     * @brief      Write source range.
     *
     * @param      range  The source range.
     *
     * @return     *this.
     */
    const DumpContext& operator<<(const SourceRange& range) const noexcept;

    /**
     * @brief      Write value.
     *
     * @param      value  The value.
     *
     * @tparam     T      Type of writen value.
     *
     * @return     *this.
     */
    template<typename T>
    const DumpContext& operator<<(const T& value) const
    {
        m_output << value;
        return *this;
    }

public:
    // Operators

    /**
     * @brief      Create child context.
     *
     * @return     Child context.
     */
    DumpContext child() const noexcept
    {
        return DumpContext{m_output, m_level + 1};
    }

    /**
     * @brief      Dump child nodes.
     *
     * @param      container  The container with child nodes.
     *
     * @tparam     Container  The container type.
     */
    template<typename Container>
    void childs(Container& container) const noexcept
    {
        auto context = child();

        for (const auto& node : container)
            node->dump(context);
    }

    /**
     * @brief      Dump new line prefix.
     *
     * @return     *this.
     */
    const DumpContext& prefix() const noexcept;

    /**
     * @brief      Dump node header.
     *
     * @param      ptr   The pointer to node.
     * @param      name  The node name.
     *
     * @return     *this.
     */
    const DumpContext& header(ViewPtr<const Node> ptr, const char* name) const
        noexcept;

private:
    // Data Members

    /// Output stream.
    std::ostream& m_output;

    /// Indentation level.
    int m_level;
};

/* ************************************************************************* */

} // namespace shard::ast

/* ************************************************************************* */

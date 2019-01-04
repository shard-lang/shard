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

// Shard
#include "shard/PtrVector.hpp"
#include "shard/String.hpp"
#include "shard/ir/Block.hpp"
#include "shard/ir/Type.hpp"

/* ************************************************************************* */

namespace shard::ir {

/* ************************************************************************* */

/**
 * @brief      Function declaration.
 */
class Function
{

public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      name            The name.
     * @param      returnType      The return type.
     * @param      parameterTypes  The parameter types.
     */
    Function(
        String name,
        ViewPtr<Type> returnType,
        Vector<ViewPtr<Type>> parameterTypes);

    /**
     * @brief      Constructor.
     *
     * @param      name            The name.
     * @param      returnType      The return type.
     * @param      parameterTypes  The parameter types.
     */
    Function(String name, Vector<ViewPtr<Type>> parameterTypes)
        : Function(std::move(name), nullptr, std::move(parameterTypes))
    {
        // Nothing to do
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns function name.
     *
     * @return     The name.
     */
    const String& name() const noexcept
    {
        return m_name;
    }

    /**
     * @brief      Set function name.
     *
     * @param      name  The name.
     */
    void setName(String name) noexcept
    {
        m_name = std::move(name);
    }

    /**
     * @brief      Return function return type.
     *
     * @return     The return type. Can be nullptr if function doesn't return
     *             value.
     */
    ViewPtr<Type> returnType() const noexcept
    {
        return m_returnType;
    }

    /**
     * @brief      Return a list of parameter types.
     *
     * @return     The parameter types.
     */
    const Vector<ViewPtr<Type>>& parameterTypes() const noexcept
    {
        return m_parameterTypes;
    }

    /**
     * @brief      Return the function blocks.
     *
     * @return     The block.
     */
    const PtrVector<Block>& blocks() const noexcept
    {
        return m_blocks;
    }

    /**
     * @brief      Set the function blocks.
     *
     * @param      blocks  The blocks.
     */
    void setBlocks(PtrVector<Block> blocks)
    {
        m_blocks = std::move(blocks);
    }

    /**
     * @brief      Adds a block.
     *
     * @param      block  The block
     */
    ViewPtr<Block> addBlock(UniquePtr<Block> block)
    {
        m_blocks.push_back(std::move(block));
        return m_blocks.back().get();
    }

    /**
     * @brief      Create a new block.
     *
     * @return     The block.
     */
    ViewPtr<Block> createBlock()
    {
        return addBlock(makeUnique<Block>());
    }

    /**
     * @brief      Return the arguments.
     *
     * @return     The arguments.
     */
    const PtrVector<Value>& arguments() const noexcept
    {
        return m_arguments;
    }

    /**
     * @brief      Returns argument value.
     *
     * @param      pos   The position.
     *
     * @return     Argument value.
     *
     * @pre        `pos < parameterTypes().size()`
     */
    ViewPtr<Value> arg(size_t pos)
    {
        return m_arguments[pos].get();
    }

    /**
     * @brief      Returns argument value.
     *
     * @param      pos   The position.
     *
     * @return     Argument value.
     *
     * @pre        `pos < parameterTypes().size()`
     */
    ViewPtr<const Value> arg(size_t pos) const
    {
        return m_arguments[pos].get();
    }

private:
    // Data Members

    /// Function name.
    String m_name;

    /// Return type.
    ViewPtr<Type> m_returnType;

    /// Parameter types
    Vector<ViewPtr<Type>> m_parameterTypes;

    /// Function blocks.
    PtrVector<Block> m_blocks;

    /// Values representing arguments.
    PtrVector<Value> m_arguments;
};

/* ************************************************************************* */

} // namespace shard::ir

/* ************************************************************************* */

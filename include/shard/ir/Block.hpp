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
#include "shard/UniquePtr.hpp"
#include "shard/ir/Instruction.hpp"

/* ************************************************************************* */

namespace shard::ir {

/* ************************************************************************* */

/**
 * @brief      Block of instructions.
 */
class Block
{

public:
    // Accessors & Mutators

    /**
     * @brief      Returns block instructions.
     *
     * @return     The list of instructions.
     */
    const PtrVector<Instruction>& instructions() const noexcept
    {
        return m_instructions;
    }

    /**
     * @brief      Returns block number of instructions.
     *
     * @return     The number of instructions.
     */
    size_t size() const noexcept
    {
        return m_instructions.size();
    }

    /**
     * @brief      Sets the instructions.
     *
     * @param      instructions  The instructions.
     */
    void setInstructions(PtrVector<Instruction> instructions)
    {
        m_instructions = std::move(instructions);
    }

    /**
     * @brief      Add a new instruction.
     *
     * @param      instruction  The instruction.
     *
     * @return     Pointer to stored instruction.
     */
    ViewPtr<Instruction> addInstruction(UniquePtr<Instruction> instruction)
    {
        m_instructions.push_back(std::move(instruction));
        return m_instructions.back().get();
    }

    /**
     * @brief      Create a new instruction.
     *
     * @param      args  The arguments.
     *
     * @tparam     T     Instruction type.
     * @tparam     Args  Argument types.
     *
     * @return     The created instruction.
     */
    template<typename T, typename... Args>
    ViewPtr<T> createInstruction(Args&&... args)
    {
        auto ptr = addInstruction(makeUnique<T>(std::forward<Args>(args)...));

        return static_cast<T*>(ptr.get());
    }

private:
    // Data Members

    /// Block instructions.
    PtrVector<Instruction> m_instructions;
};

/* ************************************************************************* */

} // namespace shard::ir

/* ************************************************************************* */

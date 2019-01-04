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
#include <stack>

// Shard
#include "shard/ViewPtr.hpp"
#include "shard/StringView.hpp"
#include "shard/interpreter/Frame.hpp"
#include "shard/interpreter/Value.hpp"

/* ************************************************************************* */

namespace shard::ir {

/* ************************************************************************* */

class Module;
class Function;
class Block;
class Instruction;
class InstructionAlloc;
class InstructionStore;
class InstructionLoad;
class InstructionAdd;
class InstructionSub;
class InstructionMul;
class InstructionDiv;
class InstructionRem;
class InstructionCmp;
class InstructionAnd;
class InstructionOr;
class InstructionXor;
class InstructionBranch;
class InstructionBranchCondition;
class InstructionCall;
class InstructionReturn;
class InstructionReturnVoid;

/* ************************************************************************* */

} // namespace shard::ir

/* ************************************************************************* */

namespace shard::interpreter {

/* ************************************************************************* */

/**
 * @brief      Shard IR interpreter.
 */
class Interpreter
{

public:
    // Accessors & Mutators

    /**
     * @brief      Returns current frame.
     *
     * @return     The frame.
     */
    Frame& currentFrame()
    {
        return m_stack.top();
    }

    /**
     * @brief      Returns current frame.
     *
     * @return     The frame.
     */
    const Frame& currentFrame() const
    {
        return m_stack.top();
    }

public:
    // Operations

    /**
     * @brief      Load module into interpreter.
     *
     * @details    This function imports symbols from the module into
     *             interpreter so they can be used.
     *
     * @param      module  The module.
     */
    void load(const ir::Module& module);

    /**
     * @brief      Call given function with given arguments.
     *
     * @details    It create a new stack frame where the function is executed.
     *
     * @param      name  The function name.
     * @param      args  The arguments.
     *
     * @return     The returned value. Might be nothing if function returning null.
     */
    Value call(StringView name, const Vector<Value>& args);

private:
    // Operations

    /**
     * @brief      Convert IR value to runtime value.
     *
     * @details    The IR value can be reference to runtime value or constant.
     *             This function converts to usable value.
     *
     * @param      value  The value.
     *
     * @return     The value.
     */
    Value fetchValue(const ir::Value& value);

    /**
     * @brief      Evaluate block in current frame.
     *
     * @param      block  The block.
     */
    void evalBlock(const ir::Block& block);

    /**
     * @brief      Evaluate instruction in current frame.
     *
     * @param      instr  The instruction.
     */
    void evalInstruction(const ir::Instruction& instr);

    /**
     * @brief      Evaluate instruction in current frame.
     *
     * @param      instr  The instruction.
     */
    void evalInstruction(const ir::InstructionAlloc& instr);

    /**
     * @brief      Evaluate instruction in current frame.
     *
     * @param      instr  The instruction.
     */
    void evalInstruction(const ir::InstructionStore& instr);

    /**
     * @brief      Evaluate instruction in current frame.
     *
     * @param      instr  The instruction.
     */
    void evalInstruction(const ir::InstructionLoad& instr);

    /**
     * @brief      Evaluate instruction in current frame.
     *
     * @param      instr  The instruction.
     */
    void evalInstruction(const ir::InstructionAdd& instr);

    /**
     * @brief      Evaluate instruction in current frame.
     *
     * @param      instr  The instruction.
     */
    void evalInstruction(const ir::InstructionSub& instr);

    /**
     * @brief      Evaluate instruction in current frame.
     *
     * @param      instr  The instruction.
     */
    void evalInstruction(const ir::InstructionMul& instr);

    /**
     * @brief      Evaluate instruction in current frame.
     *
     * @param      instr  The instruction.
     */
    void evalInstruction(const ir::InstructionDiv& instr);

    /**
     * @brief      Evaluate instruction in current frame.
     *
     * @param      instr  The instruction.
     */
    void evalInstruction(const ir::InstructionRem& instr);

    /**
     * @brief      Evaluate instruction in current frame.
     *
     * @param      instr  The instruction.
     */
    void evalInstruction(const ir::InstructionCmp& instr);

    /**
     * @brief      Evaluate instruction in current frame.
     *
     * @param      instr  The instruction.
     */
    void evalInstruction(const ir::InstructionAnd& instr);

    /**
     * @brief      Evaluate instruction in current frame.
     *
     * @param      instr  The instruction.
     */
    void evalInstruction(const ir::InstructionOr& instr);

    /**
     * @brief      Evaluate instruction in current frame.
     *
     * @param      instr  The instruction.
     */
    void evalInstruction(const ir::InstructionXor& instr);

    /**
     * @brief      Evaluate instruction in current frame.
     *
     * @param      instr  The instruction.
     */
    void evalInstruction(const ir::InstructionBranch& instr);

    /**
     * @brief      Evaluate instruction in current frame.
     *
     * @param      instr  The instruction.
     */
    void evalInstruction(const ir::InstructionBranchCondition& instr);

    /**
     * @brief      Evaluate instruction in current frame.
     *
     * @param      instr  The instruction.
     */
    void evalInstruction(const ir::InstructionCall& instr);

    /**
     * @brief      Evaluate instruction in current frame.
     *
     * @param      instr  The instruction.
     */
    void evalInstruction(const ir::InstructionReturn& instr);

    /**
     * @brief      Evaluate instruction in current frame.
     *
     * @param      instr  The instruction.
     */
    void evalInstruction(const ir::InstructionReturnVoid& instr);

private:
    // Data Members

    /// Frame stack.
    std::stack<Frame> m_stack;

    /// Loaded modules.
    Vector<ViewPtr<const ir::Module>> m_modules;
};

/* ************************************************************************* */

} // namespace shard::interpreter

/* ************************************************************************* */

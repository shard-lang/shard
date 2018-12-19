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
#include "shard/Assert.hpp"
#include "shard/UniquePtr.hpp"
#include "shard/ViewPtr.hpp"
#include "shard/ir/Type.hpp"
#include "shard/ir/Value.hpp"

/* ************************************************************************* */

namespace shard::ir {

/* ************************************************************************* */

class Block;

/* ************************************************************************* */

/**
 * @brief      Type kind instructions.
 */
enum class InstructionKind
{
    Alloc,
    Store,
    Load,
    Add,
    Sub,
    Mul,
    Div,
    Rem,
    Cmp,
    And,
    Or,
    Xor,
    Branch,
    BranchCondition,
    Call,
    Return,
    ReturnVoid,
};

/* ************************************************************************* */

/**
 * @brief      Instruction.
 */
class Instruction
{

public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      kind  The instruction kind.
     */
    explicit Instruction(InstructionKind kind) noexcept
        : m_kind(kind)
    {
        // Nothing to do
    }

    /**
     * @brief      Destructor.
     */
    virtual ~Instruction() = default;

public:
    // Accessors & Mutators

    /**
     * @brief      Returns instruction kind.
     *
     * @return     The instruction kind.
     */
    InstructionKind kind() const noexcept
    {
        return m_kind;
    }

    /**
     * @brief      Check if this instruction is required instruction.
     *
     * @tparam     T     The required instruction.
     *
     * @return     If this is the required instruction.
     */
    template<typename T>
    bool is() const noexcept
    {
        return T::typeKind == kind();
    }

    /**
     * @brief      Convert this pointer to required instruction.
     *
     * @tparam     T     The required instruction.
     *
     * @return     A reference to required instruction.
     */
    template<typename T>
    T& as()
    {
        SHARD_ASSERT(is<T>());
        return static_cast<T&>(*this);
    }

    /**
     * @brief      Convert this pointer to required instruction.
     *
     * @tparam     T     The required instruction.
     *
     * @return     A reference to required instruction.
     */
    template<typename T>
    const T& as() const
    {
        SHARD_ASSERT(is<T>());
        return static_cast<const T&>(*this);
    }

private:
    // Data Members

    /// The instruction kind.
    InstructionKind m_kind;
};

/* ************************************************************************* */

/**
 * @brief      Instruction with result value.
 */
class ResultInstruction : public Instruction
{
public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      kind    The instruction kind.
     * @param      result  The result value.
     */
    explicit ResultInstruction(InstructionKind kind, UniquePtr<Value> result)
        : Instruction(kind)
        , m_result(std::move(result))
    {
        // Nothing to do
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns result value.
     *
     * @return     The result value.
     */
    ViewPtr<Value> result() const noexcept
    {
        return m_result.get();
    }

    /**
     * @brief      Returns result type.
     *
     * @return     The result type.
     */
    ViewPtr<Type> resultType() const noexcept
    {
        return m_result ? m_result->type() : nullptr;
    }

private:
    // Data Members

    /// The result value.
    UniquePtr<Value> m_result;
};

/* ************************************************************************* */

/**
 * @brief      Allocate instruction.
 *
 * @details    Allocate memory for local variable.
 */
class InstructionAlloc : public ResultInstruction
{
public:
    // Constants

    /// Kind constant
    static constexpr InstructionKind typeKind = InstructionKind::Alloc;

public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      type   The type the memory allocate for.
     * @param      count  The number of elements.
     */
    explicit InstructionAlloc(ViewPtr<Type> type, unsigned count = 1u)
        : ResultInstruction(typeKind, makeUnique<Value>(&m_pointerType))
        , m_pointerType(type)
        , m_count(count)
    {
        // Nothing to do
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns pointee type.
     *
     * @return     The type.
     */
    ViewPtr<Type> type() const noexcept
    {
        return m_pointerType.type();
    }

    /**
     * @brief      Returns number of allocated elements.
     *
     * @return     The number of elements.
     */
    unsigned count() const noexcept
    {
        return m_count;
    }

private:
    // Data Members

    /// The pointer type.
    TypePointer m_pointerType;

    /// Number of elements.
    unsigned m_count;
};

/* ************************************************************************* */

/**
 * @brief      Store variable to memory instruction.
 */
class InstructionStore : public Instruction
{
public:
    // Constants

    /// Kind constant
    static constexpr InstructionKind typeKind = InstructionKind::Store;

public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      pointer  The destination pointer.
     * @param      value    The value to store.
     * @param      index    The element index.
     */
    explicit InstructionStore(
        ViewPtr<Value> pointer,
        ViewPtr<Value> value,
        unsigned index = 0)
        : Instruction(typeKind)
        , m_pointer(pointer)
        , m_value(value)
        , m_index(index)
    {
        // Nothing to do
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns pointer value.
     *
     * @return     The pointer.
     */
    ViewPtr<Value> pointer() const noexcept
    {
        return m_pointer;
    }

    /**
     * @brief      Returns value.
     *
     * @return     The value.
     */
    ViewPtr<Value> value() const noexcept
    {
        return m_value;
    }

    /**
     * @brief      Returns the load element index.
     *
     * @return     The index.
     */
    unsigned index() const noexcept
    {
        return m_index;
    }

private:
    // Data Members

    /// The destination pointer.
    ViewPtr<Value> m_pointer;

    /// The value to store.
    ViewPtr<Value> m_value;

    /// The element index.
    unsigned m_index;
};

/* ************************************************************************* */

/**
 * @brief      Load memory to variable instruction.
 */
class InstructionLoad : public ResultInstruction
{
public:
    // Constants

    /// Kind constant
    static constexpr InstructionKind typeKind = InstructionKind::Load;

public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      pointer  The source pointer.
     * @param      index    The index.
     */
    explicit InstructionLoad(ViewPtr<Value> pointer, unsigned index = 0)
        : ResultInstruction(
              typeKind,
              makeUnique<Value>(pointer->type<TypePointer>().type()))
        , m_pointer(pointer)
        , m_index(index)
    {
        // Nothing to do
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns pointer value.
     *
     * @return     The pointer.
     */
    ViewPtr<Value> pointer() const noexcept
    {
        return m_pointer;
    }

    /**
     * @brief      Returns the load element index.
     *
     * @return     The index.
     */
    unsigned index() const noexcept
    {
        return m_index;
    }

private:
    // Data Members

    /// The source pointer.
    ViewPtr<Value> m_pointer;

    /// The element index.
    unsigned m_index;
};

/* ************************************************************************* */

/**
 * @brief      Binary instruction - with two operands.
 *
 * @tparam     KIND  The binary operation instruction kind.
 */
template<InstructionKind KIND>
class InstructionBinary : public ResultInstruction
{
public:
    // Constants

    /// Kind constant
    static constexpr InstructionKind typeKind = KIND;

public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      type    The working type.
     * @param      value1  The first value.
     * @param      value2  The second value.
     */
    InstructionBinary(
        ViewPtr<Type> type,
        ViewPtr<Value> value1,
        ViewPtr<Value> value2)
        : ResultInstruction(typeKind, makeUnique<Value>(type))
        , m_value1(value1)
        , m_value2(value2)
    {
        // Nothing to do
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns working type.
     *
     * @return     The type.
     */
    ViewPtr<Type> type() const noexcept
    {
        return resultType();
    }

    /**
     * @brief      Returns the first value.
     *
     * @return     The first value.
     */
    ViewPtr<Value> value1() const noexcept
    {
        return m_value1;
    }

    /**
     * @brief      Returns the second value.
     *
     * @return     The second value.
     */
    ViewPtr<Value> value2() const noexcept
    {
        return m_value2;
    }

private:
    // Data Members

    /// The first value
    ViewPtr<Value> m_value1;

    /// The second value.
    ViewPtr<Value> m_value2;
};

/* ************************************************************************* */

/**
 * @brief      Add instruction.
 */
class InstructionAdd : public InstructionBinary<InstructionKind::Add>
{
public:
    // Ctors & Dtors

    // Parent constructor.
    using InstructionBinary::InstructionBinary;
};

/* ************************************************************************* */

/**
 * @brief      Sub instruction.
 */
class InstructionSub : public InstructionBinary<InstructionKind::Sub>
{
public:
    // Ctors & Dtors

    // Parent constructor.
    using InstructionBinary::InstructionBinary;
};

/* ************************************************************************* */

/**
 * @brief      Mul instruction.
 */
class InstructionMul : public InstructionBinary<InstructionKind::Mul>
{
public:
    // Ctors & Dtors

    // Parent constructor.
    using InstructionBinary::InstructionBinary;
};

/* ************************************************************************* */

/**
 * @brief      Div instruction.
 */
class InstructionDiv : public InstructionBinary<InstructionKind::Div>
{
public:
    // Ctors & Dtors

    // Parent constructor.
    using InstructionBinary::InstructionBinary;
};

/* ************************************************************************* */

/**
 * @brief      Rem instruction.
 */
class InstructionRem : public InstructionBinary<InstructionKind::Rem>
{
public:
    // Ctors & Dtors

    // Parent constructor.
    using InstructionBinary::InstructionBinary;
};

/* ************************************************************************* */

/**
 * @brief      Cmp instruction.
 */
class InstructionCmp : public InstructionBinary<InstructionKind::Cmp>
{
public:
    // Enums

    /// Comparision operation
    enum class Operation
    {
        Equal,
        NotEqual,
        GreaterThan,
        GreaterEqual,
        LessThan,
        LessEqual,
    };

public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      operation  The comparision operation.
     * @param      type       The working type.
     * @param      value1     The first value.
     * @param      value2     The second value.
     */
    InstructionCmp(
        Operation operation,
        ViewPtr<Type> type,
        ViewPtr<Value> value1,
        ViewPtr<Value> value2)
        : InstructionBinary(type, value1, value2)
        , m_operation(operation)
    {
        // Nothing to do
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns comparision operation.
     *
     * @return     The comparision operation.
     */
    Operation operation() const noexcept
    {
        return m_operation;
    }

private:
    // Data Members

    /// The operation.
    Operation m_operation;
};

/* ************************************************************************* */

/**
 * @brief      And instruction.
 */
class InstructionAnd : public InstructionBinary<InstructionKind::And>
{
public:
    // Ctors & Dtors

    // Parent constructor.
    using InstructionBinary::InstructionBinary;
};

/* ************************************************************************* */

/**
 * @brief      Or instruction.
 */
class InstructionOr : public InstructionBinary<InstructionKind::Or>
{
public:
    // Ctors & Dtors

    // Parent constructor.
    using InstructionBinary::InstructionBinary;
};

/* ************************************************************************* */

/**
 * @brief      Xor instruction.
 */
class InstructionXor : public InstructionBinary<InstructionKind::Xor>
{
public:
    // Ctors & Dtors

    // Parent constructor.
    using InstructionBinary::InstructionBinary;
};

/* ************************************************************************* */

/**
 * @brief      Unconditional branching instruction.
 */
class InstructionBranch : public Instruction
{
public:
    // Constants

    /// Kind constant
    static constexpr InstructionKind typeKind = InstructionKind::Branch;

public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      block  The block jump to.
     */
    explicit InstructionBranch(ViewPtr<Block> block)
        : Instruction(typeKind)
        , m_block(block)
    {
        // Nothing to do
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns the block jump to.
     *
     * @return     The block.
     */
    ViewPtr<Block> block() const noexcept
    {
        return m_block;
    }

private:
    // Data Members

    /// The block jump to.
    ViewPtr<Block> m_block;
};

/* ************************************************************************* */

/**
 * @brief      Conditional branching instruction.
 */
class InstructionBranchCondition : public Instruction
{
public:
    // Constants

    /// Kind constant
    static constexpr InstructionKind typeKind =
        InstructionKind::BranchCondition;

public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      condition   The condition
     * @param      blockTrue   The block true
     * @param      blockFalse  The block false
     */
    explicit InstructionBranchCondition(
        ViewPtr<Value> condition,
        ViewPtr<Block> blockTrue,
        ViewPtr<Block> blockFalse)
        : Instruction(typeKind)
        , m_condition(condition)
        , m_blockTrue(blockTrue)
        , m_blockFalse(blockFalse)
    {
        // Nothing to do
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns the condition value.
     *
     * @return     The condition value.
     */
    ViewPtr<Value> condition() const noexcept
    {
        return m_condition;
    }

    /**
     * @brief      Returns the block jump to.
     *
     * @return     The block.
     */
    ViewPtr<Block> blockTrue() const noexcept
    {
        return m_blockTrue;
    }

    /**
     * @brief      Returns the block jump to.
     *
     * @return     The block.
     */
    ViewPtr<Block> blockFalse() const noexcept
    {
        return m_blockFalse;
    }

private:
    // Data Members

    /// The condition.
    ViewPtr<Value> m_condition;

    /// The block jump to if condition is true.
    ViewPtr<Block> m_blockTrue;

    /// The block jump to if condition is false.
    ViewPtr<Block> m_blockFalse;
};

/* ************************************************************************* */

/**
 * @brief      Function call instruction.
 */
class InstructionCall : public ResultInstruction
{
public:
    // Constants

    /// Kind constant
    static constexpr InstructionKind typeKind = InstructionKind::Call;

public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      name        The called function name.
     * @param      returnType  The return type.
     * @param      arguments   The arguments used for calling function.
     */
    InstructionCall(
        String name,
        ViewPtr<Type> returnType,
        Vector<ViewPtr<Value>> arguments)
        : ResultInstruction(typeKind, makeUnique<Value>(returnType))
        , m_name(std::move(name))
        , m_arguments(std::move(arguments))
    {
        // Nothing to do
    }

    /**
     * @brief      Constructor.
     *
     * @param      name        The called function name.
     * @param      arguments   The arguments used for calling function.
     */
    InstructionCall(String name, Vector<ViewPtr<Value>> arguments)
        : ResultInstruction(typeKind, nullptr)
        , m_name(std::move(name))
        , m_arguments(std::move(arguments))
    {
        // Nothing to do
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns callee name.
     *
     * @return     The called function name.
     */
    const String& name() const noexcept
    {
        return m_name;
    }

    /**
     * @brief      Returns calling arguments.
     *
     * @return     The arguments.
     */
    const Vector<ViewPtr<Value>>& arguments() const noexcept
    {
        return m_arguments;
    }

private:
    // Data Members

    /// Called function name.
    String m_name;

    /// Call arguments.
    Vector<ViewPtr<Value>> m_arguments;
};

/* ************************************************************************* */

/**
 * @brief      Return void instruction.
 */
class InstructionReturnVoid : public Instruction
{
public:
    // Constants

    /// Kind constant
    static constexpr InstructionKind typeKind = InstructionKind::ReturnVoid;

public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     */
    InstructionReturnVoid()
        : Instruction(typeKind)
    {
        // Nothing to do
    }
};

/* ************************************************************************* */

/**
 * @brief      Return instruction.
 */
class InstructionReturn : public Instruction
{
public:
    // Constants

    /// Kind constant
    static constexpr InstructionKind typeKind = InstructionKind::Return;

public:
    // Ctors & Dtors

    /**
     * @brief      Constructor.
     *
     * @param      type   The return type.
     * @param      value  The value type.
     */
    explicit InstructionReturn(ViewPtr<Type> type, ViewPtr<Value> value)
        : Instruction(typeKind)
        , m_type(type)
        , m_value(value)
    {
        // Nothing to do
    }

public:
    // Accessors & Mutators

    ViewPtr<Type> type() const noexcept
    {
        return m_type;
    }

    /// The return value.
    ViewPtr<Value> value() const noexcept
    {
        return m_value;
    }

private:
    // Data Members

    /// The return type.
    ViewPtr<Type> m_type;

    /// The return value.
    ViewPtr<Value> m_value;
};

/* ************************************************************************* */

} // namespace shard::ir

/* ************************************************************************* */

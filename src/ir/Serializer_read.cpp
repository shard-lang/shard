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
#include "shard/ir/Serializer.hpp"

// C++
#include <istream>
#include <limits>

// Shard
#include "shard/Array.hpp"
#include "shard/Byte.hpp"
#include "shard/Map.hpp"
#include "shard/ir/Block.hpp"
#include "shard/ir/Function.hpp"
#include "shard/ir/Instruction.hpp"
#include "shard/ir/Module.hpp"

/* ************************************************************************* */

namespace shard::ir {

/* ************************************************************************* */

namespace {

/* ************************************************************************* */

/**
 * @brief      Read a byte to stream.
 *
 * @param      input  The input stream.
 *
 * @return     The value.
 */
Byte readByte(std::istream& input)
{
    Byte value;

    input.read(reinterpret_cast<char*>(&value), sizeof(value));

    return value;
}

/* ************************************************************************* */

/**
 * @brief      Read a 8 bit integer to stream.
 *
 * @param      input  The input stream.
 *
 * @return     The value.
 */
int8_t readInt8(std::istream& input)
{
    int8_t value;

    input.read(reinterpret_cast<char*>(&value), sizeof(value));

    return value;
}

/* ************************************************************************* */

/**
 * @brief      Read a 8 bit integer to stream.
 *
 * @param      input  The input stream.
 *
 * @return     The value.
 */
uint8_t readUint8(std::istream& input)
{
    uint8_t value;

    input.read(reinterpret_cast<char*>(&value), sizeof(value));

    return value;
}

/* ************************************************************************* */

/**
 * @brief      Read a 16 bit integer to stream.
 *
 * @param      input  The input stream.
 *
 * @return     The value.
 */
int16_t readInt16(std::istream& input)
{
    int16_t value;

    input.read(reinterpret_cast<char*>(&value), sizeof(value));

    return value;
}

/* ************************************************************************* */

/**
 * @brief      Read a 16 bit integer to stream.
 *
 * @param      input  The input stream.
 *
 * @return     The value.
 */
uint16_t readUint16(std::istream& input)
{
    uint16_t value;

    input.read(reinterpret_cast<char*>(&value), sizeof(value));

    return value;
}

/* ************************************************************************* */

/**
 * @brief      Read a 32 bit integer to stream.
 *
 * @param      input  The input stream.
 *
 * @return     The value.
 */
int32_t readInt32(std::istream& input)
{
    int32_t value;

    input.read(reinterpret_cast<char*>(&value), sizeof(value));

    return value;
}

/* ************************************************************************* */

/**
 * @brief      Read a 32 bit integer to stream.
 *
 * @param      input  The input stream.
 *
 * @return     The value.
 */
uint32_t readUint32(std::istream& input)
{
    uint32_t value;

    input.read(reinterpret_cast<char*>(&value), sizeof(value));

    return value;
}

/* ************************************************************************* */

/**
 * @brief      Read a 64 bit integer to stream.
 *
 * @param      input  The input stream.
 *
 * @return     The value.
 */
int64_t readInt64(std::istream& input)
{
    int64_t value;

    input.read(reinterpret_cast<char*>(&value), sizeof(value));

    return value;
}

/* ************************************************************************* */

/**
 * @brief      Read a 64 bit integer to stream.
 *
 * @param      input  The input stream.
 *
 * @return     The value.
 */
uint64_t readUint64(std::istream& input)
{
    uint64_t value;

    input.read(reinterpret_cast<char*>(&value), sizeof(value));

    return value;
}

/* ************************************************************************* */

/**
 * @brief      Read a 64 bit float to stream.
 *
 * @param      input  The input stream.
 *
 * @return     The value.
 */
float readFloat32(std::istream& input)
{
    float value;

    input.read(reinterpret_cast<char*>(&value), sizeof(value));

    return value;
}

/* ************************************************************************* */

/**
 * @brief      Read a 64 bit float to stream.
 *
 * @param      input  The input stream.
 *
 * @return     The value.
 */
double readFloat64(std::istream& input)
{
    double value;

    input.read(reinterpret_cast<char*>(&value), sizeof(value));

    return value;
}

/* ************************************************************************* */

/**
 * @brief      Read a byte to stream.
 *
 * @param      input  The input stream.
 *
 * @return     The value.
 */
String readString(std::istream& input)
{
    const int len = readUint16(input);

    String value(len, '\0');
    input.read(value.data(), value.size());

    return value;
}

/* ************************************************************************* */

/**
 * @brief      Read a list.
 *
 * @param      input    The input stream.
 * @param      fn       The function.
 *
 * @tparam     ELEMENT  Container element type.
 * @tparam     FN       Function type.
 *
 * @return     Read elements.
 */
template<typename ELEMENT, typename FN>
Vector<ELEMENT> readList(std::istream& input, FN fn)
{
    // Read size
    const uint16_t size = readUint16(input);

    Vector<ELEMENT> result;
    result.reserve(size);

    // Read elements
    for (uint16_t i = 0; i < size; ++i)
        result.push_back(fn(input));

    return result;
}

/* ************************************************************************* */

/**
 * @brief      Read a type.
 *
 * @param      input   The input.
 * @param      module  The module.
 *
 * @return     Type.
 */
ViewPtr<Type> readType(std::istream& input, Module& module)
{
    const int code = static_cast<int>(readByte(input));

    switch (code)
    {
    case 0x00: return nullptr;
    case 0x01: return TypeInt1::instance();
    case 0x02: return TypeInt8::instance();
    case 0x03: return TypeInt16::instance();
    case 0x04: return TypeInt32::instance();
    case 0x05: return TypeInt64::instance();
    case 0x06: return TypeFloat32::instance();
    case 0x07: return TypeFloat64::instance();
    case 0xE0:
    {
        auto pointee = readType(input, module);
        return module.createType<TypePointer>(pointee);
    }
    case 0xF0:
    {
        // TODO: support structs
        int index = readInt16(input);
    }
    default: throw std::invalid_argument("Unsupported type");
    }
}

/* ************************************************************************* */

/**
 * @brief      Read a constant.
 *
 * @param      input   The input stream.
 * @param      type    The constant type.
 * @param      module  The module
 *
 * @return     Constant.
 */
ViewPtr<Value>
readConst(std::istream& input, ViewPtr<Type> type, Module& module)
{
    switch (type->kind())
    {
    case ir::TypeKind::Int1:
    {
        auto value = readByte(input) == Byte(0x01);
        return module.createConstant<ir::ConstInt1>(value);
    }

    case ir::TypeKind::Int8:
    {
        auto value = readInt8(input);
        return module.createConstant<ir::ConstInt8>(value);
    }

    case ir::TypeKind::Int16:
    {
        auto value = readInt16(input);
        return module.createConstant<ir::ConstInt16>(value);
    }

    case ir::TypeKind::Int32:
    {
        auto value = readInt32(input);
        return module.createConstant<ir::ConstInt32>(value);
    }

    case ir::TypeKind::Int64:
    {
        auto value = readInt64(input);
        return module.createConstant<ir::ConstInt64>(value);
    }

    case ir::TypeKind::Float32:
    {
        auto value = readFloat32(input);
        return module.createConstant<ir::ConstFloat32>(value);
    }

    case ir::TypeKind::Float64:
    {
        auto value = readFloat64(input);
        return module.createConstant<ir::ConstFloat64>(value);
    }

    default: throw std::runtime_error("Unsupported constant type");
    }
}

/* ************************************************************************* */

struct Mapping
{
    Map<uint16_t, ViewPtr<Value>> values;
    Map<uint16_t, ViewPtr<Block>> blocks;
};

/* ************************************************************************* */

/**
 * @brief      Map value to index.
 *
 * @param      mapping  The mapping in block.
 * @param      value    The value to map.
 *
 * @return     Value index.
 */
ViewPtr<Value> mapValue(Mapping& mapping, uint16_t value)
{
    auto it = mapping.values.find(value);

    if (it != end(mapping.values))
        return it->second;

    throw std::runtime_error("Unable to map value");
}

/* ************************************************************************* */

/**
 * @brief      Map block to index.
 *
 * @param      mapping  The mapping in block.
 * @param      block    The block to map.
 *
 * @return     Block index.
 */
ViewPtr<Block> mapBlock(Mapping& mapping, uint16_t block)
{
    auto it = mapping.blocks.find(block);

    if (it != end(mapping.blocks))
        return it->second;

    throw std::runtime_error("Unable to map block");
}

/* ************************************************************************* */

/**
 * @brief      Read a value from input (via index).
 *
 * @param      input    The input.
 * @param      mapping  The value mapping.
 *
 * @return     The value.
 */
ViewPtr<Value> readValue(std::istream& input, Mapping& mapping)
{
    int16_t value = readInt16(input);
    return mapValue(mapping, value);
}

/* ************************************************************************* */

UniquePtr<InstructionAlloc> readInstructionAlloc(
    std::istream& input,
    int code,
    Module& module,
    Mapping& mapping)
{
    // | `alloc`     | `0x00` + `<type>` + `<result>` | 1+N+2 bytes     | |
    // `alloc`     | `0x01` + `<type>` + `<count>` + `<result>` | 1+N+4+2 bytes
    // |

    UniquePtr<InstructionAlloc> instr;

    auto type = readType(input, module);

    if (code == 0x00)
    {
        instr = makeUnique<InstructionAlloc>(type);
    }
    else if (code == 0x01)
    {
        auto count = readUint32(input);

        instr = makeUnique<InstructionAlloc>(type, count);
    }
    else
    {
        throw std::runtime_error("Unknown instruction code");
    }

    int16_t result = readInt16(input);

    // Register value
    mapping.values.emplace(result, instr->result());

    return instr;
}

/* ************************************************************************* */

UniquePtr<InstructionStore> readInstructionStore(
    std::istream& input,
    int code,
    Module& module,
    Mapping& mapping)
{
    // | `store`     | `0x10` + `<type>` + `<address>` + `<value>` | 1+N+2+2
    // bytes   | | `store`     | `0x11` + `<type>` + `<address>` + `<constant>`
    // | 1+N+2+M bytes   | | `store`     | `0x12` + `<type>` + `<address>` +
    // `<value>` + `<index>`    | 1+N+2+2+4 bytes | | `store`     | `0x13` +
    // `<type>` + `<address>` + `<constant>` + `<index>` | 1+N+2+M+4 bytes |

    UniquePtr<InstructionStore> instr;

    auto type    = readType(input, module);
    auto pointer = readValue(input, mapping);

    if (code == 0x10)
    {
        auto value = readValue(input, mapping);

        instr = makeUnique<InstructionStore>(pointer, value);
    }
    else if (code == 0x11)
    {
        auto value = readConst(input, type, module);

        instr = makeUnique<InstructionStore>(pointer, value);
    }
    else if (code == 0x12)
    {
        auto value = readValue(input, mapping);
        auto index = readUint32(input);

        instr = makeUnique<InstructionStore>(pointer, value, index);
    }
    else if (code == 0x13)
    {
        auto value = readConst(input, type, module);
        auto index = readUint32(input);

        instr = makeUnique<InstructionStore>(pointer, value, index);
    }
    else
    {
        throw std::runtime_error("Unknown instruction code");
    }

    return instr;
}

/* ************************************************************************* */

UniquePtr<InstructionLoad> readInstructionLoad(
    std::istream& input,
    int code,
    Module& module,
    Mapping& mapping)
{
    // | `load`      | `0x20` + `<type>` + `<address>` + `<result>` | 1+N+2+2
    // bytes   | | `load`      | `0x21` + `<type>` + `<address>` + `<result>` +
    // `<index>`   | 1+N+2+2+4 bytes |

    UniquePtr<InstructionLoad> instr;

    auto type    = readType(input, module);
    auto pointer = readValue(input, mapping);
    auto result  = readUint16(input);

    if (code == 0x20)
    {
        instr = makeUnique<InstructionLoad>(pointer);
    }
    else if (code == 0x21)
    {
        auto index = readUint32(input);

        instr = makeUnique<InstructionLoad>(pointer, index);
    }
    else
    {
        throw std::runtime_error("Unknown instruction code");
    }

    // Register value
    mapping.values.emplace(result, instr->result());

    return instr;
}

/* ************************************************************************* */

UniquePtr<InstructionAdd> readInstructionAdd(
    std::istream& input,
    int code,
    Module& module,
    Mapping& mapping)
{
    // | `add`       | `0x30` + `<type>` + `<value1>` + `<value2>` | 1+N+2+2
    // bytes   | | `add`       | `0x31` + `<type>` + `<value1>` + `<constant>`
    // | 1+N+2+M bytes   |

    UniquePtr<InstructionAdd> instr;

    auto type   = readType(input, module);
    auto value1 = readValue(input, mapping);

    if (code == 0x30)
    {
        auto value2 = readValue(input, mapping);

        instr = makeUnique<InstructionAdd>(type, value1, value2);
    }
    else if (code == 0x31)
    {
        auto value2 = readConst(input, type, module);

        instr = makeUnique<InstructionAdd>(type, value1, value2);
    }
    else
    {
        throw std::runtime_error("Unknown instruction code");
    }

    return instr;
}

/* ************************************************************************* */

UniquePtr<InstructionSub> readInstructionSub(
    std::istream& input,
    int code,
    Module& module,
    Mapping& mapping)
{
    // | `sub`       | `0x40` + `<type>` + `<value1>` + `<value2>` | 1+N+2+2
    // bytes   | | `sub`       | `0x41` + `<type>` + `<value1>` + `<constant>`
    // | 1+N+2+M bytes   | | `sub`       | `0x42` + `<type>` + `<constant>` +
    // `<value2>`              | 1+N+M+2 bytes   |

    UniquePtr<InstructionSub> instr;

    auto type = readType(input, module);

    if (code == 0x40)
    {
        auto value1 = readValue(input, mapping);
        auto value2 = readValue(input, mapping);

        instr = makeUnique<InstructionSub>(type, value1, value2);
    }
    else if (code == 0x41)
    {
        auto value1 = readValue(input, mapping);
        auto value2 = readConst(input, type, module);

        instr = makeUnique<InstructionSub>(type, value1, value2);
    }
    else if (code == 0x42)
    {
        auto value1 = readConst(input, type, module);
        auto value2 = readValue(input, mapping);

        instr = makeUnique<InstructionSub>(type, value1, value2);
    }
    else
    {
        throw std::runtime_error("Unknown instruction code");
    }

    return instr;
}

/* ************************************************************************* */

UniquePtr<InstructionMul> readInstructionMul(
    std::istream& input,
    int code,
    Module& module,
    Mapping& mapping)
{
    // | `mul`       | `0x50` + `<type>` + `<value1>` + `<value2>` | 1+N+2+2
    // bytes   | | `mul`       | `0x51` + `<type>` + `<value1>` + `<constant>`
    // | 1+N+2+M bytes   |

    UniquePtr<InstructionMul> instr;

    auto type   = readType(input, module);
    auto value1 = readValue(input, mapping);

    if (code == 0x50)
    {
        auto value2 = readValue(input, mapping);

        instr = makeUnique<InstructionMul>(type, value1, value2);
    }
    else if (code == 0x51)
    {
        auto value2 = readConst(input, type, module);

        instr = makeUnique<InstructionMul>(type, value1, value2);
    }
    else
    {
        throw std::runtime_error("Unknown instruction code");
    }

    return instr;
}

/* ************************************************************************* */

UniquePtr<InstructionDiv> readInstructionDiv(
    std::istream& input,
    int code,
    Module& module,
    Mapping& mapping)
{
    // | `div`       | `0x60` + `<type>` + `<value1>` + `<value2>` | 1+N+2+2
    // bytes   | | `div`       | `0x61` + `<type>` + `<value1>` + `<constant>`
    // | 1+N+2+M bytes   | | `div`       | `0x62` + `<type>` + `<constant>` +
    // `<value2>`              | 1+N+M+2 bytes   |

    UniquePtr<InstructionDiv> instr;

    auto type = readType(input, module);

    if (code == 0x60)
    {
        auto value1 = readValue(input, mapping);
        auto value2 = readValue(input, mapping);

        instr = makeUnique<InstructionDiv>(type, value1, value2);
    }
    else if (code == 0x61)
    {
        auto value1 = readValue(input, mapping);
        auto value2 = readConst(input, type, module);

        instr = makeUnique<InstructionDiv>(type, value1, value2);
    }
    else if (code == 0x62)
    {
        auto value1 = readConst(input, type, module);
        auto value2 = readValue(input, mapping);

        instr = makeUnique<InstructionDiv>(type, value1, value2);
    }
    else
    {
        throw std::runtime_error("Unknown instruction code");
    }

    return instr;
}

/* ************************************************************************* */

UniquePtr<InstructionRem> readInstructionRem(
    std::istream& input,
    int code,
    Module& module,
    Mapping& mapping)
{
    // | `rem`       | `0x70` + `<type>` + `<value1>` + `<value2>` | 1+N+2+2
    // bytes   | | `rem`       | `0x71` + `<type>` + `<value1>` + `<constant>`
    // | 1+N+2+M bytes   | | `rem`       | `0x72` + `<type>` + `<constant>` +
    // `<value2>`              | 1+N+M+2 bytes   |

    UniquePtr<InstructionRem> instr;

    auto type = readType(input, module);

    if (code == 0x70)
    {
        auto value1 = readValue(input, mapping);
        auto value2 = readValue(input, mapping);

        instr = makeUnique<InstructionRem>(type, value1, value2);
    }
    else if (code == 0x71)
    {
        auto value1 = readValue(input, mapping);
        auto value2 = readConst(input, type, module);

        instr = makeUnique<InstructionRem>(type, value1, value2);
    }
    else if (code == 0x72)
    {
        auto value1 = readConst(input, type, module);
        auto value2 = readValue(input, mapping);

        instr = makeUnique<InstructionRem>(type, value1, value2);
    }
    else
    {
        throw std::runtime_error("Unknown instruction code");
    }

    return instr;
}

/* ************************************************************************* */

UniquePtr<InstructionCmp> readInstructionCmp(
    std::istream& input,
    int code,
    Module& module,
    Mapping& mapping)
{
    // | `cmp`       | `0x80` + `<op>` + `<type>` + `<value1>` + `<value2>` |
    // 1+1+N+2+2 bytes | | `cmp`       | `0x81` + `<op>` + `<type>` + `<value1>`
    // + `<constant>`     | 1+1+N+2+M bytes |

    UniquePtr<InstructionCmp> instr;

    auto op     = static_cast<InstructionCmp::Operation>(readByte(input));
    auto type   = readType(input, module);
    auto value1 = readValue(input, mapping);

    if (code == 0x80)
    {
        auto value2 = readValue(input, mapping);

        instr = makeUnique<InstructionCmp>(op, type, value1, value2);
    }
    else if (code == 0x81)
    {
        auto value2 = readConst(input, type, module);

        instr = makeUnique<InstructionCmp>(op, type, value1, value2);
    }
    else
    {
        throw std::runtime_error("Unknown instruction code");
    }

    return instr;
}

/* ************************************************************************* */

UniquePtr<InstructionAnd> readInstructionAnd(
    std::istream& input,
    int code,
    Module& module,
    Mapping& mapping)
{
    // | `and`       | `0x90` + `<type>` + `<value1>` + `<value2>` | 1+N+2+2
    // bytes   | | `and`       | `0x91` + `<type>` + `<value1>` + `<constant>`
    // | 1+N+2+M bytes   | | `and`       | `0x92` + `<type>` + `<constant>` +
    // `<value2>`              | 1+N+M+2 bytes   |

    UniquePtr<InstructionAnd> instr;

    auto type = readType(input, module);

    if (code == 0x90)
    {
        auto value1 = readValue(input, mapping);
        auto value2 = readValue(input, mapping);

        instr = makeUnique<InstructionAnd>(type, value1, value2);
    }
    else if (code == 0x91)
    {
        auto value1 = readValue(input, mapping);
        auto value2 = readConst(input, type, module);

        instr = makeUnique<InstructionAnd>(type, value1, value2);
    }
    else if (code == 0x92)
    {
        auto value1 = readConst(input, type, module);
        auto value2 = readValue(input, mapping);

        instr = makeUnique<InstructionAnd>(type, value1, value2);
    }
    else
    {
        throw std::runtime_error("Unknown instruction code");
    }

    return instr;
}

/* ************************************************************************* */

UniquePtr<InstructionOr> readInstructionOr(
    std::istream& input,
    int code,
    Module& module,
    Mapping& mapping)
{
    // | `or`        | `0xA0` + `<type>` + `<value1>` + `<value2>` | 1+N+2+2
    // bytes   | | `or`        | `0xA1` + `<type>` + `<value1>` + `<constant>`
    // | 1+N+2+M bytes   | | `or`        | `0xA2` + `<type>` + `<constant>` +
    // `<value2>`              | 1+N+M+2 bytes   |

    UniquePtr<InstructionOr> instr;

    auto type = readType(input, module);

    if (code == 0xA0)
    {
        auto value1 = readValue(input, mapping);
        auto value2 = readValue(input, mapping);

        instr = makeUnique<InstructionOr>(type, value1, value2);
    }
    else if (code == 0xA1)
    {
        auto value1 = readValue(input, mapping);
        auto value2 = readConst(input, type, module);

        instr = makeUnique<InstructionOr>(type, value1, value2);
    }
    else if (code == 0xA2)
    {
        auto value1 = readConst(input, type, module);
        auto value2 = readValue(input, mapping);

        instr = makeUnique<InstructionOr>(type, value1, value2);
    }
    else
    {
        throw std::runtime_error("Unknown instruction code");
    }

    return instr;
}

/* ************************************************************************* */

UniquePtr<InstructionXor> readInstructionXor(
    std::istream& input,
    int code,
    Module& module,
    Mapping& mapping)
{
    // | `xor`       | `0xB0` + `<type>` + `<value1>` + `<value2>` | 1+N+2+2
    // bytes   | | `xor`       | `0xB1` + `<type>` + `<value1>` + `<constant>`
    // | 1+N+2+M bytes   | | `xor`       | `0xB2` + `<type>` + `<constant>` +
    // `<value2>`              | 1+N+M+2 bytes   |

    UniquePtr<InstructionXor> instr;

    auto type = readType(input, module);

    if (code == 0xB0)
    {
        auto value1 = readValue(input, mapping);
        auto value2 = readValue(input, mapping);

        instr = makeUnique<InstructionXor>(type, value1, value2);
    }
    else if (code == 0xB1)
    {
        auto value1 = readValue(input, mapping);
        auto value2 = readConst(input, type, module);

        instr = makeUnique<InstructionXor>(type, value1, value2);
    }
    else if (code == 0xB2)
    {
        auto value1 = readConst(input, type, module);
        auto value2 = readValue(input, mapping);

        instr = makeUnique<InstructionXor>(type, value1, value2);
    }
    else
    {
        throw std::runtime_error("Unknown instruction code");
    }

    return instr;
}

/* ************************************************************************* */

UniquePtr<InstructionBranch> readInstructionBranch(
    std::istream& input,
    int code,
    Module& module,
    Mapping& mapping)
{
    // | `branch`    | `0xC0` + `<label>` | 1+2 bytes       |

    auto lab = readUint16(input);

    // TODO: create block??
    mapping.blocks.emplace();

    return makeUnique<InstructionBranch>(nullptr);
}

/* ************************************************************************* */

UniquePtr<InstructionBranchCondition> readInstructionBranchCondition(
    std::istream& input,
    int code,
    Module& module,
    Mapping& mapping)
{
    // | `branch`    | `0xC1` + `<value>` + `<label1>` + `<label2>` | 1+2+2+2
    // bytes   |

    auto value = readValue(input, mapping);
    auto lab1  = readUint16(input);
    auto lab2  = readUint16(input);

    // TODO: create blocks??
    mapping.blocks.emplace();

    return makeUnique<InstructionBranchCondition>(value, nullptr, nullptr);
}

/* ************************************************************************* */

UniquePtr<InstructionCall> readInstructionCall(
    std::istream& input,
    int code,
    Module& module,
    Mapping& mapping)
{
    // | `call`      | `0xD0` + `<types...>` + `<name>` | 1+N+M bytes     | |
    // `call`      | `0xD1` + `<type>` + `<types...>` + `<name>` | 1+N+M+K bytes
    // |

    UniquePtr<InstructionCall> instr;

    if (code == 0xD0)
    {
        auto types = readList<ViewPtr<Type>>(
            input, [&](auto& input) { return readType(input, module); });

        auto name = readString(input);

        auto args = readList<ViewPtr<Value>>(
            input, [&](auto& input) { return readValue(input, mapping); });

        instr = makeUnique<InstructionCall>(name, args);
    }
    else if (code == 0xD1)
    {
        auto type  = readType(input, module);
        auto types = readList<ViewPtr<Type>>(
            input, [&](auto& input) { return readType(input, module); });

        auto name = readString(input);

        auto args = readList<ViewPtr<Value>>(
            input, [&](auto& input) { return readValue(input, mapping); });

        instr = makeUnique<InstructionCall>(name, type, args);
    }
    else
    {
        throw std::runtime_error("Unknown instruction code");
    }

    return instr;
}

/* ************************************************************************* */

UniquePtr<InstructionReturn> readInstructionReturn(
    std::istream& input,
    int code,
    Module& module,
    Mapping& mapping)
{
    // | `return`    | `0xE1` + `<type>` + `<value>` | 1+N+2 bytes     |

    auto type  = readType(input, module);
    auto value = readValue(input, mapping);

    return makeUnique<InstructionReturn>(type, value);
}

/* ************************************************************************* */

UniquePtr<InstructionReturnVoid> readInstructionReturnVoid(
    std::istream& input,
    int code,
    Module& module,
    Mapping& mapping)
{
    // | `return`    | `0xE0` | 1 bytes         |

    return makeUnique<InstructionReturnVoid>();
}

/* ************************************************************************* */

UniquePtr<Instruction>
readInstruction(std::istream& input, Module& module, Mapping& mapping)
{
    const int code = static_cast<int>(readByte(input));

    switch (code)
    {
    case 0x00:
    case 0x01: return readInstructionAlloc(input, code, module, mapping);
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13: return readInstructionStore(input, code, module, mapping);
    case 0x20:
    case 0x21: return readInstructionLoad(input, code, module, mapping);
    case 0x30:
    case 0x31: return readInstructionAdd(input, code, module, mapping);
    case 0x40:
    case 0x41:
    case 0x42: return readInstructionSub(input, code, module, mapping);
    case 0x50:
    case 0x51: return readInstructionMul(input, code, module, mapping);
    case 0x60:
    case 0x61:
    case 0x62: return readInstructionDiv(input, code, module, mapping);
    case 0x70:
    case 0x71:
    case 0x72: return readInstructionRem(input, code, module, mapping);
    case 0x80:
    case 0x81: return readInstructionCmp(input, code, module, mapping);
    case 0x90:
    case 0x91:
    case 0x92: return readInstructionAnd(input, code, module, mapping);
    case 0xA0:
    case 0xA1:
    case 0xA2: return readInstructionOr(input, code, module, mapping);
    case 0xB0:
    case 0xB1:
    case 0xB2: return readInstructionXor(input, code, module, mapping);
    case 0xC0: return readInstructionBranch(input, code, module, mapping);
    case 0xC1:
        return readInstructionBranchCondition(input, code, module, mapping);
    case 0xD0:
    case 0xD1: return readInstructionCall(input, code, module, mapping);
    case 0xE1: return readInstructionReturn(input, code, module, mapping);
    case 0xE0: return readInstructionReturnVoid(input, code, module, mapping);
    }
}

/* ************************************************************************* */

UniquePtr<Block>
readBlock(std::istream& input, Module& module, Mapping& mapping)
{
    auto block = makeUnique<Block>();

    auto instructions =
        readList<UniquePtr<Instruction>>(input, [&](auto& input) {
            return readInstruction(input, module, mapping);
        });

    block->setInstructions(std::move(instructions));

    return block;
}

/* ************************************************************************* */

UniquePtr<Function> readFunction(std::istream& input, Module& module)
{
    // Read function name
    auto name = readString(input);

    // Return type
    auto retType = readType(input, module);

    // Parameter types
    auto types = readList<ViewPtr<Type>>(
        input, [&](auto& input) { return readType(input, module); });

    // Blocks
    Mapping mapping;
    auto blocks = readList<UniquePtr<Block>>(
        input, [&](auto& input) { return readBlock(input, module, mapping); });

    auto fn = makeUnique<Function>(std::move(name), retType, std::move(types));

    fn->setBlocks(std::move(blocks));

    return fn;
}

/* ************************************************************************* */

} // namespace

/* ************************************************************************* */

Module deserialize(std::istream& input)
{
    Module module;

    Array<Byte, 4> guard;

    // Read guard
    for (auto& byte : guard)
        byte = readByte(input);

    // Check guard
    if (guard[0] != Byte('S') || guard[1] != Byte('H') ||
        guard[2] != Byte('R') || guard[3] != Byte('D'))
        throw std::runtime_error("invalid input file");

    Byte versionMajor = readByte(input);
    Byte versionMinor = readByte(input);

    if (versionMajor != Byte(0x00) || versionMinor != Byte(0x01))
        throw std::runtime_error("unsupported version");

    // TODO: read structures

    // Read functions
    auto functions = readList<UniquePtr<Function>>(
        input, [&](auto& input) { return readFunction(input, module); });

    module.setFunctions(std::move(functions));

    return module;
}

/* ************************************************************************* */

} // namespace shard::ir

/* ************************************************************************* */

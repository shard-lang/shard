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
#include <limits>
#include <ostream>

// Shard
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
 * @brief      Write a byte to stream.
 *
 * @param      os     The output stream.
 * @param      value  The value.
 */
void writeByte(std::ostream& os, Byte value)
{
    os.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

/* ************************************************************************* */

/**
 * @brief      Write a 8 bit integer to stream.
 *
 * @param      os     The output stream.
 * @param      value  The value.
 */
void writeInt8(std::ostream& os, int8_t value)
{
    os.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

/* ************************************************************************* */

/**
 * @brief      Write a 8 bit integer to stream.
 *
 * @param      os     The output stream.
 * @param      value  The value.
 */
void writeUint8(std::ostream& os, uint8_t value)
{
    os.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

/* ************************************************************************* */

/**
 * @brief      Write a 16 bit integer to stream.
 *
 * @param      os     The output stream.
 * @param      value  The value.
 */
void writeInt16(std::ostream& os, int16_t value)
{
    os.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

/* ************************************************************************* */

/**
 * @brief      Write a 16 bit integer to stream.
 *
 * @param      os     The output stream.
 * @param      value  The value.
 */
void writeUint16(std::ostream& os, uint16_t value)
{
    os.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

/* ************************************************************************* */

/**
 * @brief      Write a 32 bit integer to stream.
 *
 * @param      os     The output stream.
 * @param      value  The value.
 */
void writeInt32(std::ostream& os, int32_t value)
{
    os.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

/* ************************************************************************* */

/**
 * @brief      Write a 32 bit integer to stream.
 *
 * @param      os     The output stream.
 * @param      value  The value.
 */
void writeUint32(std::ostream& os, uint32_t value)
{
    os.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

/* ************************************************************************* */

/**
 * @brief      Write a 64 bit integer to stream.
 *
 * @param      os     The output stream.
 * @param      value  The value.
 */
void writeInt64(std::ostream& os, int64_t value)
{
    os.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

/* ************************************************************************* */

/**
 * @brief      Write a 64 bit integer to stream.
 *
 * @param      os     The output stream.
 * @param      value  The value.
 */
void writeUint64(std::ostream& os, uint64_t value)
{
    os.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

/* ************************************************************************* */

/**
 * @brief      Write a 64 bit float to stream.
 *
 * @param      os     The output stream.
 * @param      value  The value.
 */
void writeFloat32(std::ostream& os, float value)
{
    os.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

/* ************************************************************************* */

/**
 * @brief      Write a 64 bit float to stream.
 *
 * @param      os     The output stream.
 * @param      value  The value.
 */
void writeFloat64(std::ostream& os, double value)
{
    os.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

/* ************************************************************************* */

/**
 * @brief      Write a byte to stream.
 *
 * @param      os     The output stream.
 * @param      value  The value.
 */
void writeString(std::ostream& os, const std::string& value)
{
    SHARD_ASSERT(value.size() <= std::numeric_limits<uint16_t>::max());

    writeUint16(os, value.size());
    os.write(value.c_str(), value.size());
}

/* ************************************************************************* */

/**
 * @brief      Write a list.
 *
 * @param      output     The output stream.
 * @param      container  The container
 * @param      fn         The function
 *
 * @tparam     Container  Container type.
 * @tparam     Fn         Function type.
 */
template<typename Container, typename Fn>
void writeList(std::ostream& output, const Container& container, Fn fn)
{
    SHARD_ASSERT(container.size() <= std::numeric_limits<uint16_t>::max());

    // Write size
    writeUint16(output, container.size());

    // Write items
    for (const auto& item : container)
        fn(output, item);
}

/* ************************************************************************* */

void writeType(std::ostream& output, const Type& type)
{
    // TODO: reorder by probability
    if (type.is<TypeInt1>())
    {
        writeByte(output, Byte{0x01});
    }
    else if (type.is<TypeInt8>())
    {
        writeByte(output, Byte{0x02});
    }
    else if (type.is<TypeInt16>())
    {
        writeByte(output, Byte{0x03});
    }
    else if (type.is<TypeInt32>())
    {
        writeByte(output, Byte{0x04});
    }
    else if (type.is<TypeInt64>())
    {
        writeByte(output, Byte{0x05});
    }
    else if (type.is<TypeFloat32>())
    {
        writeByte(output, Byte{0x06});
    }
    else if (type.is<TypeFloat64>())
    {
        writeByte(output, Byte{0x07});
    }
    else if (type.is<TypePointer>())
    {
        auto pointee = type.as<TypePointer>().type();

        writeByte(output, Byte{0xE0});
        writeType(output, *pointee);
    }
    else if (type.is<TypeStruct>())
    {
        writeByte(output, Byte{0xF0});
        // TODO: support structs
        writeInt16(output, 0);
    }
    else
    {
        throw std::invalid_argument("Unsupported type");
    }
}

/* ************************************************************************* */

/**
 * @brief      Write a constant.
 *
 * @param      out    The output stream.
 * @param      value  The constant.
 */
void writeConst(std::ostream& out, ViewPtr<Value> value)
{
    switch (value->type()->kind())
    {
    case ir::TypeKind::Int1:
    {
        auto& val = static_cast<ir::ConstInt1&>(*value);
        writeByte(out, Byte(val.value() ? 1 : 0));
        break;
    }

    case ir::TypeKind::Int8:
    {
        auto& val = static_cast<ir::ConstInt8&>(*value);
        writeInt8(out, val.value());
        break;
    }

    case ir::TypeKind::Int16:
    {
        auto& val = static_cast<ir::ConstInt16&>(*value);
        writeInt16(out, val.value());
        break;
    }

    case ir::TypeKind::Int32:
    {
        auto& val = static_cast<ir::ConstInt32&>(*value);
        writeInt32(out, val.value());
        break;
    }

    case ir::TypeKind::Int64:
    {
        auto& val = static_cast<ir::ConstInt64&>(*value);
        writeInt64(out, val.value());
        break;
    }

    case ir::TypeKind::Float32:
    {
        auto& val = static_cast<ir::ConstFloat32&>(*value);
        writeFloat32(out, val.value());
        break;
    }

    case ir::TypeKind::Float64:
    {
        auto& val = static_cast<ir::ConstFloat64&>(*value);
        writeFloat64(out, val.value());
        break;
    }

    default: throw std::runtime_error("Unsupported constant type");
    }
}

/* ************************************************************************* */

struct Mapping
{
    Map<ViewPtr<Value>, uint16_t> values;
    Map<ViewPtr<Block>, uint16_t> blocks;
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
uint16_t mapValue(Mapping& mapping, ViewPtr<Value> value)
{
    SHARD_ASSERT(value != nullptr);

    auto it = mapping.values.find(value);

    if (it != end(mapping.values))
        return it->second;

    auto [iti, ins] = mapping.values.emplace(value, mapping.values.size() + 1);

    return iti->second;
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
uint16_t mapBlock(Mapping& mapping, ViewPtr<Block> block)
{
    SHARD_ASSERT(block != nullptr);

    auto it = mapping.blocks.find(block);

    if (it != end(mapping.blocks))
        return it->second;

    auto [iti, ins] = mapping.blocks.emplace(block, mapping.blocks.size() + 1);

    return iti->second;
}

/* ************************************************************************* */

void writeValue(std::ostream& out, Mapping& mapping, ViewPtr<Value> value)
{
    writeUint16(out, mapValue(mapping, value));
}

/* ************************************************************************* */

void writeBlock(std::ostream& out, Mapping& mapping, ViewPtr<Block> block)
{
    writeUint16(out, mapBlock(mapping, block));
}

/* ************************************************************************* */

void writeInstruction(
    std::ostream& out,
    Mapping& mapping,
    const InstructionAlloc& instr)
{
    // | `alloc`     | `0x00` + `<type>` + `<result>` | 1+N+2 bytes     | |
    // `alloc`     | `0x01` + `<type>` + `<count>` + `<result>` | 1+N+4+2 bytes
    // |

    if (instr.count() == 1)
    {
        writeByte(out, Byte{0x00});
        writeType(out, *instr.type());
        writeValue(out, mapping, instr.result());
    }
    else
    {
        writeByte(out, Byte{0x01});
        writeType(out, *instr.type());
        writeUint32(out, instr.count());
        writeValue(out, mapping, instr.result());
    }
}

/* ************************************************************************* */

void writeInstruction(
    std::ostream& out,
    Mapping& mapping,
    const InstructionStore& instr)
{
    // | `store`     | `0x10` + `<type>` + `<address>` + `<value>` | 1+N+2+2
    // bytes   | | `store`     | `0x11` + `<type>` + `<address>` + `<constant>`
    // | 1+N+2+M bytes   | | `store`     | `0x12` + `<type>` + `<address>` +
    // `<value>` + `<index>`    | 1+N+2+2+4 bytes | | `store`     | `0x13` +
    // `<type>` + `<address>` + `<constant>` + `<index>` | 1+N+2+M+4 bytes |

    if (instr.index() == 0)
    {
        if (!instr.value()->isConst())
        {
            writeByte(out, Byte{0x10});
            writeType(out, *instr.value()->type());
            writeValue(out, mapping, instr.pointer());
            writeValue(out, mapping, instr.value());
        }
        else
        {
            writeByte(out, Byte{0x11});
            writeType(out, *instr.value()->type());
            writeValue(out, mapping, instr.pointer());
            writeConst(out, instr.value());
        }
    }
    else
    {
        if (!instr.value()->isConst())
        {
            writeByte(out, Byte{0x12});
            writeType(out, *instr.value()->type());
            writeValue(out, mapping, instr.pointer());
            writeValue(out, mapping, instr.value());
            writeUint32(out, instr.index());
        }
        else
        {
            writeByte(out, Byte{0x13});
            writeType(out, *instr.value()->type());
            writeValue(out, mapping, instr.pointer());
            writeConst(out, instr.value());
            writeUint32(out, instr.index());
        }
    }
}

/* ************************************************************************* */

void writeInstruction(
    std::ostream& out,
    Mapping& mapping,
    const InstructionLoad& instr)
{
    // | `load`      | `0x20` + `<type>` + `<address>` + `<result>` | 1+N+2+2
    // bytes   | | `load`      | `0x21` + `<type>` + `<address>` + `<result>` +
    // `<index>`   | 1+N+2+2+4 bytes |

    if (instr.index() == 0)
    {
        writeByte(out, Byte{0x20});
        writeType(out, *instr.resultType());
        writeValue(out, mapping, instr.pointer());
        writeValue(out, mapping, instr.result());
    }
    else
    {
        writeByte(out, Byte{0x21});
        writeType(out, *instr.resultType());
        writeValue(out, mapping, instr.pointer());
        writeValue(out, mapping, instr.result());
        writeUint32(out, instr.index());
    }
}

/* ************************************************************************* */

void writeInstruction(
    std::ostream& out,
    Mapping& mapping,
    const InstructionAdd& instr)
{
    // | `add`       | `0x30` + `<type>` + `<value1>` + `<value2>` | 1+N+2+2
    // bytes   | | `add`       | `0x31` + `<type>` + `<value1>` + `<constant>`
    // | 1+N+2+M bytes   |

    if (!instr.value2()->isConst())
    {
        writeByte(out, Byte{0x30});
        writeType(out, *instr.resultType());
        writeValue(out, mapping, instr.value1());
        writeValue(out, mapping, instr.value2());
    }
    else
    {
        writeByte(out, Byte{0x31});
        writeType(out, *instr.resultType());
        writeValue(out, mapping, instr.value1());
        writeConst(out, instr.value2());
    }

    writeValue(out, mapping, instr.result());
}

/* ************************************************************************* */

void writeInstruction(
    std::ostream& out,
    Mapping& mapping,
    const InstructionSub& instr)
{
    // | `sub`       | `0x40` + `<type>` + `<value1>` + `<value2>` | 1+N+2+2
    // bytes   | | `sub`       | `0x41` + `<type>` + `<value1>` + `<constant>`
    // | 1+N+2+M bytes   | | `sub`       | `0x42` + `<type>` + `<constant>` +
    // `<value2>`              | 1+N+M+2 bytes   |

    if (!instr.value2()->isConst())
    {
        if (!instr.value1()->isConst())
        {
            writeByte(out, Byte{0x40});
            writeType(out, *instr.resultType());
            writeValue(out, mapping, instr.value1());
            writeValue(out, mapping, instr.value2());
        }
        else
        {
            writeByte(out, Byte{0x42});
            writeType(out, *instr.resultType());
            writeConst(out, instr.value1());
            writeValue(out, mapping, instr.value2());
        }
    }
    else
    {
        writeByte(out, Byte{0x41});
        writeType(out, *instr.resultType());
        writeValue(out, mapping, instr.value1());
        writeConst(out, instr.value2());
    }

    writeValue(out, mapping, instr.result());
}

/* ************************************************************************* */

void writeInstruction(
    std::ostream& out,
    Mapping& mapping,
    const InstructionMul& instr)
{
    // | `mul`       | `0x50` + `<type>` + `<value1>` + `<value2>` | 1+N+2+2
    // bytes   | | `mul`       | `0x51` + `<type>` + `<value1>` + `<constant>`
    // | 1+N+2+M bytes   |

    if (!instr.value2()->isConst())
    {
        writeByte(out, Byte{0x50});
        writeType(out, *instr.resultType());
        writeValue(out, mapping, instr.value1());
        writeValue(out, mapping, instr.value2());
    }
    else
    {
        writeByte(out, Byte{0x51});
        writeType(out, *instr.resultType());
        writeValue(out, mapping, instr.value1());
        writeConst(out, instr.value2());
    }

    writeValue(out, mapping, instr.result());
}

/* ************************************************************************* */

void writeInstruction(
    std::ostream& out,
    Mapping& mapping,
    const InstructionDiv& instr)
{
    // | `div`       | `0x60` + `<type>` + `<value1>` + `<value2>` | 1+N+2+2
    // bytes   | | `div`       | `0x61` + `<type>` + `<value1>` + `<constant>`
    // | 1+N+2+M bytes   | | `div`       | `0x62` + `<type>` + `<constant>` +
    // `<value2>`              | 1+N+M+2 bytes   |

    if (!instr.value2()->isConst())
    {
        if (!instr.value1()->isConst())
        {
            writeByte(out, Byte{0x60});
            writeType(out, *instr.resultType());
            writeValue(out, mapping, instr.value1());
            writeValue(out, mapping, instr.value2());
        }
        else
        {
            writeByte(out, Byte{0x62});
            writeType(out, *instr.resultType());
            writeConst(out, instr.value1());
            writeValue(out, mapping, instr.value2());
        }
    }
    else
    {
        writeByte(out, Byte{0x61});
        writeType(out, *instr.resultType());
        writeValue(out, mapping, instr.value1());
        writeConst(out, instr.value2());
    }

    writeValue(out, mapping, instr.result());
}

/* ************************************************************************* */

void writeInstruction(
    std::ostream& out,
    Mapping& mapping,
    const InstructionRem& instr)
{
    // | `rem`       | `0x70` + `<type>` + `<value1>` + `<value2>` | 1+N+2+2
    // bytes   | | `rem`       | `0x71` + `<type>` + `<value1>` + `<constant>`
    // | 1+N+2+M bytes   | | `rem`       | `0x72` + `<type>` + `<constant>` +
    // `<value2>`              | 1+N+M+2 bytes   |

    if (!instr.value2()->isConst())
    {
        if (!instr.value1()->isConst())
        {
            writeByte(out, Byte{0x70});
            writeType(out, *instr.resultType());
            writeValue(out, mapping, instr.value1());
            writeValue(out, mapping, instr.value2());
        }
        else
        {
            writeByte(out, Byte{0x72});
            writeType(out, *instr.resultType());
            writeConst(out, instr.value1());
            writeValue(out, mapping, instr.value2());
        }
    }
    else
    {
        writeByte(out, Byte{0x71});
        writeType(out, *instr.resultType());
        writeValue(out, mapping, instr.value1());
        writeConst(out, instr.value2());
    }

    writeValue(out, mapping, instr.result());
}

/* ************************************************************************* */

void writeInstruction(
    std::ostream& out,
    Mapping& mapping,
    const InstructionCmp& instr)
{
    // | `cmp`       | `0x80` + `<op>` + `<type>` + `<value1>` + `<value2>` |
    // 1+1+N+2+2 bytes | | `cmp`       | `0x81` + `<op>` + `<type>` + `<value1>`
    // + `<constant>`     | 1+1+N+2+M bytes |

    if (!instr.value2()->isConst())
    {
        writeByte(out, Byte{0x80});
        writeByte(out, static_cast<Byte>(instr.operation()));
        writeType(out, *instr.resultType());
        writeValue(out, mapping, instr.value1());
        writeValue(out, mapping, instr.value2());
    }
    else
    {
        writeByte(out, Byte{0x81});
        writeByte(out, static_cast<Byte>(instr.operation()));
        writeType(out, *instr.resultType());
        writeValue(out, mapping, instr.value1());
        writeConst(out, instr.value2());
    }

    writeValue(out, mapping, instr.result());
}

/* ************************************************************************* */

void writeInstruction(
    std::ostream& out,
    Mapping& mapping,
    const InstructionAnd& instr)
{
    // | `and`       | `0x90` + `<type>` + `<value1>` + `<value2>` | 1+N+2+2
    // bytes   | | `and`       | `0x91` + `<type>` + `<value1>` + `<constant>`
    // | 1+N+2+M bytes   | | `and`       | `0x92` + `<type>` + `<constant>` +
    // `<value2>`              | 1+N+M+2 bytes   |

    if (!instr.value2()->isConst())
    {
        if (!instr.value1()->isConst())
        {
            writeByte(out, Byte{0x90});
            writeType(out, *instr.resultType());
            writeValue(out, mapping, instr.value1());
            writeValue(out, mapping, instr.value2());
        }
        else
        {
            writeByte(out, Byte{0x92});
            writeType(out, *instr.resultType());
            writeConst(out, instr.value1());
            writeValue(out, mapping, instr.value2());
        }
    }
    else
    {
        writeByte(out, Byte{0x91});
        writeType(out, *instr.resultType());
        writeValue(out, mapping, instr.value1());
        writeConst(out, instr.value2());
    }
}

/* ************************************************************************* */

void writeInstruction(
    std::ostream& out,
    Mapping& mapping,
    const InstructionOr& instr)
{
    // | `or`        | `0xA0` + `<type>` + `<value1>` + `<value2>` | 1+N+2+2
    // bytes   | | `or`        | `0xA1` + `<type>` + `<value1>` + `<constant>`
    // | 1+N+2+M bytes   | | `or`        | `0xA2` + `<type>` + `<constant>` +
    // `<value2>`              | 1+N+M+2 bytes   |

    if (!instr.value2()->isConst())
    {
        if (!instr.value1()->isConst())
        {
            writeByte(out, Byte{0xA0});
            writeType(out, *instr.resultType());
            writeValue(out, mapping, instr.value1());
            writeValue(out, mapping, instr.value2());
        }
        else
        {
            writeByte(out, Byte{0xA2});
            writeType(out, *instr.resultType());
            writeConst(out, instr.value1());
            writeValue(out, mapping, instr.value2());
        }
    }
    else
    {
        writeByte(out, Byte{0xA1});
        writeType(out, *instr.resultType());
        writeValue(out, mapping, instr.value1());
        writeConst(out, instr.value2());
    }

    writeValue(out, mapping, instr.result());
}

/* ************************************************************************* */

void writeInstruction(
    std::ostream& out,
    Mapping& mapping,
    const InstructionXor& instr)
{
    // | `xor`       | `0xB0` + `<type>` + `<value1>` + `<value2>` | 1+N+2+2
    // bytes   | | `xor`       | `0xB1` + `<type>` + `<value1>` + `<constant>`
    // | 1+N+2+M bytes   | | `xor`       | `0xB2` + `<type>` + `<constant>` +
    // `<value2>`              | 1+N+M+2 bytes   |

    if (!instr.value2()->isConst())
    {
        if (!instr.value1()->isConst())
        {
            writeByte(out, Byte{0xB0});
            writeType(out, *instr.resultType());
            writeValue(out, mapping, instr.value1());
            writeValue(out, mapping, instr.value2());
        }
        else
        {
            writeByte(out, Byte{0xB2});
            writeType(out, *instr.resultType());
            writeConst(out, instr.value1());
            writeValue(out, mapping, instr.value2());
        }
    }
    else
    {
        writeByte(out, Byte{0xB1});
        writeType(out, *instr.resultType());
        writeValue(out, mapping, instr.value1());
        writeConst(out, instr.value2());
    }

    writeValue(out, mapping, instr.result());
}

/* ************************************************************************* */

void writeInstruction(
    std::ostream& out,
    Mapping& mapping,
    const InstructionBranch& instr)
{
    // | `branch`    | `0xC0` + `<label>` | 1+2 bytes       |

    writeByte(out, Byte{0xC0});
    writeBlock(out, mapping, instr.block());
}

/* ************************************************************************* */

void writeInstruction(
    std::ostream& out,
    Mapping& mapping,
    const InstructionBranchCondition& instr)
{
    // | `branch`    | `0xC1` + `<value>` + `<label1>` + `<label2>` | 1+2+2+2
    // bytes   |

    writeByte(out, Byte{0xC1});
    writeValue(out, mapping, instr.condition());
    writeBlock(out, mapping, instr.blockTrue());
    writeBlock(out, mapping, instr.blockFalse());
}

/* ************************************************************************* */

void writeInstruction(
    std::ostream& out,
    Mapping& mapping,
    const InstructionCall& instr)
{
    // | `call`      | `0xD0` + `<types...>` + `<name>` | 1+N+M bytes     | |
    // `call`      | `0xD1` + `<type>` + `<types...>` + `<name>` | 1+N+M+K bytes
    // |

    if (instr.resultType() != nullptr)
    {
        writeByte(out, Byte{0xD1});
        writeType(out, *instr.resultType());
        writeList(out, instr.arguments(), [](auto& out, const auto& arg) {
            writeType(out, *arg->type());
        });

        // Write function name
        writeString(out, instr.name());

        writeList(out, instr.arguments(), [&](auto& out, const auto& arg) {
            if (arg->isConst())
            {
                writeByte(out, Byte(0x01));
                writeConst(out, arg);
            }
            else
            {
                writeByte(out, Byte(0x00));
                writeValue(out, mapping, arg);
            }
        });

        writeValue(out, mapping, instr.result());
    }
    else
    {
        writeByte(out, Byte{0xD0});
        writeList(out, instr.arguments(), [](auto& out, const auto& arg) {
            writeType(out, *arg->type());
        });

        // Write function name
        writeString(out, instr.name());

        writeList(out, instr.arguments(), [&](auto& out, const auto& arg) {
            if (arg->isConst())
            {
                writeByte(out, Byte(0x01));
                writeConst(out, arg);
            }
            else
            {
                writeByte(out, Byte(0x00));
                writeValue(out, mapping, arg);
            }
        });
    }
}

/* ************************************************************************* */

void writeInstruction(
    std::ostream& out,
    Mapping& mapping,
    const InstructionReturn& instr)
{
    // | `return`    | `0xE1` + `<type>` + `<value>` | 1+N+2 bytes     |

    writeByte(out, Byte{0xE1});
    writeType(out, *instr.type());
    writeUint16(out, mapValue(mapping, instr.value()));
}

/* ************************************************************************* */

void writeInstruction(
    std::ostream& out,
    Mapping& mapping,
    const InstructionReturnVoid& instr)
{
    // | `return`    | `0xE0` | 1 bytes         |

    writeByte(out, Byte{0xE0});
}

/* ************************************************************************* */

void writeInstruction(
    std::ostream& out,
    Mapping& mapping,
    const Instruction& instr)
{
    switch (instr.kind())
    {
    case InstructionKind::Alloc:
        writeInstruction(out, mapping, instr.as<InstructionAlloc>());
        break;
    case InstructionKind::Store:
        writeInstruction(out, mapping, instr.as<InstructionStore>());
        break;
    case InstructionKind::Load:
        writeInstruction(out, mapping, instr.as<InstructionLoad>());
        break;
    case InstructionKind::Add:
        writeInstruction(out, mapping, instr.as<InstructionAdd>());
        break;
    case InstructionKind::Sub:
        writeInstruction(out, mapping, instr.as<InstructionSub>());
        break;
    case InstructionKind::Mul:
        writeInstruction(out, mapping, instr.as<InstructionMul>());
        break;
    case InstructionKind::Div:
        writeInstruction(out, mapping, instr.as<InstructionDiv>());
        break;
    case InstructionKind::Rem:
        writeInstruction(out, mapping, instr.as<InstructionRem>());
        break;
    case InstructionKind::Cmp:
        writeInstruction(out, mapping, instr.as<InstructionCmp>());
        break;
    case InstructionKind::And:
        writeInstruction(out, mapping, instr.as<InstructionAnd>());
        break;
    case InstructionKind::Or:
        writeInstruction(out, mapping, instr.as<InstructionOr>());
        break;
    case InstructionKind::Xor:
        writeInstruction(out, mapping, instr.as<InstructionXor>());
        break;
    case InstructionKind::Branch:
        writeInstruction(out, mapping, instr.as<InstructionBranch>());
        break;
    case InstructionKind::BranchCondition:
        writeInstruction(out, mapping, instr.as<InstructionBranchCondition>());
        break;
    case InstructionKind::Call:
        writeInstruction(out, mapping, instr.as<InstructionCall>());
        break;
    case InstructionKind::Return:
        writeInstruction(out, mapping, instr.as<InstructionReturn>());
        break;
    case InstructionKind::ReturnVoid:
        writeInstruction(out, mapping, instr.as<InstructionReturnVoid>());
        break;
    }
}

/* ************************************************************************* */

void writeBlock(std::ostream& output, Mapping& mapping, const Block& block)
{
    writeList(
        output, block.instructions(), [&](auto& output, const auto& instr) {
            writeInstruction(output, mapping, *instr);
        });
}

/* ************************************************************************* */

void writeFunction(std::ostream& output, const Function& function)
{
    // Write function name
    writeString(output, function.name());

    // Return type
    if (function.returnType())
    {
        writeType(output, *function.returnType());
    }
    else
    {
        writeByte(output, Byte{0x00});
    }

    // Parameter types
    writeList(
        output, function.parameterTypes(), [](auto& output, const auto& type) {
            writeType(output, *type);
        });

    // Blocks
    Mapping mapping;
    writeList(output, function.blocks(), [&](auto& output, const auto& block) {
        writeBlock(output, mapping, *block);
    });
}

/* ************************************************************************* */

} // namespace

/* ************************************************************************* */

void serialize(std::ostream& output, const Module& module)
{
    // Write guard
    writeByte(output, Byte('S'));
    writeByte(output, Byte('H'));
    writeByte(output, Byte('R'));
    writeByte(output, Byte('D'));

    // Version 0.1
    writeByte(output, Byte(0x00));
    writeByte(output, Byte(0x01));

    // TODO: write structures
    writeUint16(output, 0);

    // Write functions
    writeList(
        output, module.functions(), [](auto& output, const auto& function) {
            writeFunction(output, *function);
        });
}

/* ************************************************************************* */

} // namespace shard::ir

/* ************************************************************************* */

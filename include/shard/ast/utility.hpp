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
#include "shard/ViewPtr.hpp"
#include "shard/UniquePtr.hpp"
#include "shard/utility.hpp"
#include "shard/SourceLocation.hpp"
#include "shard/SourceRange.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {


/* ************************************************************************* */

/**
 * @brief Helper class for storing location in source code.
 */
class LocationInfo
{

// Public Ctors & Dtors
public:


    /**
     * @brief Constructor.
     * @param range Source range.
     */
    LocationInfo(SourceRange range) noexcept
        : m_range(moveValue(range))
    {
        // Nothing to do
    }


// Public Accessors & Mutators
public:


    /**
     * @brief Returns source range.
     * @return
     */
    const SourceRange& getSourceRange() const noexcept
    {
        return m_range;
    }


    /**
     * @brief Returns source range start.
     * @return
     */
    const SourceLocation& getSourceStart() const noexcept
    {
        return getSourceRange().getStart();
    }


    /**
     * @brief Returns source range end.
     * @return
     */
    const SourceLocation& getSourceEnd() const noexcept
    {
        return getSourceRange().getEnd();
    }


// Private Data Members
private:

    /// Source range.
    SourceRange m_range;

};


/* ************************************************************************* */

/**
 * @brief Cast helper class.
 * @tparam BaseT  Base type.
 * @tparam ChildT Child type.
 */
template<typename BaseT, typename ChildT>
class KindCaster
{

// Public Operations
public:


    /**
     * @brief Cast base type to specified subclass.
     * @param value Value to cast.
     * @return Casted value.
     */
    static ChildT& cast(BaseT& value) noexcept
    {
        SHARD_ASSERT(ChildT::is(value));
        return static_cast<const ChildT&>(value);
    }


    /**
     * @brief Cast base type to specified subclass.
     * @param value Value to cast.
     * @return Casted value.
     */
    static const ChildT& cast(const BaseT& value) noexcept
    {
        SHARD_ASSERT(ChildT::is(value));
        return static_cast<const ChildT&>(value);
    }


    /**
     * @brief Cast base type to specified subclass.
     * @param value Value to cast.
     * @return Casted value.
     */
    static ViewPtr<ChildT> cast(ViewPtr<BaseT> value) noexcept
    {
        SHARD_ASSERT(ChildT::is(value));
        return ViewPtr<ChildT>(static_cast<ChildT*>(value.get()));
    }


    /**
     * @brief Cast base type to specified subclass.
     * @param value Value to cast.
     * @return Casted value.
     */
    static ViewPtr<const ChildT> cast(ViewPtr<const BaseT> value) noexcept
    {
        SHARD_ASSERT(ChildT::is(value));
        return ViewPtr<const ChildT>(static_cast<const ChildT*>(value.get()));
    }


    /**
     * @brief Cast base type to specified subclass.
     * @param value Value to cast.
     * @return Casted value.
     */
    static ViewPtr<ChildT> cast(const UniquePtr<BaseT>& value) noexcept
    {
        SHARD_ASSERT(ChildT::is(value));
        return ViewPtr<ChildT>(static_cast<ChildT*>(value.get()));
    }


    /**
     * @brief Cast base type to specified subclass.
     * @param value Value to cast.
     * @return Casted value.
     */
    static ViewPtr<const ChildT> cast(const UniquePtr<const BaseT>& value) noexcept
    {
        SHARD_ASSERT(ChildT::is(value));
        return ViewPtr<const ChildT>(static_cast<const ChildT*>(value.get()));
    }

};

/* ************************************************************************* */

/**
 * @brief Helper class for types.
 * @tparam EnumT Enum type.
 * @tparam KIND  Tested enum value.
 * @tparam BaseT Base type.
 */
template<typename EnumT, EnumT KIND, typename BaseT>
class KindTester
{


// Public Operations
public:


    /**
     * @brief Check if given object match this class requirements.
     * @param value Value to test.
     * @return
     */
    static bool is(const BaseT& value) noexcept
    {
        return value.getKind() == KIND;
    }


    /**
     * @brief Check if given object match this class requirements.
     * @param value Value to test.
     * @return
     */
    static bool is(ViewPtr<const BaseT> value) noexcept
    {
        SHARD_ASSERT(value);
        return is(*value);
    }


    /**
     * @brief Check if given object match this class requirements.
     * @param value Value to test.
     * @return
     */
    static bool is(const UniquePtr<BaseT>& value) noexcept
    {
        SHARD_ASSERT(value);
        return is(*value);
    }


    /**
     * @brief Check if given object match this class requirements.
     * @param value Value to test.
     * @return
     */
    static bool is(const UniquePtr<const BaseT>& value) noexcept
    {
        SHARD_ASSERT(value);
        return is(*value);
    }

};

/* ************************************************************************* */

/**
 * @brief Helper class for types.
 * @tparam EnumT Enum type.
 * @tparam KIND1 The first tested enum value.
 * @tparam KIND2 The last tested enum value.
 * @tparam BaseT Base type.
 */
template<typename EnumT, EnumT KIND1, EnumT KIND2, typename BaseT>
class KindRangeTester
{


// Public Operations
public:


    /**
     * @brief Check if given object match this class requirements.
     * @param value Value to test.
     * @return
     */
    static bool is(const BaseT& value) noexcept
    {
        return
            value.getKind() >= KIND1 &&
            value.getKind() <= KIND2
        ;
    }


    /**
     * @brief Check if given object match this class requirements.
     * @param value Value to test.
     * @return
     */
    static bool is(ViewPtr<BaseT> value) noexcept
    {
        SHARD_ASSERT(value);
        return is(*value);
    }


    /**
     * @brief Check if given object match this class requirements.
     * @param value Value to test.
     * @return
     */
    static bool is(const UniquePtr<BaseT>& value) noexcept
    {
        SHARD_ASSERT(value);
        return is(*value);
    }

};

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

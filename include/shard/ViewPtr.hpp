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
#include <type_traits>
#include <utility>

/* ************************************************************************* */

namespace shard {

/* ************************************************************************* */

/**
 * @brief      View pointer - non-owning pointer.
 *
 *             Implementation based on GCC libstdc++ version.
 *
 * @tparam     T     Pointer type.
 */
template<typename T>
class ViewPtr
{

public:
    // Types

    // publish our template parameter and variations thereof
    using element_type = T;

public:
    // Ctors & Dtors

    /**
     * @brief      Default constructor.
     */
    constexpr ViewPtr() noexcept
        : m_ptr(nullptr)
    {
        // Nothing to do
    }

    /**
     * @brief      Nullptr constructor.
     */
    constexpr ViewPtr(std::nullptr_t) noexcept
        : m_ptr(nullptr)
    {
        // Nothing to do
    }

    /**
     * @brief      Raw pointer constructor.
     *
     * @param      ptr   Pointer.
     */
    constexpr ViewPtr(T* ptr) noexcept
        : m_ptr(ptr)
    {
        // Nothing to do
    }

    /**
     * @brief      Copy constructor.
     *
     * @param      rhs        Source pointer.
     *
     * @tparam     U          Source pointer type.
     */
    template<
        typename U,
        typename = typename std::enable_if_t<
            std::is_convertible<std::add_pointer_t<U>, T*>::value>>
    constexpr ViewPtr(ViewPtr<U> rhs) noexcept
        : m_ptr(rhs.get())
    {
        // Nothing to do
    }

public:
    // Operators

    /**
     * @brief      Returns reference.
     *
     * @return     Reference.
     */
    constexpr T& operator*() const
    {
        return *get();
    }

    /**
     * @brief      Pointer access.
     *
     * @return     The pointer.
     */
    constexpr T* operator->() const noexcept
    {
        return get();
    }

    /**
     * @brief      Bool conversion operator.
     */
    constexpr explicit operator bool() const noexcept
    {
        return get() != nullptr;
    }

    /**
     * @brief      Explictit raw pointer cast.
     *
     * @return     Raw pointer.
     */
    constexpr explicit operator T*() const noexcept
    {
        return get();
    }

public:
    // Accessors & Mutators

    /**
     * @brief      Returns raw pointer.
     *
     * @return     Raw pointer.
     */
    constexpr T* get() const noexcept
    {
        return m_ptr;
    }

public:
    // Operations

    /**
     * @brief      Release pointer.
     *
     * @return     Released raw pointer.
     */
    constexpr T* release() noexcept
    {
        T* tmp = get();
        reset();
        return tmp;
    }

    /**
     * @brief      Reset pointer.
     *
     * @param      ptr   New raw pointer.
     */
    constexpr void reset(T* ptr = nullptr) noexcept
    {
        m_ptr = ptr;
    }

    /**
     * @brief      Swap operation.
     *
     * @param      rhs   The second pointer.
     */
    constexpr void swap(ViewPtr& rhs) noexcept
    {
        std::swap(m_ptr, rhs.m_ptr);
    }

private:
    // Data Members

    // Pointer.
    T* m_ptr = nullptr;
};

/* ************************************************************************* */

/**
 * @brief      Make view pointer from raw pointer.
 *
 * @param      ptr   Raw pointer.
 *
 * @tparam     T     Pointer type.
 *
 * @return     View pointer.
 */
template<typename T>
ViewPtr<T> makeView(T* ptr) noexcept
{
    return ViewPtr<T>(ptr);
}

/* ************************************************************************* */

/**
 * @brief Equality comparison.
 */
template<typename T, typename U>
bool operator==(ViewPtr<T> lhs, ViewPtr<U> rhs) noexcept
{
    return lhs.get() == rhs.get();
}

/* ************************************************************************* */

/**
 * @brief Equality comparison.
 */
template<typename T, typename U>
bool operator!=(ViewPtr<T> lhs, ViewPtr<U> rhs) noexcept
{
    return !(lhs == rhs);
}

/* ************************************************************************* */

/**
 * @brief Equality comparison.
 */
template<typename T>
bool operator==(ViewPtr<T> ptr, std::nullptr_t) noexcept
{
    return !ptr;
}

/* ************************************************************************* */

/**
 * @brief Equality comparison.
 */
template<typename T>
bool operator==(std::nullptr_t, ViewPtr<T> ptr) noexcept
{
    return !ptr;
}

/* ************************************************************************* */

/**
 * @brief Equality comparison.
 */
template<typename T>
bool operator!=(ViewPtr<T> ptr, std::nullptr_t) noexcept
{
    return bool(ptr);
}

/* ************************************************************************* */

/**
 * @brief Equality comparison.
 */
template<typename T>
bool operator!=(std::nullptr_t, ViewPtr<T> ptr) noexcept
{
    return bool(ptr);
}

/* ************************************************************************* */

/**
 * @brief Equality comparison.
 */
template<typename T, typename U>
bool operator==(ViewPtr<T> lhs, U* rhs) noexcept
{
    return lhs.get() == rhs;
}

/* ************************************************************************* */

/**
 * @brief Equality comparison.
 */
template<typename T, typename U>
bool operator==(T* lhs, ViewPtr<U> rhs) noexcept
{
    return lhs == rhs.get();
}

/* ************************************************************************* */

/**
 * @brief Equality comparison.
 */
template<typename T, typename U>
bool operator!=(ViewPtr<T> lhs, U* rhs) noexcept
{
    return !operator==(lhs, rhs);
}

/* ************************************************************************* */

/**
 * @brief Equality comparison.
 */
template<typename T, typename U>
bool operator!=(T* lhs, ViewPtr<U> rhs) noexcept
{
    return !operator==(lhs, rhs);
}

/* ************************************************************************* */

/**
 * @brief Ordered comparison.
 */
template<typename T, typename U>
bool operator<(ViewPtr<T> lhs, ViewPtr<U> rhs) noexcept
{
    return lhs.get() < rhs.get();
}

/* ************************************************************************* */

/**
 * @brief Ordered comparison.
 */
template<typename T, typename U>
bool operator>(ViewPtr<T> lhs, ViewPtr<U> rhs) noexcept
{
    return rhs < lhs;
}

/* ************************************************************************* */

/**
 * @brief Ordered comparison.
 */
template<typename T, typename U>
bool operator<=(ViewPtr<T> lhs, ViewPtr<U> rhs) noexcept
{
    return !(rhs < lhs);
}

/* ************************************************************************* */

/**
 * @brief Ordered comparison.
 */
template<typename T, typename U>
bool operator>=(ViewPtr<T> lhs, ViewPtr<U> rhs) noexcept
{
    return !(lhs < rhs);
}

/* ************************************************************************* */

} // namespace shard

/* ************************************************************************* */

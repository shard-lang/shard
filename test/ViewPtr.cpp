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

// C++
#include <type_traits>

// GTest
#include "gtest/gtest.h"

// CeCe
#include "shard/ViewPtr.hpp"

/* ************************************************************************ */

using namespace shard;

/* ************************************************************************ */

namespace {

/* ************************************************************************ */

struct Nontrivial { Nontrivial() {} };
struct Other {};
struct Base {};
struct Derived : Base {};

static_assert(!std::is_trivially_constructible<ViewPtr<Nontrivial>>::value, "");
static_assert(std::is_trivially_copyable<ViewPtr<Nontrivial>>::value, "");
static_assert(std::is_trivially_destructible<ViewPtr<Nontrivial>>::value, "");

static_assert(std::is_constructible<ViewPtr<Nontrivial>, Nontrivial*>::value, "");
static_assert(std::is_constructible<ViewPtr<Base>, Base*>::value, "");
static_assert(std::is_constructible<ViewPtr<Base>, Derived*>::value, "");
static_assert(!std::is_constructible<ViewPtr<Base>, Other*>::value, "");
static_assert(std::is_constructible<ViewPtr<Base>, ViewPtr<Base>>::value, "");
static_assert(std::is_constructible<ViewPtr<Base>, ViewPtr<Derived>>::value, "");
static_assert(!std::is_constructible<ViewPtr<Base>, ViewPtr<Other>>::value, "");

//static_assert(!std::is_assignable<ViewPtr<Nontrivial>, Nontrivial*>::value, "");
static_assert(std::is_assignable<ViewPtr<Nontrivial>, ViewPtr<Nontrivial>>::value, "");
static_assert(std::is_assignable<ViewPtr<Base>, ViewPtr<Base>>::value, "");
static_assert(std::is_assignable<ViewPtr<Base>, ViewPtr<Derived>>::value, "");
static_assert(!std::is_assignable<ViewPtr<Base>, ViewPtr<Other>>::value, "");
static_assert(std::is_assignable<ViewPtr<const int>, ViewPtr<int>>::value, "");
static_assert(!std::is_assignable<ViewPtr<int>, ViewPtr<const int>>::value, "");

/* ************************************************************************ */

constexpr bool assignHelper(ViewPtr<const int> a, ViewPtr<const int> b)
{
    a = b;
    return (a.get() == b.get());
}

/* ************************************************************************ */

}

/* ************************************************************************ */

TEST(ViewPtr, construction)
{
    struct B {};
    struct D : B {};

    {
        ViewPtr<int> a;
        EXPECT_FALSE(a);
        ViewPtr<int> b{nullptr};
        EXPECT_FALSE(b);
    }

    {
        int x{};
        ViewPtr<int> a{&x};
        ViewPtr<int> b{a};
        EXPECT_EQ(a, b);
    }

    {
        int x{};
        ViewPtr<int> a;
        ViewPtr<const int> b{a};
        EXPECT_EQ(a, b);
    }

    {
        D x{};
        ViewPtr<D> a{&x};
        ViewPtr<B> b{a};
        EXPECT_EQ(a, b);
    }

    {
        D x{};
        ViewPtr<D> a{&x};
        ViewPtr<B> b{std::move(a)};
        EXPECT_EQ(a, b);
    }

    {
        static constexpr D x{};
        constexpr ViewPtr<const D> a{&x};
        constexpr ViewPtr<const B> b{std::move(a)};
        EXPECT_EQ(a, b);
        constexpr ViewPtr<const B> c{a};
        EXPECT_EQ(a, b);
        EXPECT_EQ(a, c);
        EXPECT_EQ(b, c);
        constexpr ViewPtr<int> d;
        constexpr ViewPtr<int> e{nullptr};
        EXPECT_FALSE(d);
        EXPECT_FALSE(e);
    }
}

/* ************************************************************************ */

TEST(ViewPtr, makeView)
{
    const int i = 42;
    auto o = makeView(&i);
    static_assert(std::is_same<decltype(o), ViewPtr<const int>>(), "");
    ASSERT_TRUE(o);
    EXPECT_EQ(*o, 42);
    EXPECT_EQ(o.get(), &i);
}

/* ************************************************************************ */

TEST(ViewPtr, assign)
{
    {
        ViewPtr<int> a;
        int b;
        a = &b;
        EXPECT_EQ(a, &b);
    }

    {
        ViewPtr<int> a;
        ViewPtr<int> b;
        a = b;
        EXPECT_EQ(a, b);
    }

    {
        int x{};
        ViewPtr<int> a;
        ViewPtr<int> b{&x};
        EXPECT_NE(a, b);
        a = b;
        EXPECT_EQ(a, b);
    }

    {
        int x{};
        ViewPtr<const int> a;
        ViewPtr<int> b{&x};
        EXPECT_NE(a, b);
        a = b;
        EXPECT_EQ(a, b);
    }

    {
        struct B {};
        struct D : B {};

        D x{};
        ViewPtr<B> a;
        ViewPtr<D> b{&x};
        EXPECT_NE(a, b);
        a = b;
        EXPECT_EQ(a, b);
    }

    {
        static constexpr int x{};
        constexpr ViewPtr<const int> a;
        constexpr ViewPtr<const int> b{&x};
        constexpr bool assigned = assignHelper(a, b);
        EXPECT_TRUE(assigned);
    }
}

/* ************************************************************************ */

TEST(ViewPtr, relop)
{
    {
        ViewPtr<int> a, b;
        EXPECT_EQ(a, b);
    }

    {
        int x[2]{};
        ViewPtr<int> a{&x[0]};
        ViewPtr<int> b{&x[1]};
        EXPECT_NE(a, b);
        EXPECT_LT(a, b);
        EXPECT_LE(a, b);
        EXPECT_GE(b, a);
        EXPECT_GT(b, a);
    }

    {
        int x{};
        ViewPtr<int> a{&x};
        ViewPtr<int> b{&x};
        EXPECT_EQ(a, b);
    }

    {
        static constexpr int x[2]{};
        constexpr ViewPtr<const int> a{&x[0]};
        constexpr ViewPtr<const int> b{&x[1]};
        EXPECT_NE(a, b);
        EXPECT_LT(a, b);
        EXPECT_LE(a, b);
        EXPECT_GE(b, a);
        EXPECT_GT(b, a);
    }

    {
        static constexpr int x{};
        constexpr ViewPtr<const int> a{&x};
        constexpr ViewPtr<const int> b{&x};
        EXPECT_EQ(a, b);
    }
}

/* ************************************************************************ */

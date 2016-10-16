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

#include <gtest/gtest.h>
// Shard Core
#include "core/src/Path.hpp"
#include "core/src/String.hpp"
#include "core/src/DynamicArray.hpp"
// Shard Tokenizer
#include "tokenizer/src/Source.hpp"

/* ************************************************************************* */

using namespace shard;
using namespace shard::tokenizer;

static void test_impl(
        int line,
        const String& code,
        DynamicArray<ReadMode> correct)
{
    SCOPED_TRACE(code);

    Source source(code);

    DynamicArray<ReadMode> result;
    result.reserve(correct.size());

    while (!source.empty())
    {
        result.push_back(source.extract());
    }

    ASSERT_EQ(result.size(), correct.size());

    for (int i = 0; i < correct.size(); i++)
    {
        ASSERT_EQ(result[i], correct[i]);
    }
}

static void test_file_impl(
        int line,
        const String& code,
        DynamicArray<ReadMode> correct)
{
    SCOPED_TRACE(code);

    const Path path (code);
    Source source(path);

    DynamicArray<ReadMode> result;
    result.reserve(correct.size());

    try
    {
        while (!source.empty())
        {
            result.push_back(source.extract());
        }
    }
    catch (std::exception& ex)
    {
        // Nothing to do
    }

    ASSERT_EQ(correct.size(), result.size());

    for (int i = 0; i < correct.size(); i++)
    {
        ASSERT_EQ(correct[i], result[i]);
    }
}

#define test(...) test_impl(__LINE__, __VA_ARGS__)
#define test_file(...) test_file_impl(__LINE__,__VA_ARGS__)

TEST(Source, basic)
{
    test(".", {'.' });
    test("{}", {'{', '}'});
}
TEST(Source, basic_long)
{
    test("{,.-dsah  \t\n\r   wq&@v<>b}",
    {'{', ',', '.', '-', 'd', 's', 'a', 'h', ' ', ' ', '\t', '\n', '\r', ' ', ' ', ' ', 'w', 'q', '&', '@', 'v', '<', '>', 'b', '}'});
}
TEST(Source, empty)
{
    test("", {});
}
TEST(Source, file_basic)
{
    test_file("../test/source-test-file_basic.txt",
    {'\n', '\r', 'a', '\n', '{', '}', ' ', ' ', ' ', 'b', '\t', 'a'});
}
TEST(Source, file_empty)
{
    test_file("../test/source-test-file_empty.txt", {});
}
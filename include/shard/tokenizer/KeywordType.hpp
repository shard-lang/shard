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

#define KEYWORDS \
    KEYWORD(Namespace, namespace), \
    KEYWORD(Class, class), \
    KEYWORD(Enum, enum), \
    KEYWORD(Presenter, presenter), \
    KEYWORD(Model, model), \
    KEYWORD(Public, public), \
    KEYWORD(Protected, protected), \
    KEYWORD(Private, private), \
    KEYWORD(Action, action), \
    KEYWORD(Render, render), \
    KEYWORD(Before, before), \
    KEYWORD(Var, var), \
    KEYWORD(Auto, auto), \
    KEYWORD(Int, int), \
    KEYWORD(Char, char), \
    KEYWORD(Bool, bool), \
    KEYWORD(Float, float), \
    KEYWORD(String, string), \
    KEYWORD(Null, null), \
    KEYWORD(True, true), \
    KEYWORD(False, false), \
    KEYWORD(Array, array), \
    KEYWORD(As, as), \
    KEYWORD(Use, use), \
    KEYWORD(Extends, extends), \
    KEYWORD(If, if), \
    KEYWORD(Else, else), \
    KEYWORD(Do, do), \
    KEYWORD(While, while), \
    KEYWORD(For, for), \
    KEYWORD(Try, try), \
    KEYWORD(Catch, catch), \
    KEYWORD(Finally, finally), \
    KEYWORD(Throw, throw)

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace tokenizer {

/* ************************************************************************* */

enum class KeywordType
{
#define KEYWORD(name, str) name
    KEYWORDS
#undef KEYWORD
};

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

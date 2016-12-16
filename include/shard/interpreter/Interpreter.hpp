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
#include "shard/ViewPtr.hpp"
#include "shard/interpreter/Value.hpp"

/* ************************************************************************* */

namespace shard { inline namespace v1 { namespace ast {

/* ************************************************************************* */

class Expr;
class Stmt;
class Module;

/* ************************************************************************* */

} } }

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace interpreter {

/* ************************************************************************* */

class Context;

/* ************************************************************************* */

/**
 * @brief      Interpret a compilation module.
 *
 * @param      unit  The unit.
 * @param      ctx   The context.
 */
extern void interpret(ViewPtr<const ast::Module> unit, Context& ctx);

/* ************************************************************************* */

/**
 * @brief      Interpret a compilation unit.
 *
 * @param      unit  The unit.
 */
extern void interpret(ViewPtr<const ast::Module> unit);

/* ************************************************************************* */

/**
 * @brief      Interpret a statement.
 *
 * @param      stmt  The statement.
 * @param      ctx   The context.
 */
extern void interpret(ViewPtr<const ast::Stmt> stmt, Context& ctx);

/* ************************************************************************* */

/**
 * @brief      Interpret an expression.
 *
 * @param      expr  The expression.
 * @param      ctx   The context.
 */
extern Value interpret(ViewPtr<const ast::Expr> expr, Context& ctx);

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

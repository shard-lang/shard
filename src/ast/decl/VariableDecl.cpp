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
#include "shard/ast/decl/VariableDecl.hpp"

// Shard
#include "shard/ast/Expr.hpp"

/* ************************************************************************* */

namespace shard::ast {

/* ************************************************************************* */

VariableDecl::VariableDecl(Type type, String name, UniquePtr<Expr> initExpr, SourceRange range)
    : Decl(Kind, std::move(name), std::move(range))
    , m_type(std::move(type))
    , m_initExpr(std::move(initExpr))
{
    // Nothing to do
}

/* ************************************************************************* */

VariableDecl::~VariableDecl() = default;

/* ************************************************************************* */

void VariableDecl::setType(Type type)
{
    m_type = std::move(type);
}

/* ************************************************************************* */

void VariableDecl::setInitExpr(UniquePtr<Expr> expr)
{
    m_initExpr = std::move(expr);
}

/* ************************************************************************* */

UniquePtr<VariableDecl> VariableDecl::make(Type type, String name, UniquePtr<Expr> initExpr, SourceRange range)
{
    return makeUnique<VariableDecl>(std::move(type), std::move(name), std::move(initExpr), std::move(range));
}

/* ************************************************************************* */

}

/* ************************************************************************* */

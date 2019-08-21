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
#include "shard/ast/Stmt.hpp"
#include "shard/parser/Parser.hpp"

/* ************************************************************************* */

namespace shard::builtin {

/* ************************************************************************* */

/**
 * @brief      Parse function statement.
 *
 * @param      parser  The parser.
 *
 * @return     The result statement.
 */
ast::StmtPtr parseFunc(parser::Parser& parser);

/* ************************************************************************* */

/**
 * @brief      Parse var statement.
 *
 * @param      parser  The parser.
 *
 * @return     The result statement.
 */
ast::StmtPtr parseVar(parser::Parser& parser);

/* ************************************************************************* */

/**
 * @brief      Parse const statement.
 *
 * @param      parser  The parser.
 *
 * @return     The result statement.
 */
ast::StmtPtr parseConst(parser::Parser& parser);

/* ************************************************************************* */

/**
 * @brief      Parse return statement.
 *
 * @param      parser  The parser.
 *
 * @return     Return statement.
 */
ast::StmtPtr parseReturn(parser::Parser& parser);

/* ************************************************************************* */

/**
 * @brief      Extend parser by builtin extensions.
 *
 * @param      parser  The parser.
 */
void extendParser(parser::Parser& parser);

/* ************************************************************************* */

/**
 * @brief      Shard parser extended by builtin language.
 */
class Parser : public parser::Parser
{
public:
    // Ctors & Dtors

    /**
     * @brief      Create a parser.
     *
     * @param      begin  The begin iterator.
     * @param      end    The end iterator.
     *
     * @tparam     IT     Iterator type.
     */
    template<typename IT>
    explicit Parser(IT begin, IT end)
        : parser::Parser(begin, end)
    {
        extendParser(*this);
    }

    /**
     * @brief      Create a parser.
     *
     * @param      tokenizer  The tokenizer.
     */
    explicit Parser(tokenizer::Tokenizer& tokenizer)
        : Parser(tokenizer.begin(), tokenizer.end())
    {
        // Nothing to do
    }
};

/* ************************************************************************* */

} // namespace shard::builtin

/* ************************************************************************* */

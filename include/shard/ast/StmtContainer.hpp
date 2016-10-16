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
#include "shard/UniquePtr.hpp"
#include "shard/DynamicArray.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace ast {

/* ************************************************************************* */

class Stmt;

/* ************************************************************************* */

/**
 * @brief Statements container.
 */
class StmtContainer
{

// Public Ctors & Dtors
public:


    /**
     * @brief Default constructor.
     */
    StmtContainer() noexcept;


    /**
     * @brief Constructor.
     * @param stmts A list of statements.
     * @param range Source range.
     */
    explicit StmtContainer(DynamicArray<UniquePtr<Stmt>> stmts) noexcept;


    /**
     * @brief Destructor.
     */
    ~StmtContainer();


// Public Accessors & Mutators
public:


    /**
     * @brief Checks if the container has no elements.
     * @return
     */
    bool isEmpty() const noexcept
    {
        return m_statements.empty();
    }


    /**
     * @brief Returns the number of elements in the container.
     * @return
     */
    int getCount() const noexcept
    {
        return m_statements.size();
    }


    /**
     * @brief Returns inner statements.
     * @return A list of statements.
     */
    const DynamicArray<UniquePtr<Stmt>>& getStatements() const noexcept
    {
        return m_statements;
    }


    /**
     * @brief Adds a statement.
     * @param stmt New statement.
     */
    void addStatement(UniquePtr<Stmt> stmt) noexcept;


    /**
     * @brief Returns an iterator to the first element of the container.
     * @return Iterator to the first element.
     */
    auto begin() noexcept
    {
        return m_statements.begin();
    }


    /**
     * @brief Returns an iterator to the first element of the container.
     * @return Iterator to the first element.
     */
    auto begin() const noexcept
    {
        return m_statements.begin();
    }


    /**
     * @brief Returns an iterator to the first element of the container.
     * @return Iterator to the first element.
     */
    auto cbegin() const noexcept
    {
        return m_statements.begin();
    }


    /**
     * @brief Returns an iterator to the element following the last element of the container.
     * @return Iterator to the element following the last element.
     */
    auto end() noexcept
    {
        return m_statements.end();
    }


    /**
     * @brief Returns an iterator to the element following the last element of the container.
     * @return Iterator to the element following the last element.
     */
    auto end() const noexcept
    {
        return m_statements.end();
    }


    /**
     * @brief Returns an iterator to the element following the last element of the container.
     * @return Iterator to the element following the last element.
     */
    auto cend() const noexcept
    {
        return m_statements.end();
    }


// Private Data Members
private:

    /// List of statements.
    DynamicArray<UniquePtr<Stmt>> m_statements;

};

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */

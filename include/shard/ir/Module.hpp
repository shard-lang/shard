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
#include "shard/PtrVector.hpp"
#include "shard/ir/Constant.hpp"
#include "shard/ir/Function.hpp"
#include "shard/ir/Type.hpp"

/* ************************************************************************* */

namespace shard::ir {

/* ************************************************************************* */

/**
 * @brief      The main class for storing source IR code.
 */
class Module
{

public:
    // Accessors & Mutators

    /**
     * @brief      Returns a list of types.
     *
     * @return     The types.
     */
    const PtrVector<Type>& types() const noexcept
    {
        return m_types;
    }

    /**
     * @brief      Set the list of types.
     *
     * @param      types  The types.
     */
    void setTypes(PtrVector<Type> types)
    {
        m_types = std::move(types);
    }

    /**
     * @brief      Add a new type.
     *
     * @param      type  The type.
     *
     * @return     Pointer to stored type.
     */
    ViewPtr<Type> addType(UniquePtr<Type> type)
    {
        m_types.push_back(std::move(type));
        return m_types.back().get();
    }

    /**
     * @brief      Create a new type.
     *
     * @param      args  The arguments.
     *
     * @tparam     T     Type type.
     * @tparam     Args  Argument types.
     *
     * @return     The created type.
     */
    template<typename T, typename... Args>
    ViewPtr<T> createType(Args&&... args)
    {
        auto ptr = addType(makeUnique<T>(std::forward<Args>(args)...));

        return static_cast<T*>(ptr.get());
    }

    /**
     * @brief      Returns a list of constants.
     *
     * @return     The constants.
     */
    const PtrVector<Value>& constants() const noexcept
    {
        return m_constants;
    }

    /**
     * @brief      Set the list of constants.
     *
     * @param      constants  The constants.
     */
    void setConstants(PtrVector<Value> constants)
    {
        m_constants = std::move(constants);
    }

    /**
     * @brief      Add a new constant.
     *
     * @param      constant  The constant.
     *
     * @return     Pointer to stored constant.
     */
    ViewPtr<Value> addConstant(UniquePtr<Value> constant)
    {
        m_constants.push_back(std::move(constant));
        return m_constants.back().get();
    }

    /**
     * @brief      Create a new constant.
     *
     * @param      args  The arguments.
     *
     * @tparam     T     Constant constant.
     * @tparam     Args  Argument constants.
     *
     * @return     The created constant.
     */
    template<typename T, typename... Args>
    ViewPtr<T> createConstant(Args&&... args)
    {
        auto ptr = addConstant(makeUnique<T>(std::forward<Args>(args)...));

        return static_cast<T*>(ptr.get());
    }

    /**
     * @brief      Returns a list of functions.
     *
     * @return     The functions.
     */
    const PtrVector<Function>& functions() const noexcept
    {
        return m_functions;
    }

    /**
     * @brief      Set the list of functions.
     *
     * @param      functions  The functions.
     */
    void setFunctions(PtrVector<Function> functions)
    {
        m_functions = std::move(functions);
    }

    /**
     * @brief      Add a function.
     *
     * @param      function  The function.
     *
     * @return     A pointer to added function.
     */
    ViewPtr<Function> addFunction(UniquePtr<Function> function)
    {
        m_functions.push_back(std::move(function));
        return m_functions.back().get();
    }

    /**
     * @brief      Create a new function.
     *
     * @param      name            The name.
     * @param      returnType      The return type.
     * @param      parameterTypes  The parameter types.
     *
     * @return     A pointer to created function.
     */
    ViewPtr<Function> createFunction(
        String name,
        ViewPtr<Type> returnType,
        Vector<ViewPtr<Type>> parameterTypes)
    {
        return addFunction(makeUnique<Function>(
            std::move(name), std::move(returnType), std::move(parameterTypes)));
    }

    /**
     * @brief      Create a new function.
     *
     * @param      name            The name.
     * @param      parameterTypes  The parameter types.
     *
     * @return     A pointer to created function.
     */
    ViewPtr<Function> createFunction(
        String name,
        Vector<ViewPtr<Type>> parameterTypes)
    {
        return addFunction(
            makeUnique<Function>(std::move(name), std::move(parameterTypes)));
    }

private:
    // Data Members

    /// Shared types.
    PtrVector<Type> m_types;

    /// Shared constants.
    PtrVector<Value> m_constants;

    /// A list of functions.
    PtrVector<Function> m_functions;
};

/* ************************************************************************* */

} // namespace shard::ir

/* ************************************************************************* */

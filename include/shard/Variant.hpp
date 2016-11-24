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

#include "shard/SharedPtr.hpp"

/* ************************************************************************* */

namespace shard {
inline namespace v1 {

/* ************************************************************************* */

/**
 * @brief Simple implementation of variant - class to hold any type.
 */
class Variant
{

private:

    /**
    * @brief Container for value which is being hold.
    */
    class VariantContainer
    {

    public: 

    	virtual ~VariantContainer() {}
    };

    /**
     * @brief Specific implementation for each type.
     */
    template<class T>
    class VariantContainerImpl : public VariantContainer
    {

    public:

        VariantContainerImpl(const T& value)
        	: m_value(value) {}

        ~VariantContainerImpl() {}

        T getValue() const noexcept { return m_value; }

        T m_value;
    };

private:

	SharedPtr<VariantContainer> m_container;

public:

    /**
     * @brief Contructor for empty variant.
     */
	Variant() :
		m_container(nullptr) {}

    /**
     * @brief Constructor of specific type.
     */
    template<typename T>
    explicit Variant(T value) :
        m_container(makeShared<VariantContainerImpl<T>>(value)) {}

public:

    /**
     * @brief Get copy of current value.
     */
    template<typename T>
    T get() const
    {
    	return static_cast<VariantContainerImpl<T>*>(m_container.get())->getValue();
    }

    /**
     * @brief Replace current value.
     */
    template<typename T>
    void set(T value)
    {
        m_container = makeShared<VariantContainerImpl<T>>(value);
    }
};

/* ************************************************************************* */

}
}

/* ************************************************************************* */
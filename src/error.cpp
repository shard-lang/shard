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
#include "shard/error.hpp"

// C++
#include <iostream>

/* ************************************************************************* */

namespace shard {

/* ************************************************************************* */

void error(StringView str) noexcept
{
    std::cerr << "\033[31m[ERROR]: " << str << "\033[0m" << std::endl;
    exit(1);
}

/* ************************************************************************* */

}

/* ************************************************************************* */

#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/integer_constant.hpp>

namespace BR {

template< bool value >
using BooleanConstant = IntegerConstant< bool, value >;

using BooleanTrue = BooleanConstant< true >;

using BooleanFalse = BooleanConstant< false >;

} // namespace BR

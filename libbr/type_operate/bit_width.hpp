#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/integer_constant.hpp>

namespace BR {

template< typename T >
using BitWidth = IntegerConstant< Size, sizeof(T) * BIT_PER_CHAR >;

} // namespace BR

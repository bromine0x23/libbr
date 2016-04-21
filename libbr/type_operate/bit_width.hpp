#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/integral_constant.hpp>

namespace BR {

template< typename T >
using BitWidth = IntegerConstant< Size, sizeof(T) * BIT_PER_BYTE >;

} // namespace BR

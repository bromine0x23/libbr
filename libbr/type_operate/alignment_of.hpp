#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/integer_constant.hpp>

namespace BR {

template< typename T >
using AlignmentOf = IntegerConstant< Size, alignof(T) >;

} // namespace BR
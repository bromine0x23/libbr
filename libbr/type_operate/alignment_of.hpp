#pragma once

#include <libbr/config.hpp>

#include <libbr/type_operate/integer.hpp>

namespace BR {

template< typename T >
using AlignmentOf = IntegerConstant< Size, alignof(T) >;

} // namespace BR
#pragma once

#include <libbr/config.hpp>

#include <libbr/type_operate/integer.hpp>

namespace BR {
namespace TypeOperate {

template< typename T >
using AlignmentOf = IntegerConstant< Size, alignof(T) >;

} // namespace TypeOperate
} // namespace BR


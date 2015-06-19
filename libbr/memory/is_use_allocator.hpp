#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {

template< typename TAllocator, typename ... T >
struct IsUseAllocator : BooleanFalse {};

} // namespace BR
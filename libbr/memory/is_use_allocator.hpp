#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {
namespace Memory {

template< typename ... T, typename TAllocator >
struct IsUseAllocator : TypeOperate::BooleanFalse {};

} // namespace Memory
} // namespace BR
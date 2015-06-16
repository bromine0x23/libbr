#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_fundamental.hpp>

namespace BR {
namespace TypeOperate{

namespace Detail {

template< typename T >
using IsCompound = BooleanNot< IsFundamental< T > >;

} // namespace Detail

template< typename T >
using IsCompound = Boolean< Detail::IsCompound< T > >;

template< typename T >
using NotCompound = BooleanNot< Detail::IsCompound< T > >;

} // namespace TypeOperate
} // namespace BR



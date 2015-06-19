#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_fundamental.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
using IsCompound = BooleanNot< IsFundamental< T > >;

} // namespace TypeOperate
} // namespace Detail

template< typename T >
using IsCompound = Boolean< Detail::TypeOperate::IsCompound< T > >;

template< typename T >
using NotCompound = BooleanNot< Detail::TypeOperate::IsCompound< T > >;

} // namespace BR



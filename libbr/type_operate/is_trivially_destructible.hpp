#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_destructible.hpp>
#include <libbr/type_operate/has_trivial_destructor.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
using IsTriviallyDestructible = BooleanAnd< IsDestructible< T >, HasTrivialDestructor< T > >;

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsTriviallyDestructible : Boolean< Detail::TypeOperate::IsTriviallyDestructible< T > > {};

template< typename T >
struct NotTriviallyDestructible : BooleanNot< Detail::TypeOperate::IsTriviallyDestructible< T > > {};

} // namespace BR

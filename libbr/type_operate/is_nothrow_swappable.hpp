#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_swappable.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
using IsNothrowSwappableBasic = BooleanConstant< noexcept(swap(make_reference<T &>(), make_reference<T &>())) >;

template< typename T >
using IsNothrowSwappable = BooleanAnd< IsSwappable<T>, IsNothrowSwappableBasic<T> >;

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsNothrowSwappable : Boolean< Detail::TypeOperate::IsNothrowSwappable< T > > {};

template< typename T >
struct NotNothrowSwappable : BooleanNot< Detail::TypeOperate::IsNothrowSwappable< T > > {};

} // namespace BR


#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_swappable.hpp>
#include <libbr/utility/make_value.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
struct IsNothrowSwappableBasic {
	constexpr static auto value = noexcept(swap(make_reference<T>(), make_reference<T>()));
};

template< typename T >
using IsNothrowSwappable = BooleanAnd<
	IsSwappable<T>,
	BooleanConstant< IsNothrowSwappableBasic<T>::value >
>;

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsNothrowSwappable : Boolean< Detail::TypeOperate::IsNothrowSwappable<T> > {};

template< typename T >
struct NotNothrowSwappable : BooleanNot< Detail::TypeOperate::IsNothrowSwappable<T> > {};

} // namespace BR


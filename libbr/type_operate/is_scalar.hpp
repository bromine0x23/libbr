#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_arithmetic.hpp>
#include <libbr/type_operate/is_enum.hpp>
#include <libbr/type_operate/is_pointer.hpp>
#include <libbr/type_operate/is_member_pointer.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
using IsScalar = BooleanOr<
	IsArithmetic<T>,
	IsEnum<T>,
	IsPointer<T>,
	IsMemberPointer<T>
>;

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsScalar : Boolean< Detail::TypeOperate::IsScalar< T > > {};

template< typename T >
struct NotScalar : BooleanNot< Detail::TypeOperate::IsScalar< T > > {};

} // namespace BR
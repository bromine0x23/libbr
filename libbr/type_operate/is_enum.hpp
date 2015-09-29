#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>
#if !defined(BR_IS_ENUM)
#  include <libbr/type_operate/add_lvalue_reference.hpp>
#  include <libbr/type_operate/is_arithmetic.hpp>
#  include <libbr/type_operate/is_array.hpp>
#  include <libbr/type_operate/is_class.hpp>
#  include <libbr/type_operate/is_convertible.hpp>
#  include <libbr/type_operate/is_reference.hpp>
#  include <libbr/type_operate/is_union.hpp>
#  include <libbr/type_operate/is_void.hpp>
#endif

namespace BR {

#if defined(BR_IS_ENUM)

namespace Detail {
namespace TypeOperate {

template< typename T >
using IsEnum = BooleanConstant< BR_IS_ENUM(T) >;

} // namespace TypeOperate
} // namespace Detail

#else

namespace Detail {
namespace TypeOperate {

struct IntConvertible {
	IntConvertible(int);
};

template< typename T >
using IsEnum = BooleanAnd<
	NotVoid<T>,
	NotArithmetic<T>,
	NotReference<T>,
	NotClass<T>,
	NotUnion<T>,
	NotArray<T>,
	IsConvertible<
		AddLValueReference<T>,
		IntConvertible
	>
>;

} // namespace TypeOperate
} // namespace Detail

#endif // defined(BR_IS_ENUM)

template< typename T >
struct IsEnum : Boolean< Detail::TypeOperate::IsEnum< RemoveConstVolatile< T > > > {};

template< typename T >
struct NotEnum : BooleanNot< Detail::TypeOperate::IsEnum< RemoveConstVolatile< T > > > {};

} // namespace BR

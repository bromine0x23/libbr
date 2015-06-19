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
#endif

namespace BR {

namespace Detail {
namespace TypeOperate {

#if defined(BR_IS_ENUM)

template< typename T >
using IsEnum = BooleanConstant< BR_IS_ENUM(T) >;

#else

struct IntConvertible {
	IntConvertible(int);
};

template< typename T >
using IsEnum = BooleanAnd<
	NotVoid< T >,
	NotArithmetic< T >,
	NotReference< T >,
	NotClass< T >,
	NotUnion< T >,
	NotArray< T >,
	IsConvertible< AddLValueReference< T >, IntConvertible >
>;

#endif // !BR_IS_ENUM

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsEnum : Boolean< Detail::TypeOperate::IsEnum< RemoveConstVolatile< T > > > {};

template< typename T >
struct NotEnum : BooleanNot< Detail::TypeOperate::IsEnum< RemoveConstVolatile< T > > > {};

} // namespace BR

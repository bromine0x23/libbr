#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#if !defined(BR_TYPE_OPERATE_IS_EMPTY)
#  include <libbr/type_operate/is_class.hpp>
#  include <libbr/type_operate/remove_const_volatile.hpp>
#endif // !BR_TYPE_OPERATE_IS_EMPTY

namespace BR {
namespace TypeOperate {

namespace Detail {

#if defined(BR_TYPE_OPERATE_IS_EMPTY)

template< typename T >
using IsEmpty = BooleanConstant< BR_TYPE_OPERATE_IS_EMPTY(T) >;

#else

template< typename T >
struct IsEmptyHelper0 : public T {
	IsEmptyHelper0();
	int i[0x100];
};

struct IsEmptyHelper1 {
	int i[0x100];
};

template< typename T >
using IsEmptyBasic = BooleanConstant< sizeof(IsEmptyHelper0< T >) == sizeof(IsEmptyHelper1) >;

template< typename T >
using IsEmpty = BooleanAnd< IsClass< T >, IsEmptyBasic< RemoveConstVolatile< T > > >;

#endif // !BR_TYPE_OPERATE_IS_EMPTY

} // namespace Detail

template< typename T >
struct IsEmpty : Boolean< Detail::IsEmpty< T > > {};

template< typename T >
struct NotEmpty : BooleanNot< Detail::IsEmpty< T > > {};

} // namespace TypeOperate
} // namespace BR
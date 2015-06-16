#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>
#if !defined(BR_TYPE_OPERATE_IS_BASE_OF)
#  include <libbr/type_operate/is_class.hpp>
#  include <libbr/type_operate/is_lvalue_reference.hpp>
#  include <libbr/type_operate/is_same.hpp>
#endif // !BR_TYPE_OPERATE_IS_BASE_OF

namespace BR {
namespace TypeOperate {

namespace Detail {

#if defined(BR_TYPE_OPERATE_IS_BASE_OF)

template< typename TBase, typename TDerived >
using IsBaseOf = BooleanConstant < BR_TYPE_OPERATE_IS_BASE_OF(RemoveConstVolatile< TBase >, RemoveConstVolatile< TDerived >) >;

#else

template< typename TBase, typename TDerived >
struct IsBaseOfTester {
	template< typename T >
	static BooleanTrue test(TDerived const volatile *, T);

	static BooleanFalse test(TBase const volatile *, int);
};

template< typename TBase, typename TDerived >
struct IsBaseOfHelper {
	operator TBase    const volatile *() const;
	operator TDerived const volatile *();
};

template< typename TBase, typename TDerived >
struct IsBaseOfBasic : BooleanAnd<
	IsClass< TBase >,
	IsClass< TDerived >,
	NotSame< TBase, TDerived >,
	decltype(IsBaseOfTester< TBase, TDerived >::test(IsBaseOfHelper< TBase, TDerived >(), 0))
> {
	static_assert(sizeof(TBase   ) != 0, "Base must be complete."   );
	static_assert(sizeof(TDerived) != 0, "Derived must be complete.");
};

template< typename TBase, typename TDerived >
using IsBaseOf = BooleanAnd<
	NotLValueReference< TBase >,
	NotLValueReference< TDerived >,
	IsBaseOfBasic< RemoveConstVolatile< TBase >, RemoveConstVolatile< TDerived > >
 >;

#endif // BR_TYPE_OPERATE_IS_BASE_OF

} // namespace Detail

template< typename TBase, typename TDerived >
struct IsBaseOf : Boolean< Detail::IsBaseOf< TBase, TDerived > > {};

template< typename TBase, typename TDerived >
struct NotBaseOf : BooleanNot< Detail::IsBaseOf< TBase, TDerived > > {};

} // namespace TypeOperate
} // namespace BR


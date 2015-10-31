/// \cond
/*
 * <libbr/type_operate/bool.hpp> should be included before.
 */
#if false
#include <libbr/config.hpp>
#include <libbr/type_traits/bool_constant.hpp>
#endif

#ifndef BR_TYPE_OPERATE_TYPE_NAME
#error "BR_TYPE_OPERATE_TYPE_NAME not defined!"
#endif

namespace BR_JOIN(MemberType, BR_TYPE_OPERATE_TYPE_NAME) {

using BR::BooleanTrue;
using BR::BooleanFalse;

struct HasMemberTypeTest {
	template < typename T >
	static auto test(typename T::BR_TYPE_OPERATE_TYPE_NAME * = nullptr) -> BR::BooleanTrue;

	template < typename T >
	static auto test(...) -> BR::BooleanFalse;
};

template < typename T >
using HasMemberType = decltype(HasMemberTypeTest::test<T>(nullptr));

} // namespace BR_JOIN(MemberType, BR_TYPE_OPERATE_TYPE_NAME)

template< typename T >
struct BR_JOIN(HasMemberType, BR_TYPE_OPERATE_TYPE_NAME) : BR::BooleanRewrapPositive<
	BR_JOIN(MemberType, BR_TYPE_OPERATE_TYPE_NAME)::HasMemberType<T>
> {};

template< typename T >
struct BR_JOIN(NoMemberType, BR_TYPE_OPERATE_TYPE_NAME) : BR::BooleanRewrapNegative<
	BR_JOIN(MemberType, BR_TYPE_OPERATE_TYPE_NAME)::HasMemberType<T>
> {};

#undef BR_TYPE_OPERATE_TYPE_NAME
/// \endcond
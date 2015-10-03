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

struct HasMemberTypeTest {
	template < typename T >
	static BR::BooleanTrue test(typename T::BR_TYPE_OPERATE_TYPE_NAME * = nullptr);

	template < typename T >
	static BR::BooleanFalse test(...);
};

template < typename T >
using HasMemberType = decltype(HasMemberTypeTest::test< T >(0));

} // namespace BR_JOIN(MemberType, BR_TYPE_OPERATE_TYPE_NAME)

template< typename T >
struct BR_JOIN(HasMemberType, BR_TYPE_OPERATE_TYPE_NAME) : BR::Boolean<
	BR_JOIN(MemberType, BR_TYPE_OPERATE_TYPE_NAME)::HasMemberType<T>
> {};

template< typename T >
struct BR_JOIN(NoMemberType, BR_TYPE_OPERATE_TYPE_NAME) : BR::BooleanNot<
	BR_JOIN(MemberType, BR_TYPE_OPERATE_TYPE_NAME)::HasMemberType<T>
> {};

#undef BR_TYPE_OPERATE_TYPE_NAME
/// \endcond
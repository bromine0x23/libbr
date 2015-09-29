/// \cond
/*
 * <libbr/type_operate/bool.hpp> should be included before.
 */
#ifndef BR_TYPE_OPERATE_TYPE_NAME
#error "BR_TYPE_OPERATE_TYPE_NAME not defined!"
#endif

#define BR_TYPE_OPERATE_NAMESPACE BR_JOIN(MemberType, BR_TYPE_OPERATE_TYPE_NAME)

namespace BR_TYPE_OPERATE_NAMESPACE {

struct HasMemberTypeTest {
	template < typename T >
	static ::BR::BooleanTrue test(typename T::BR_TYPE_OPERATE_TYPE_NAME * = nullptr);

	template < typename T >
	static ::BR::BooleanFalse test(...);
};

template < typename T >
using HasMemberType = decltype(HasMemberTypeTest::test< T >(0));

} // namespace BR_TYPE_OPERATE_NAMESPACE

template< typename T >
struct BR_JOIN(HasMemberType, BR_TYPE_OPERATE_TYPE_NAME) : ::BR::Boolean<
	BR_TYPE_OPERATE_NAMESPACE::HasMemberType< T >
> {};

template< typename T >
struct BR_JOIN(NoMemberType, BR_TYPE_OPERATE_TYPE_NAME) : ::BR::BooleanNot<
	BR_TYPE_OPERATE_NAMESPACE::HasMemberType< T >
> {};

#undef BR_TYPE_OPERATE_NAMESPACE
#undef BR_TYPE_OPERATE_TYPE_NAME
/// \endcond
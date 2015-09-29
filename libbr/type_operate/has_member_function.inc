/// \cond
/*
 * <libbr/type_operate/bool.hpp> and <libbr/utility/make_value.hpp> should be included before.
 */
#ifndef BR_TYPE_OPERATE_FUNCTION_NAME
#error "BR_TYPE_OPERATE_FUNCTION_NAME not defined!"
#endif

#define BR_TYPE_OPERATE_NAMESPACE BR_JOIN(MemberFunction_, BR_TYPE_OPERATE_FUNCTION_NAME)

namespace BR_TYPE_OPERATE_NAMESPACE {

using ::BR::make_rvalue;
using ::BR::BooleanTrue;
using ::BR::BooleanFalse;

struct HasMemberFunctionTest {
	template < typename T, typename ... TArguments >
	static auto test(int) -> decltype(make_rvalue< T >().BR_TYPE_OPERATE_FUNCTION_NAME(make_rvalue< TArguments >() ...), BooleanTrue());

	template < typename T, typename ... TArguments >
	static auto test(...) -> BooleanFalse;
};

template < typename T, typename ... TArguments >
using HasMemberFunction = decltype(HasMemberFunctionTest::test< T, TArguments ... >(0));

} // namespace BR_TYPE_OPERATE_NAMESPACE

template< typename T, typename ... TArguments >
struct BR_JOIN(HasMemberFunction_, BR_TYPE_OPERATE_FUNCTION_NAME) : ::BR::Boolean<
	BR_TYPE_OPERATE_NAMESPACE::HasMemberFunction< T, TArguments ... >
> {};

template< typename T, typename ... TArguments >
struct BR_JOIN(NoMemberFunction_, BR_TYPE_OPERATE_FUNCTION_NAME) : ::BR::BooleanNot<
	BR_TYPE_OPERATE_NAMESPACE::HasMemberFunction< T, TArguments ... >
> {};

#undef BR_TYPE_OPERATE_NAMESPACE
#undef BR_TYPE_OPERATE_FUNCTION_NAME
/// \endcond

/// \cond
/*
 * <libbr/type_traits/bool_constant.hpp> and <libbr/utility/make_value.hpp> should be included before.
 */
#if false
#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/make_value.hpp>
#endif

#ifndef BR_TYPE_OPERATE_FUNCTION_NAME
#error "BR_TYPE_OPERATE_FUNCTION_NAME not defined!"
#endif

namespace BR_JOIN(MemberFunction_, BR_TYPE_OPERATE_FUNCTION_NAME) {

using BR::make_rvalue;
using BR::BooleanTrue;
using BR::BooleanFalse;

struct HasMemberFunctionTest {
	template< typename T, typename... TArgs >
	static auto test(int) -> decltype(make_rvalue<T>().BR_TYPE_OPERATE_FUNCTION_NAME(make_rvalue<TArgs>() ...), BooleanTrue());

	template< typename T, typename... TArgs >
	static auto test(...) -> BooleanFalse;
};

template< typename T, typename... TArgs >
using HasMemberFunction = decltype(HasMemberFunctionTest::test< T, TArgs... >(0));

} // namespace BR_JOIN(MemberFunction_, BR_TYPE_OPERATE_FUNCTION_NAME)

template< typename T, typename... TArgs >
struct BR_JOIN(HasMemberFunction_, BR_TYPE_OPERATE_FUNCTION_NAME) : BR::BooleanRewrapPositive<
	BR_JOIN(MemberFunction_, BR_TYPE_OPERATE_FUNCTION_NAME)::HasMemberFunction< T, TArgs... >
> {};

template< typename T, typename... TArgs >
struct BR_JOIN(NoMemberFunction_, BR_TYPE_OPERATE_FUNCTION_NAME) : BR::BooleanRewrapNegative<
	BR_JOIN(MemberFunction_, BR_TYPE_OPERATE_FUNCTION_NAME)::HasMemberFunction< T, TArgs... >
> {};

#undef BR_TYPE_OPERATE_FUNCTION_NAME
/// \endcond

/**
 * @file
 * @brief BR_HAS_MEMBER_FUNCTION
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/make_value.hpp>

#define BR_HAS_MEMBER_FUNCTION(FUNCTION_NAME)                                                                                         \
namespace Detail {                                                                                                                    \
namespace BR_JOIN(MemberFunction, FUNCTION_NAME) {                                                                                    \
	struct HasMemberFunctionTest {                                                                                                    \
		template< typename T, typename... TArgs >                                                                                     \
		static auto test(int) -> decltype(::BR::make_rvalue<T>().FUNCTION_NAME(::BR::make_rvalue<TArgs>() ...), ::BR::BooleanTrue{}); \
		template< typename T, typename... TArgs >                                                                                     \
		static auto test(...) -> ::BR::BooleanFalse;                                                                                  \
	};                                                                                                                                \
	template< typename T, typename... TArgs >                                                                                         \
	using HasMemberFunction = decltype(HasMemberFunctionTest::test< T, TArgs... >(0));                                                \
} /* namespace BR_JOIN(MemberFunction, FUNCTION_NAME) */                                                                              \
} /* namespace Detail */                                                                                                              \
template< typename T, typename... TArgs >                                                                                             \
struct BR_JOIN(HasMemberFunction_, FUNCTION_NAME) : ::BR::BooleanRewrapPositive<                                                      \
	Detail::BR_JOIN(MemberFunction, FUNCTION_NAME)::HasMemberFunction<T>                                                              \
> {};                                                                                                                                 \
template< typename T, typename... TArgs >                                                                                             \
struct BR_JOIN(NoMemberFunction_, FUNCTION_NAME) : ::BR::BooleanRewrapNegative<                                                       \
	Detail::BR_JOIN(MemberFunction, FUNCTION_NAME)::HasMemberFunction<T>                                                              \
> {};
/* BR_HAS_MEMBER_FUNCTION */

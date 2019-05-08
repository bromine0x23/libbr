/**
 * @file
 * @brief BR_HAS_MEMBER_FUNCTION
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/declare_value.hpp>

#define BR_HAS_MEMBER_FUNCTION(FUNCTION_NAME)                                                                                            \
namespace BR_JOIN(_MemberFunction_, FUNCTION_NAME) {                                                                                     \
    struct HasMemberFunctionTest {                                                                                                       \
        template< typename T, typename... TArgs >                                                                                        \
        static auto test(int) -> decltype(BR::declare_value<T>().FUNCTION_NAME(BR::declare_value<TArgs>()...), BR::BooleanTrue{});       \
        template< typename T, typename... TArgs >                                                                                        \
        static auto test(...) -> BR::BooleanFalse;                                                                                       \
    };                                                                                                                                   \
    template< typename T, typename... TArgs >                                                                                            \
    using HasMemberFunction = decltype(HasMemberFunctionTest::test< T, TArgs... >(0));                                                   \
} /* namespace BR_JOIN(MemberFunction_, FUNCTION_NAME) */                                                                                \
template< typename T, typename... TArgs >                                                                                                \
struct BR_JOIN(HasMemberFunction_, FUNCTION_NAME) : public BR::BooleanRewrapPositive<                                                    \
    BR_JOIN(_MemberFunction_, FUNCTION_NAME)::HasMemberFunction<T, TArgs...>                                                             \
> {};                                                                                                                                    \
template< typename T, typename... TArgs >                                                                                                \
struct BR_JOIN( NoMemberFunction_, FUNCTION_NAME) : public BR::BooleanRewrapNegative<                                                    \
    BR_JOIN(_MemberFunction_, FUNCTION_NAME)::HasMemberFunction<T, TArgs...>                                                             \
> {};                                                                                                                                    \
template< typename T, typename... TArgs >                                                                                                \
constexpr auto BR_JOIN(has_member_function_, FUNCTION_NAME) = boolean_constant<BR_JOIN(HasMemberFunction_, FUNCTION_NAME)<T, TArgs...>>; \
template< typename T, typename... TArgs >                                                                                                \
constexpr auto BR_JOIN( no_member_function_, FUNCTION_NAME) = boolean_constant<BR_JOIN( NoMemberFunction_, FUNCTION_NAME)<T, TArgs...>>; \
/* BR_HAS_MEMBER_FUNCTION */

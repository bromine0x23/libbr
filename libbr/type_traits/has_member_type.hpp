/**
 * @file
 * @brief BR_HAS_MEMBER_TYPE
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/type_wrapper.hpp>

#define BR_HAS_MEMBER_TYPE(TYPE_NAME)                                                                         \
namespace BR_JOIN(_MemberType, TYPE_NAME) {                                                                   \
    template< typename... >                                                                                   \
    struct Void : public TypeWrapper<void> {};                                                                \
    template< typename, typename = void >                                                                     \
    struct HasMemberType : BR::BooleanFalse {};                                                               \
    template< typename T >                                                                                    \
    struct HasMemberType< T, TypeUnwrap< Void< typename T::TYPE_NAME > > > : BR::BooleanTrue {};              \
} /* namespace BR_JOIN(_MemberType, TYPE_NAME) */                                                             \
template< typename T >                                                                                        \
struct BR_JOIN(HasMemberType, TYPE_NAME) : BR::BooleanRewrapPositive<                                         \
    BR_JOIN(_MemberType, TYPE_NAME)::HasMemberType<T>                                                         \
> {};                                                                                                         \
template< typename T >                                                                                        \
struct BR_JOIN(NoMemberType, TYPE_NAME) : BR::BooleanRewrapNegative<                                          \
    BR_JOIN(_MemberType, TYPE_NAME)::HasMemberType<T>                                                         \
> {};                                                                                                         \
template< typename T >                                                                                        \
constexpr auto BR_JOIN(has_member_type_, TYPE_NAME) = boolean_constant<BR_JOIN(HasMemberType, TYPE_NAME)<T>>; \
template< typename T >                                                                                        \
constexpr auto BR_JOIN( no_member_type_, TYPE_NAME) = boolean_constant<BR_JOIN( NoMemberType, TYPE_NAME)<T>>; \
/* BR_HAS_MEMBER_TYPE */

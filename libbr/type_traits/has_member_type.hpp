/**
 * @file
 * @brief BR_HAS_MEMBER_TYPE
 * @author Bromine0x23
 * @since 2016/10/10
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/dummy.hpp>

#define BR_HAS_MEMBER_TYPE(TYPE_NAME)                                                       \
namespace Detail {                                                                          \
namespace BR_JOIN(MemberType, TYPE_NAME) {                                                  \
	template< typename, typename = BR::Dummy<> >                                            \
	struct HasMemberType : BR::BooleanFalse {};                                             \
	template< typename T >                                                                  \
	struct HasMemberType< T, BR::Dummy< typename T::TYPE_NAME > > : BR::BooleanTrue {};     \
} /* namespace BR_JOIN(MemberType, TYPE_NAME) */                                            \
} /* namespace Detail */                                                                    \
template< typename T >                                                                      \
struct BR_JOIN(HasMemberType, TYPE_NAME) : ::BR::BooleanRewrapPositive<                     \
	Detail::BR_JOIN(MemberType, TYPE_NAME)::HasMemberType<T>                                \
> {};                                                                                       \
template< typename T >                                                                      \
struct BR_JOIN(NoMemberType, TYPE_NAME) : ::BR::BooleanRewrapNegative<                      \
	Detail::BR_JOIN(MemberType, TYPE_NAME)::HasMemberType<T>                                \
> {};
/* BR_HAS_MEMBER_TYPE */

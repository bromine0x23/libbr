/**
 * @file
 * @brief MemberPointerTraits
 * @author Bromine0x23
 * @since 2015/10/31
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_traits/is_member_pointer.hpp>
#include <libbr/type_traits/is_member_function_pointer.hpp>
#include <libbr/type_traits/is_member_object_pointer.hpp>

namespace BR {

template< typename T >
struct MemberPointerTraits;

template< typename T >
struct MemberPointerTraits< T const > : public MemberPointerTraits<T> {
};

template< typename T >
struct MemberPointerTraits< T volatile > : public MemberPointerTraits<T> {
};

template< typename T >
struct MemberPointerTraits< T const volatile > : public MemberPointerTraits<T> {
};

namespace Detail {
namespace TypeTraits {

template< typename T, bool is_member_pointer = IsMemberPointer<T>::value >
struct MemberPointerTraits;

template< typename T >
struct MemberPointerTraits< T, false > {
};

template< typename TMember, typename TClass >
struct MemberPointerTraits< TMember TClass::*, true > {
	using MemberPointer = TMember TClass::*;
	using Class = TClass;
	using Member = TMember;
	using IsObjectPointer = IsMemberObjectPointer< MemberPointer >;
	using IsFunctionPointer = IsMemberFunctionPointer< MemberPointer >;
};

} // namespace TypeTraits
} // namespace Detail

template< typename T >
struct MemberPointerTraits : public Detail::TypeTraits::MemberPointerTraits<T> {
};

} // namespace BR
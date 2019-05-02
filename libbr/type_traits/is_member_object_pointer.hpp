/**
 * @file
 * @brief 成员变量指针检查
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/is_member_pointer.hpp>
#include <libbr/type_traits/is_member_function_pointer.hpp>
#include <libbr/utility/abjunction.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否是成员函数指针
 * @tparam T 待检查类型
 * @see Utility::IntegralConstant
 * @see NotMemberObjectPointer
 *
 * 如果 \em T 是指向非静态成员变量的指针类型，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsMemberObjectPointer;

/**
 * @brief IsMemberObjectPointer 的否定
 * @tparam T 待检查类型
 * @see IsMemberObjectPointer
 */
template< typename T >
struct NotMemberObjectPointer;

/**
 * @brief IsMemberObjectPointer 的模板变量版本
 * @tparam T 待检查类型
 * @see IsMemberObjectPointer
 * @see not_member_object_pointer
 */
template< typename T >
constexpr auto is_member_object_pointer = boolean_constant< IsMemberObjectPointer<T> >;

/**
 * @brief NotMemberObjectPointer 的模板变量版本
 * @tparam T 待检查类型
 * @see NotMemberObjectPointer
 * @see is_member_object_pointer
 */
template< typename T >
constexpr auto not_member_object_pointer = boolean_constant< NotMemberObjectPointer<T> >;

} // namespace TypeTraits



namespace _ {
namespace TypeTraits {

template< typename T >
struct IsMemberObjectPointer : public Abjunction< IsMemberPointer<T>, IsMemberFunctionPointer<T> > {};

} // namespace TypeTraits
} // namespace _

inline namespace TypeTraits {

template< typename T >
struct IsMemberObjectPointer : public BooleanRewrapPositive< _::TypeTraits::IsMemberObjectPointer<T> > {};

template< typename T >
struct NotMemberObjectPointer : public BooleanRewrapNegative< _::TypeTraits::IsMemberObjectPointer<T> > {};

} // namespace TypeTraits

} // namespace BR

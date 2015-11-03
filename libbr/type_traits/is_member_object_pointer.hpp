/**
 * @file
 * @brief 成员变量指针检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_traits/is_member_pointer.hpp>
#include <libbr/type_traits/is_member_function_pointer.hpp>

namespace BR {

/**
 * @brief 检查 \em T 是否是成员函数指针
 * @tparam T 待检查类型
 * @see IntegerConstant
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
using NotMemberObjectPointer = BooleanNot< IsMemberObjectPointer<T> >;

#if defined(BR_CXX14)

/**
 * @brief IsMemberObjectPointer 的模板变量版本
 * @tparam T 待检查类型
 * @see IsMemberObjectPointer
 * @see not_member_object_pointer
 */
template< typename T >
constexpr auto is_member_object_pointer = IsMemberObjectPointer<T>::value;

/**
 * @brief NotMemberObjectPointer 的模板变量版本
 * @tparam T 待检查类型
 * @see NotMemberObjectPointer
 * @see is_member_object_pointer
 */
template< typename T >
constexpr auto not_member_object_pointer = NotMemberObjectPointer<T>::value;

#endif // defined(BR_CXX14)

namespace Detail {
namespace TypeTraits {

template< typename T >
struct IsMemberObjectPointer : public BooleanAnd< IsMemberPointer<T>, NotMemberFunctionPointer<T> > {
};

} // namespace TypeTraits
} // namespace Detail

template< typename T >
struct IsMemberObjectPointer : public BooleanRewrap< Detail::TypeTraits::IsMemberObjectPointer<T> > {
};


} // namespace BR

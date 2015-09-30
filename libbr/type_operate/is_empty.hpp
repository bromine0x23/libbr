/**
 * @file
 * @brief 空类型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#if !defined(BR_IS_EMPTY)
#  include <libbr/type_operate/is_class.hpp>
#  include <libbr/type_operate/remove_const_volatile.hpp>
#endif // !BR_IS_EMPTY

namespace BR {

namespace Detail {
namespace TypeOperate {

#if defined(BR_IS_EMPTY)

template< typename T >
using IsEmpty = BooleanConstant< BR_IS_EMPTY(T) >;

#else

using RemoveConstVolatile;

template< typename T >
struct IsEmptyHelper0 : public T {
	IsEmptyHelper0();
	int i[0x100];
};

struct IsEmptyHelper1 {
	int i[0x100];
};

template< typename T >
using IsEmptyBasic = BooleanConstant< sizeof(IsEmptyHelper0<T>) == sizeof(IsEmptyHelper1) >;

template< typename T >
using IsEmpty = BooleanAnd< IsClass<T>, IsEmptyBasic< RemoveConstVolatile<T> > >;

#endif // !BR_IS_EMPTY

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 检查 \em T 是否是空类型
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotEmpty
 *
 * 如果 \em T 是空类型(除静态成员外的字段位宽为0、无虚函数、无虚基类、无非空基类)，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsEmpty : Boolean< Detail::TypeOperate::IsEmpty<T> > {};

/**
 * @brief IsEmpty 的否定
 * @tparam T 待检查类型
 * @see IsEmpty
 */
template< typename T >
struct NotEmpty : BooleanNot< Detail::TypeOperate::IsEmpty<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsEmpty 的模板变量版本
 * @tparam T 待检查类型
 * @see IsEmpty
 * @see not_empty
 */
template< typename T >
constexpr auto is_empty = IsEmpty<T>::value;

/**
 * @brief NotEmpty 的模板变量版本
 * @tparam T 待检查类型
 * @see NotEmpty
 * @see is_empty
 */
template< typename T >
constexpr auto not_empty = NotEmpty<T>::value;

#endif // defined(BR_CXX14)

} // namespace BR
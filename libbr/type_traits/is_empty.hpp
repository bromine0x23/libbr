/**
 * @file
 * @brief 空类型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#if !defined(BR_IS_EMPTY)
#  include <libbr/type_traits/boolean.hpp>
#  include <libbr/type_traits/is_class.hpp>
#  include <libbr/type_traits/remove_const_volatile.hpp>
#endif // !BR_IS_EMPTY

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否是空类型
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see BR_IS_EMPTY
 * @see IsClass
 * @see NotEmpty
 *
 * 如果 \em T 是空的(除静态成员外的字段位宽为0、无虚函数、无虚基类、无非空基类)类类型，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsEmpty;

/**
 * @brief IsEmpty 的否定
 * @tparam T 待检查类型
 * @see IsEmpty
 */
template< typename T >
struct NotEmpty;

#if defined(BR_AFTER_CXX11)

/**
 * @brief IsEmpty 的模板变量版本
 * @tparam T 待检查类型
 * @see IsEmpty
 * @see not_empty
 */
template< typename T >
constexpr auto is_empty = boolean_constant< IsEmpty<T> >;

/**
 * @brief NotEmpty 的模板变量版本
 * @tparam T 待检查类型
 * @see NotEmpty
 * @see is_empty
 */
template< typename T >
constexpr auto not_empty = boolean_constant< NotEmpty<T> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

#if defined(BR_IS_EMPTY)

template< typename T >
using IsEmpty = BooleanConstant< BR_IS_EMPTY(T) >;

#else

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
struct IsEmpty : public BooleanAnd< IsClass<T>, IsEmptyBasic< RemoveConstVolatile<T> > > {};

#endif // !BR_IS_EMPTY

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct IsEmpty : public BooleanRewrapPositive< Detail::TypeTraits::IsEmpty<T> > {};

template< typename T >
struct NotEmpty : public BooleanRewrapNegative< Detail::TypeTraits::IsEmpty<T> > {};

} // namespace TypeTraits

} // namespace BR
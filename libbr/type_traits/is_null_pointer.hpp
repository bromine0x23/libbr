/**
 * @file
 * @brief 空指针类型检查
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/remove_const_volatile.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否是空指针类型
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotNullPointer
 *
 * 如果 \em T 是空指针类型(\em nullptr 的类型)，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsNullPointer;

/**
 * @brief IsNullPointer 的否定
 * @tparam T 待检查类型
 * @see IsNullPointer
 */
template< typename T >
struct NotNullPointer;

#if defined(BR_AFTER_CXX11)

/**
 * @brief IsNullPointer 的模板变量版本
 * @tparam T 待检查类型
 * @see IsNullPointer
 * @see not_null_pointer
 */
template< typename T >
constexpr auto is_null_pointer = boolean_constant< IsNullPointer<T> >;

/**
 * @brief NotNullPointer 的模板变量版本
 * @tparam T 待检查类型
 * @see NotNullPointer
 * @see is_null_pointer
 */
template< typename T >
constexpr auto not_null_pointer = boolean_constant< NotNullPointer<T> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< typename T >
struct IsNullPointerBasic : public BooleanFalse {};

template<>
struct IsNullPointerBasic<NullPointer> : public BooleanTrue {};

template< typename T >
using IsNullPointer = IsNullPointerBasic< RemoveConstVolatile<T> >;

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct IsNullPointer : public BooleanRewrapPositive< Detail::TypeTraits::IsNullPointer<T> > {};

template< typename T >
struct NotNullPointer: public BooleanRewrapNegative< Detail::TypeTraits::IsNullPointer<T> > {};

} // namespace TypeTraits

} // namespace BR

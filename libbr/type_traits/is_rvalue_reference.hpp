/**
 * @file
 * @brief 右值引用类型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否是右值引用类型
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see IsLValueReference
 * @see NotRValueReference
 *
 * 如果 \em T 是右值引用类型，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsRValueReference;

/**
 * @brief IsRValueReference 的否定
 * @tparam T 待检查类型
 * @see IsRValueReference
 */
template< typename T >
struct NotRValueReference;

#if defined(BR_AFTER_CXX11)

/**
 * @brief IsRValueReference 的模板变量版本
 * @tparam T 待检查类型
 * @see IsRValueReference
 * @see not_rvalue_reference
 */
template< typename T >
constexpr auto is_rvalue_reference = boolean_constant< IsRValueReference<T> >;

/**
 * @brief NotRValueReference 的模板变量版本
 * @tparam T 待检查类型
 * @see NotRValueReference
 * @see is_rvalue_reference
 */
template< typename T >
constexpr auto not_rvalue_reference = boolean_constant< NotRValueReference<T> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< typename T >
struct IsRValueReference : public BooleanFalse {};

template< typename T >
struct IsRValueReference< T && > : public BooleanTrue {};

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct IsRValueReference : public BooleanRewrapPositive< Detail::TypeTraits::IsRValueReference<T> > {};

template< typename T >
struct NotRValueReference : public BooleanRewrapNegative< Detail::TypeTraits::IsRValueReference<T> > {};

} // namespace TypeTraits

} // namespace BR
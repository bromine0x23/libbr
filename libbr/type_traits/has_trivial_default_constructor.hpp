/**
 * @file
 * @brief 检查类型是否具有平凡的默认构造函数
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/is_trivially_constructible.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否具有平凡的默认构造函数
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see IsTriviallyConstructible
 * @see HasDefaultConstructor
 * @see NoTrivialDefaultConstructor
 *
 * 如果 \em T 具有平凡的默认构造函数，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasTrivialDefaultConstructor;

/**
 * @brief HasTrivialDefaultConstructor 的否定
 * @tparam T 待检查类型
 * @see HasTrivialDefaultConstructor
 */
template< typename T >
struct NoTrivialDefaultConstructor;

#if defined(BR_AFTER_CXX11)

/**
 * @brief HasTrivialDefaultConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see HasTrivialDefaultConstructor
 * @see no_trivial_default_constructor
 */
template< typename T >
constexpr auto has_trivial_default_constructor = boolean_constant< HasTrivialDefaultConstructor<T> >;

/**
 * @brief NoTrivialDefaultConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see NoTrivialDefaultConstructor
 * @see has_trivial_default_constructor
 */
template< typename T >
constexpr auto no_trivial_default_constructor = boolean_constant< NoTrivialDefaultConstructor<T> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< typename T >
using HasTrivialDefaultConstructor = IsTriviallyConstructible<T>;

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct HasTrivialDefaultConstructor : public BooleanRewrapPositive< Detail::TypeTraits::HasTrivialDefaultConstructor<T> > {};

template< typename T >
struct NoTrivialDefaultConstructor : public BooleanRewrapNegative< Detail::TypeTraits::HasTrivialDefaultConstructor<T> > {};

} // namespace TypeTraits

} // namespace BR
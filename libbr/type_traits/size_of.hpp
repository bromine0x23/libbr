/**
 * @file
 * @brief 获取类型的长度
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/integral_constant.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 获取类型的长度
 * @tparam T
 * @see IntegerConstant
 *
 * <tt>sizeof(T)</tt>
 */
template< typename T >
using SizeOf = IntegralConstant< Size, sizeof(T) >;

#if defined(BR_AFTER_CXX11)

/**
 * @brief SizeOf 的模板变量版本
 * @tparam T
 * @see SizeOf
 */
template< typename T >
constexpr auto size_of = integral_constant< SizeOf<T> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits

} // namespace BR
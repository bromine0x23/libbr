/**
 * @file
 * @brief 获取类型的对齐长度
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/integral_constant.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 获取类型的对齐长度
 * @tparam T
 * @see IntegerConstant
 *
 * <tt>alignof(T)</tt>
 */
template< typename T >
using AlignmentOf = IntegralConstant< Size, alignof(T) >;

#if defined(BR_AFTER_CXX11)

/**
 * @brief AlignmentOf 的模板变量版本
 * @tparam T
 * @see AlignmentOf
 */
template< typename T >
constexpr auto alignment_of = integral_constant< AlignmentOf<T> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits

} // namespace BR
/**
 * @file
 * @brief 获取类型的对齐长度
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/integral_constant.hpp>

namespace BR {

/**
 * @brief 获取类型的对齐长度
 * @tparam T
 * @see IntegerConstant
 *
 * <tt>alignof(T)</tt>
 */
template< typename T >
using AlignmentOf = IntegralConstant< Size, alignof(T) >;

#if defined(BR_CXX14)

/**
 * @brief AlignmentOf 的模板变量版本
 * @tparam T
 * @see AlignmentOf
 */
template< typename T >
constexpr auto alignment_of = integer_constant< AlignmentOf<T> >;

#endif // defined(BR_CXX14)

} // namespace BR
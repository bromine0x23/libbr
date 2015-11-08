/**
 * @file
 * @brief 获取类型的长度
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/integer_constant.hpp>

namespace BR {

/**
 * @brief 获取类型的长度
 * @tparam T
 * @see IntegerConstant
 *
 * <tt>sizeof(T)</tt>
 */
template< typename T >
using SizeOf = IntegerConstant< Size, sizeof(T) >;

#if defined(BR_CXX14)

/**
 * @brief SizeOf 的模板变量版本
 * @tparam T
 * @see SizeOf
 */
template< typename T >
constexpr auto size_of = integer_constant< SizeOf<T> >;

#endif // defined(BR_CXX14)

} // namespace BR
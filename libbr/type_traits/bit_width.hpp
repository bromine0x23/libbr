/**
 * @file
 * @brief BitWidth
 * @author Bromine0x23
 * @since 2015/6/23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/integral_constant.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief BitWidth
 * @tparam T
 * @see bit_width
 */
template< typename T >
using BitWidth = IntegerConstant< Size, sizeof(T) * BIT_PER_BYTE >;

#if defined(BR_AFTER_CXX11)

/**
 * @brief bit_with
 * @tparam T
 * @see BitWidth
 */
template< typename T >
constexpr auto bit_width = integral_constant< BitWidth<T> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits

} // namespace BR

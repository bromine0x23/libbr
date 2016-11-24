/**
 * @file
 * @brief log2
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/is_integral.hpp>

extern "C" {

/**
 * like std::log2
 * @param x
 * @return
 */
//@{
auto libbr_log2_32(BR::Float32 x) -> BR::Float32;

auto libbr_log2_64(BR::Float64 x) -> BR::Float64;
//@}

}

namespace BR {
inline namespace Math {
inline namespace Function {

inline auto log2(Float32 x) -> Float32 {
	return libbr_log2_32(x);
}

inline auto log2(Float64 x) -> Float64 {
	return libbr_log2_64(x);
}

#if defined(BR_GCC)
template< typename T >
constexpr auto log2(T x) -> EnableIf< IsIntegral<T>, T > {
	return __builtin_log2(x);
}
#else
template< typename T >
constexpr auto log2(T x) -> EnableIf< IsIntegral<T>, T > {
	return 0; // TODO
}
#endif

} // inline namespace Function
} // inline namespace Math
} // namespace BR
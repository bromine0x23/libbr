/**
 * @file
 * @brief log
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/is_integral.hpp>

extern "C" {

/**
 * like std::log
 * @param x
 * @return
 */
//@{
auto libbr_log_32(BR::Float32 x) -> BR::Float32;

auto libbr_log_64(BR::Float64 x) -> BR::Float64;
//@}

}

namespace BR {
inline namespace Math {
inline namespace Function {

inline auto log(Float32 x) -> Float32 {
	return libbr_log_32(x);
}

inline auto log(Float64 x) -> Float64 {
	return libbr_log_64(x);
}

template< typename T >
constexpr auto log(T x) -> EnableIf< IsIntegral<T>, T > {
	return 0; // TODO
}

} // inline namespace Function
} // inline namespace Math
} // namespace BR
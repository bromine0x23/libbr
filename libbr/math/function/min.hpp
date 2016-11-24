/**
 * @file
 * @brief min
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/function/is_less_equal.hpp>
#include <libbr/math/function/is_nan.hpp>

extern "C" {

/**
 * like std::fmin
 * @param x
 * @param y
 * @return
 */
//@{
inline auto libbr_min_32(BR::Float32 x, BR::Float32 y) -> BR::Float32 {
	return (libbr_is_less_equal_32(x, y) || libbr_is_nan_32(y)) ? x : y;
}

inline auto libbr_min_64(BR::Float64 x, BR::Float64 y) -> BR::Float64 {
	return (libbr_is_less_equal_64(x, y) || libbr_is_nan_64(y)) ? x : y;
}
//@}

}

namespace BR {
inline namespace Math {
inline namespace Function {

inline auto min(Float32 x, Float32 y) -> Float32 {
	return libbr_min_32(x, y);
}

inline auto min(Float64 x, Float64 y) -> Float64 {
	return libbr_min_64(x, y);
}

} // inline namespace Function
} // inline namespace Math
} // namespace BR
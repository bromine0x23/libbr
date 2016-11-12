/**
 * @file
 * @brief max
 * @author Bromine0x23
 * @since 2016/10/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/function/is_greater_equal.hpp>
#include <libbr/math/function/is_nan.hpp>

extern "C" {

/**
 * like std::fmax
 * @param x
 * @param y
 * @return
 */
//@{
inline auto libbr_max_32(BR::Float32 x, BR::Float32 y) -> BR::Float32 {
	return (libbr_is_greater_equal_32(x, y) || libbr_is_nan_32(y)) ? x : y;
}

inline auto libbr_max_64(BR::Float64 x, BR::Float64 y) -> BR::Float64 {
	return (libbr_is_greater_equal_64(x, y) || libbr_is_nan_64(y)) ? x : y;
}
//@}

}

namespace BR {
inline namespace Math {
inline namespace Function {

inline auto max(Float32 x, Float32 y) -> Float32 {
	return libbr_max_32(x, y);
}

inline auto max(Float64 x, Float64 y) -> Float64 {
	return libbr_max_64(x, y);
}

} // inline namespace Function
} // inline namespace Math
} // namespace BR
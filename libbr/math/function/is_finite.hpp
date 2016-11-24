/**
 * @file
 * @brief is_finite
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/is_integral.hpp>
#if !defined(BR_GCC)
#  include <libbr/math/detail/bind.hpp>
#endif

extern "C" {

/**
 * like std::isfinite
 * @param x
 * @return
 */
//@{
#if defined(BR_GCC)
constexpr auto libbr_is_finite_32(BR::Float32 x) -> bool {
	return __builtin_isfinite(x);
}

constexpr auto libbr_is_finite_64(BR::Float64 x) -> bool {
	return __builtin_isfinite(x);
}
#else
inline auto libbr_is_finite_32(BR::Float32 x) -> bool {
	return (((BR::Detail::Math::Bind32{x}.r & 0x7FFFFFFFU) - 0x7F800000U) >> 31) != 0;
}

inline auto libbr_is_finite_64(BR::Float64 x) -> bool {
	return (((BR::Detail::Math::Bind64{x}.h & 0x7FFFFFFFU) - 0x7FF00000U) >> 31) != 0;
}
#endif
//@}

}

namespace BR {
inline namespace Math {
inline namespace Function {

#if defined(BR_GCC)
constexpr
#endif // defined(BR_GCC)
inline auto is_finite(Float32 x) -> bool {
	return libbr_is_finite_32(x);
}

#if defined(BR_GCC)
constexpr
#endif // defined(BR_GCC)
inline auto is_finite(Float64 x) -> bool {
	return libbr_is_finite_64(x);
}

template< typename T >
constexpr auto is_finite(T x) -> EnableIf< IsIntegral<T>, bool > {
	return true;
}

} // inline namespace Function
} // inline namespace Math
} // namespace BR
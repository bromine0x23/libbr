/**
 * @file
 * @brief is_infinite
 * @author Bromine0x23
 * @since 2016/10/11
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
 * like std::isinf
 * @param x
 * @return
 */
//@{
#if defined(BR_GCC)
constexpr auto libbr_is_infinite_32(BR::Float32 x) -> bool {
	return __builtin_isinf(x);
}

constexpr auto libbr_is_infinite_64(BR::Float64 x) -> bool {
	return __builtin_isinf(x);
}
#else
inline auto libbr_is_infinite_32(BR::Float32 x) -> bool {
	return ((BR::Detail::Math::Bind32{x}.r & 0x7FFFFFFFU) ^ 0x7F800000U) == 0;
}

inline auto libbr_is_infinite_64(BR::Float64 x) -> bool {
	return (BR::Detail::Math::Bind64{x}.l | ((BR::Detail::Math::Bind64{x}.h & 0x7FFFFFFFU) ^ 0x7FF00000U)) == 0;
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
inline auto is_infinite(Float32 x) -> bool {
	return libbr_is_infinite_32(x);
}

#if defined(BR_GCC)
constexpr
#endif // defined(BR_GCC)
inline auto is_infinite(Float64 x) -> bool {
	return libbr_is_infinite_64(x);
}

template< typename T >
constexpr auto is_infinite(T x) -> EnableIf< IsIntegral<T>, bool > {
	return false;
}

} // inline namespace Function
} // inline namespace Math
} // namespace BR
/**
 * @file
 * @brief is_normal
 * @author Bromine0x23
 * @since 2016/10/12
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_traits/is_integral.hpp>
#if !defined(BR_GCC)
#  include <libbr/math/float_category.hpp>
#  include <libbr/math/function/classify.hpp>
#endif

extern "C" {

/**
 * like std::isnormal
 * @param x
 * @return
 */
//@{
#if defined(BR_GCC)
constexpr auto libbr_is_normal_32(BR::Float32 x) -> bool {
	return __builtin_isnormal(x);
}

constexpr auto libbr_is_normal_64(BR::Float64 x) -> bool {
	return __builtin_isnormal(x);
}
#else
inline auto libbr_is_normal_32(BR::Float32 x) -> bool {
	return libbr_classify32(x) == static_cast<BR::SInt>(BR::FloatCategory::Normal);
}

inline auto libbr_is_normal_64(BR::Float64 x) -> bool {
	return libbr_classify64(x) == static_cast<BR::SInt>(BR::FloatCategory::Normal);
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
inline auto is_normal(Float32 x) -> bool {
	return libbr_is_normal_32(x);
}

#if defined(BR_GCC)
constexpr
#endif // defined(BR_GCC)
inline auto is_normal(DFloat x) -> bool {
	return libbr_is_normal_64(x);
}

template< typename T >
constexpr auto is_normal(T x) -> EnableIf< IsIntegral<T>, bool > {
	return x != 0;
}

} // inline namespace Function
} // inline namespace Math
} // namespace BR
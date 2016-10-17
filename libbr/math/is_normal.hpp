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
#  include <libbr/math/classify.hpp>
#  include <libbr/math/detail/float.hpp>
#endif

extern "C" {

/**
 * like isnormal
 * @param f
 * @return
 */
//@{
#if defined(BR_GCC)
constexpr auto libbr_is_normal_32(BR::Float32 f) -> bool {
	return __builtin_isnormal(f);
}

constexpr auto libbr_is_normal_64(BR::Float64 f) -> bool {
	return __builtin_isnormal(f);
}
#else
BR_CONSTEXPR_AFTER_CXX11 inline auto libbr_is_normal_32(BR::Float32 f) -> bool {
	return libbr_classify32(f) == static_cast<BR::SInt>(BR::FloatCategory::normal);
}

BR_CONSTEXPR_AFTER_CXX11 inline auto libbr_is_normal_64(BR::Float64 f) -> bool {
	return libbr_classify64(f) == static_cast<BR::SInt>(BR::FloatCategory::normal);
}
#endif
//@}

}

namespace BR {

BR_CONSTEXPR_AFTER_CXX11 inline auto is_normal(Float32 x) -> bool {
	return libbr_is_normal_32(x);
}

BR_CONSTEXPR_AFTER_CXX11 inline auto is_normal(DFloat x) -> bool {
	return libbr_is_normal_64(x);
}

template< typename T >
constexpr auto is_normal(T x) -> EnableIf< IsIntegral<T>, bool > {
	return x != 0;
}

} // namespace BR
/**
 * @file
 * @author Bromine0x23
 * @date 2016/10/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/detail/bind.hpp>
#include <libbr/math/float_category.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/is_integral.hpp>

extern "C" {

/**
 * like std::fpclassfiy
 * @param x
 * @return
 */
//@{
inline auto libbr_classify32(BR::Float32 x) -> BR::SInt {
	auto category = BR::FloatCategory::Normal;
	auto r = BR::Detail::Math::Bind32{x}.r & 0x7FFFFFFFU;
	if (r == 0x00000000U) {
		category = BR::FloatCategory::Zero;
	} else if (r < 0x00800000U) {
		category = BR::FloatCategory::SubNormal;
	} else if (r == 0x7F800000U) {
		category = BR::FloatCategory::Infinite;
	} else if (r > 0x7F800000U) {
		category = BR::FloatCategory::NaN;
	}
	return BR::to_i(category);
}

inline auto libbr_classify64(BR::Float64 x) -> BR::SInt {
	auto category = BR::FloatCategory::Normal;
	auto h = BR::Detail::Math::Bind64{x}.h;
	auto l = BR::Detail::Math::Bind64{x}.l;
	BR::UInt32 t = l | (h & 0x000FFFFFU);
	BR::UInt32 u = h & 0x7FF00000U;
	if ((t | u) == 0x00000000U) {
		category = BR::FloatCategory::Zero;
	} else if (u == 0x00000000U) {
		category = BR::FloatCategory::SubNormal;
	} else if (u == 0x7FF00000U) {
		category = (t != 0x00000000U ? BR::FloatCategory::NaN : BR::FloatCategory::Infinite);
	}
	return BR::to_i(category);
}
//@}

}

namespace BR {
inline namespace Math {
inline namespace Function {

inline auto classify(Float32 x) -> FloatCategory {
	return static_cast<FloatCategory>(libbr_classify32(x));
}

inline auto classify(Float64 x) -> FloatCategory {
	return static_cast<FloatCategory>(libbr_classify64(x));
}

template< typename T >
constexpr auto classify(T x) -> EnableIf< IsIntegral<T>, T > {
	return x != 0 ? FloatCategory::Normal : FloatCategory::Zero;
}

} // inline namespace Function
} // inline namespace Math
} // namespace BR

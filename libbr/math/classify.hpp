/**
 * @file
 * @author Bromine0x23
 * @date 2016/10/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/float_category.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_traits/is_integral.hpp>
#if !defined(BR_GCC)
#  include <libbr/math/detail/float.hpp>
#endif

extern "C" {

#if defined(BR_GCC)
constexpr auto libbr_classify32(BR::Float32 x) -> BR::SInt {
	return __builtin_fpclassify(
		BR::to_i(BR::FloatCategory::nan),
		BR::to_i(BR::FloatCategory::infinite),
		BR::to_i(BR::FloatCategory::normal),
		BR::to_i(BR::FloatCategory::subnormal),
		BR::to_i(BR::FloatCategory::zero),
		x
	);
}

constexpr auto libbr_classify64(BR::Float64 x) -> BR::SInt {
	return __builtin_fpclassify(
		BR::to_i(BR::FloatCategory::nan),
		BR::to_i(BR::FloatCategory::infinite),
		BR::to_i(BR::FloatCategory::normal),
		BR::to_i(BR::FloatCategory::subnormal),
		BR::to_i(BR::FloatCategory::zero),
		x
	);
}
#else
BR_CONSTEXPR_AFTER_CXX11 inline auto libbr_classify32(BR::Float32 x) -> BR::SInt {
	auto category = BR::FloatCategory::normal;
	auto r = BR::Detail::Float::ToRaw32{f}.r & 0x7FFFFFFFU;
	if (r == 0x00000000U) {
		category = BR::FloatCategory::zero;
	} else if (r < 0x00800000U) {
		category = BR::FloatCategory::subnormal;
	} else if (r == 0x7F800000U) {
		category = BR::FloatCategory::infinite;
	} else if (r > 0x7F800000U) {
		category = BR::FloatCategory::nan;
	}
	return BR::to_i(category);
}

BR_CONSTEXPR_AFTER_CXX11 inline auto libbr_classify64(BR::Float64 x) -> BR::SInt {
	auto category = BR::FloatCategory::normal;
	auto h = BR::Detail::Float::ToRaw64{f}.h;
	auto l = BR::Detail::Float::ToRaw64{f}.l;
	UInt32 t = l | (h & 0x000FFFFFU);
	UInt32 u = h & 0x7FF00000U;
	if ((t | u) == 0x00000000U) {
		category = BR::FloatCategory::zero;
	} else if (u == 0x00000000U) {
		category = BR::FloatCategory::subnormal;
	} else if (u == 0x7FF00000U) {
		category = (t != 0x00000000U ? BR::FloatCategory::nan : BR::FloatCategory::infinite);
	}
	return BR::to_i(category);
}
#endif
}

namespace BR {

BR_CONSTEXPR_AFTER_CXX11 inline auto classify(Float32 x) -> FloatCategory {
	return static_cast<FloatCategory>(libbr_classify32(x));
}

BR_CONSTEXPR_AFTER_CXX11 inline auto classify(Float64 x) -> FloatCategory {
	return static_cast<FloatCategory>(libbr_classify64(x));
}

template< typename T >
constexpr auto classify(T x) -> EnableIf< IsIntegral<T>, T > {
	return x != 0 ? FloatCategory::normal : FloatCategory::zero;
}

} // namespace BR

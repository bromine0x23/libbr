#pragma once

#include <libbr/config.hpp>

namespace BR {
namespace Detail {
namespace Math {

union Bind32 {
	Float32 f;
	UInt32 r;
#if defined(BR_LITTLE_ENDIAN)
	struct {
		UInt mantissa:23;
		UInt exponent:8;
		UInt negative:1;
	};
#endif
#if defined(BR_BIG_ENDIAN)
	struct {
		UInt negative:1;
		UInt exponent:8;
		UInt mantissa:23;
	};
#endif

	constexpr Bind32(Float32 f) : f(f) {}

	constexpr Bind32(UInt32 r) : r(r) {}
};

union Bind64 {
	Float64 f;
	UInt64 r;
	struct {
#if defined(BR_LITTLE_ENDIAN)
		UInt32 l;
		UInt32 h;
#endif
#if defined(BR_BIG_ENDIAN)
		UInt32 h
		UInt32 l;
#endif
	};
#if defined(BR_LITTLE_ENDIAN)
	struct {
		UInt mantissa1:32;
		UInt mantissa0:20;
		UInt exponent:11;
		UInt negative:1;
	};
#endif
#if defined(BR_BIG_ENDIAN)
	struct {
		UInt negative:1;
		UInt exponent:11;
		UInt mantissa0:20;
		UInt mantissa1:32;
	};
#endif

	constexpr Bind64(Float64 f) : f(f) {}

	constexpr Bind64(UInt64 r) : r(r) {}

#if defined(BR_LITTLE_ENDIAN)
	constexpr Bind64(UInt32 h, UInt32 l) : l(l), h(h) {}
#endif
#if defined(BR_BIG_ENDIAN)
	constexpr Bind64(UInt32 h, UInt32 l) : h(h), l(l) {}
#endif
};

} // namespace Math
} // namespace Detail
} // namespace BR
#pragma once

#include <libbr/config.hpp>

#if defined(BR_SKIP_TYPE_TRANSFORM_TEST)

#define SUFFIX_TRANSFORM_CHECK(...)
#define SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(...)

#else

#define SUFFIX_TRANSFORM_CHECK(traits, applied_type, from_suffix, to_suffix)\
	TRANSFORM_CHECK(traits, applied_type to_suffix, applied_type from_suffix);\
	TRANSFORM_CHECK(traits, applied_type to_suffix, applied_type from_suffix);

#define SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(traits, from_suffix, to_suffix)\
	SUFFIX_TRANSFORM_CHECK(traits, bool, from_suffix, to_suffix);\
	SUFFIX_TRANSFORM_CHECK(traits, char, from_suffix, to_suffix);\
	SUFFIX_TRANSFORM_CHECK(traits, int, from_suffix, to_suffix);\
	SUFFIX_TRANSFORM_CHECK(traits, double, from_suffix, to_suffix);\
	SUFFIX_TRANSFORM_CHECK(traits, char32_t, from_suffix, to_suffix);

#endif
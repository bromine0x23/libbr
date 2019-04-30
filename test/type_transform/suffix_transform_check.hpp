#pragma once

#include <libbr/config.hpp>

#if defined(BR_SKIP_TYPE_TRANSFORM_TEST)

#define SUFFIX_TRANSFORM_CHECK(...)
#define SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(...)

#else

#define SUFFIX_TRANSFORM_CHECK(expected_type, traits, ...)\
	TRANSFORM_CHECK(expected_type, TRANSFORM_APPLY_FULL( traits, ##__VA_ARGS__));\
	TRANSFORM_CHECK(expected_type, TRANSFORM_APPLY_SHORT(traits, ##__VA_ARGS__));

#define SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(traits, from_suffix, to_suffix)\
	SUFFIX_TRANSFORM_CHECK(bool     to_suffix, traits, bool     from_suffix);\
	SUFFIX_TRANSFORM_CHECK(char     to_suffix, traits, char     from_suffix);\
	SUFFIX_TRANSFORM_CHECK(wchar_t  to_suffix, traits, wchar_t  from_suffix);\
	SUFFIX_TRANSFORM_CHECK(char16_t to_suffix, traits, char16_t from_suffix);\
	SUFFIX_TRANSFORM_CHECK(char32_t to_suffix, traits, char32_t from_suffix);\
	SUFFIX_TRANSFORM_CHECK(int      to_suffix, traits, int      from_suffix);\
	SUFFIX_TRANSFORM_CHECK(double   to_suffix, traits, double   from_suffix);

#endif
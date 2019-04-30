#pragma once

#include <libbr/config.hpp>

#if defined(BR_SKIP_TYPE_TRAITS_TEST)

#define IS_TRAITS_CHECK(...)
#define IS_TRAITS_CHECK_CV(...)

#else

#define IS_TRAITS_CHECK(expected_value, Traits, traits, ...)\
	CONSTANT_CHECK(expected_value,  (Is   ## Traits< __VA_ARGS__ >{}));\
	CONSTANT_CHECK(expected_value, !(Not  ## Traits< __VA_ARGS__ >{}));\
	CONSTANT_CHECK(expected_value,  (is_  ## traits< __VA_ARGS__ >)); \
	CONSTANT_CHECK(expected_value, !(not_ ## traits< __VA_ARGS__ >));

#define IS_TRAITS_CHECK_CV(expected_value, Traits, traits, T)\
	IS_TRAITS_CHECK(expected_value, Traits, traits, T);\
	IS_TRAITS_CHECK(expected_value, Traits, traits, T const);\
	IS_TRAITS_CHECK(expected_value, Traits, traits, T volatile);\
	IS_TRAITS_CHECK(expected_value, Traits, traits, T const volatile);

#endif
#pragma once

#include <libbr/config.hpp>

#if defined(BR_SKIP_TYPE_TRAITS_TEST)

#define HAS_TRAITS_CHECK(...)
#define HAS_TRAITS_CHECK_CV(...)

#else

#define HAS_TRAITS_CHECK(expected_value, Traits, traits, ...)\
	CONSTANT_CHECK(expected_value,  (Has  ## Traits< __VA_ARGS__ >{}));\
	CONSTANT_CHECK(expected_value, !(No   ## Traits< __VA_ARGS__ >{}));\
	CONSTANT_CHECK(expected_value,  (has_ ## traits< __VA_ARGS__ >));\
	CONSTANT_CHECK(expected_value, !(no_  ## traits< __VA_ARGS__ >));

#define HAS_TRAITS_CHECK_CV(expected_value, Traits, traits, T)\
	HAS_TRAITS_CHECK(expected_value, Traits, traits, T);\
	HAS_TRAITS_CHECK(expected_value, Traits, traits, T const);\
	HAS_TRAITS_CHECK(expected_value, Traits, traits, T volatile);\
	HAS_TRAITS_CHECK(expected_value, Traits, traits, T const volatile);

#endif
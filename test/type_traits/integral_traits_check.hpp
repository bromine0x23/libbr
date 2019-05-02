#pragma once

#include <libbr/config.hpp>

#if defined(BR_SKIP_TYPE_TRAITS_TEST)

#define INTEGRAL_TRAITS_CHECK(...)

#else

#define INTEGRAL_TRAITS_APPLY(name, ...) ((name< __VA_ARGS__ >{})())

#define INTEGRAL_TRAITS_CHECK(expected_value, Traits, traits, ...)\
	CONSTANT_CHECK(expected_value, INTEGRAL_TRAITS_APPLY(Traits, ##__VA_ARGS__));

#endif
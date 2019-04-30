#pragma once

#include "../test.hpp"
#include <libbr/config.hpp>

#if defined(BR_SKIP_TYPE_TRANSFORM_TEST)

#define TRANSFORM_CHECK(...)

#else

#include <libbr/type_traits/is_same.hpp>

#define TRANSFORM_CHECK(expected_type, actual_type) EXPECT_TRUE((::BR::is_same< expected_type, actual_type >))

#endif

#define TRANSFORM_APPLY_FULL( name, ...) Type ## name< __VA_ARGS__ >::Type
#define TRANSFORM_APPLY_SHORT(name, ...)         name< __VA_ARGS__ >

#include "suffix_transform_check.hpp"
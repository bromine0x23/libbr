#pragma once

#include "../test.hpp"
#include <libbr/config.hpp>

#if defined(BR_SKIP_TYPE_TRAITS_TEST)

#define CONSTANT_CHECK(...)

#else

#define CONSTANT_CHECK(expected_value, actual_value) EXPECT_EQ(expected_value, actual_value)

#endif

#include "is_traits_check.hpp"
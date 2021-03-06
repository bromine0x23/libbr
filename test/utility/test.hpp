#pragma once

#include "../test.hpp"
#include <libbr/config.hpp>

#if defined(BR_SKIP_UTILITY_TEST)

#define LOGICAL_CONNECTIVE_CHECK(...)

#else

#define LOGICAL_CONNECTIVE_CHECK(expected_value, Connective, connective, ...)\
  EXPECT_EQ(expected_value, (Connective<__VA_ARGS__>{}));\
  EXPECT_EQ(expected_value, (connective<__VA_ARGS__>  ));

#define LOGICAL_CONNECTIVE_CHECK_BY_VALUE(expected_value, Connective, connective, ...)\
  EXPECT_EQ(expected_value, (Connective## By## Value <__VA_ARGS__>{}));\
  EXPECT_EQ(expected_value, (connective##_by##_value<__VA_ARGS__>  ));

#endif


#pragma once

#include <gtest/gtest.h>
#include <libbr/config.hpp>

#define CONSTANT_CHECK(expected_value, actual_value) ASSERT_EQ(expected_value, actual_value)

#define TRAITS_APPLY_IS( name, ...) (Is  ## name< __VA_ARGS__ >()())
#define TRAITS_APPLY_NOT(name, ...) (Not ## name< __VA_ARGS__ >()())

#define IS_TRAITS_CHECK(expected_value, traits, ...)\
	CONSTANT_CHECK(expected_value,  TRAITS_APPLY_IS( traits, ##__VA_ARGS__));\
	CONSTANT_CHECK(expected_value, !TRAITS_APPLY_NOT(traits, ##__VA_ARGS__));

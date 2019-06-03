#include "test.hpp"

#include <libbr/strings/string_fill.hpp>

using namespace BR;

TEST(Strings, string_fill) {
	char array[10] = {};

	auto result = string_fill(array, 5, 'c');

	for (int i = 0; i < 5; ++i) {
		EXPECT_EQ('c', result[i]);
	}

	EXPECT_EQ('\0', result[5]);
}

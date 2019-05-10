#include "test.hpp"

#include <libbr/memory/memory_fill.hpp>

using namespace BR;

TEST(Memory, memory_fill) {
	int array[5] = {};

	auto result = memory_fill(array + 1, 3 * sizeof(int), 0xEF);

	EXPECT_EQ(array + 1, result);

	EXPECT_EQ(0xEFEFEFEF, array[1]);
	EXPECT_EQ(0xEFEFEFEF, array[2]);
	EXPECT_EQ(0xEFEFEFEF, array[3]);
}

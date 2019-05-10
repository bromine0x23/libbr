#include "test.hpp"

#include <libbr/memory/memory_copy.hpp>

using namespace BR;

TEST(Memory, memory_copy) {
	{
		char string[] = "1234567890";

		memory_copy(string + 3, string + 4, 3);

		EXPECT_STREQ(string, "1234456890");
	}
	{
		int array[] = {0, 1, 2, 3, 4};

		memory_copy(array, array + 1, 3 * sizeof(array[0]));

		EXPECT_EQ(0, array[0]);
		EXPECT_EQ(0, array[1]);
		EXPECT_EQ(1, array[2]);
		EXPECT_EQ(2, array[3]);
		EXPECT_EQ(4, array[4]);
	}
}

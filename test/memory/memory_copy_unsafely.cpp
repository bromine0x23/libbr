#include "test.hpp"

#include <libbr/memory/memory_copy_unsafely.hpp>

using namespace BR;

TEST(Memory, memory_copy_unsafely) {
	{
		char string[] = "1234567890";

		memory_copy_unsafely(string + 3, string + 4, 3);

		EXPECT_STREQ(string, "1234456890");
	}
}

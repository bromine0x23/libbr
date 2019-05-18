#include "test.hpp"

#include <libbr/iterators/prev.hpp>

using namespace BR;

TEST(Iterators, prev) {
	char string[] = "12345";
	EXPECT_EQ(string + 4, prev(string + 5));
	EXPECT_EQ(string + 3, prev(prev(string + 5)));
	EXPECT_EQ(string + 2, prev(string + 5, 3));
}

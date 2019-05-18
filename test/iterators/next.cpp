#include "test.hpp"

#include <libbr/iterators/next.hpp>

using namespace BR;

TEST(Iterators, next) {
	char string[] = "12345";
	EXPECT_EQ(string + 1, next(string));
	EXPECT_EQ(string + 2, next(next(string)));
	EXPECT_EQ(string + 3, next(string, 3));
}

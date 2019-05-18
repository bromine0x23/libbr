#include "test.hpp"

#include <libbr/iterators/distance.hpp>

using namespace BR;

TEST(Iterators, distance) {
	char string[] = "12345";
	EXPECT_EQ(3, distance(string, string + 3));

}

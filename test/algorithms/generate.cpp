#include "test.hpp"

#include <libbr/algorithms/generate.hpp>

using namespace BR;

TEST(Algorithms, generate) {
	int array[10] = {};

	int x = 0;

	generate(array, array + 5, [&x]{ return ++x; });

	EXPECT_EQ(1, array[0]);
	EXPECT_EQ(5, array[4]);
	EXPECT_EQ(0, array[9]);
}

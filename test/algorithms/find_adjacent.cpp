#include "test.hpp"

#include <libbr/algorithms/find_adjacent.hpp>

#include <libbr/functional/greater.hpp>

using namespace BR;

TEST(Algorithms, find_adjacent) {
	int array[] = { 0, 1, 2, 3, 40, 40, 41, 41, 5 };

	EXPECT_EQ(array + 4, find_adjacent(array, array + 9));

	EXPECT_EQ(array + 7, find_adjacent(array, array + 9, Greater<>{}));

	EXPECT_EQ(array + 9, find_adjacent(array, array + 9, [](auto x, auto y){ return x + y >= 100; }));
}

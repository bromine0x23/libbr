#include "test.hpp"

#include <libbr/algorithms/search_repeated.hpp>

using namespace BR;

TEST(Algorithms, search_repeated) {
	int array[] = { 1, 1, 2, 3, 3, 2, 2, 1, 1, 1, 3, 3 };

	EXPECT_EQ(array, search_repeated(array, array + 12, 2, 1));
	EXPECT_EQ(array + 5, search_repeated(array, array + 12, 2, 2));
	EXPECT_EQ(array + 12, search_repeated(array, array + 12, 3, 2));
	EXPECT_EQ(array + 7, search_repeated(array, array + 12, 5, 0.0, [](auto x, auto _){ return x % 2 == 1; }));
}
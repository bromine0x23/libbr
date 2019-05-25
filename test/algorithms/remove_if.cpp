#include "test.hpp"

#include <libbr/algorithms/remove_if.hpp>

using namespace BR;

TEST(Algorithms, remove_if) {
	auto is_even = [](int x){ return x % 2 == 0; };

	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	auto new_end = remove_if(array, array + 10, is_even);

	EXPECT_EQ(5, new_end - array);
	EXPECT_EQ(1, array[0]);
	EXPECT_EQ(9, array[4]);
}

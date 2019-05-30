#include "test.hpp"

#include <libbr/algorithms/remove_copy_if.hpp>


using namespace BR;

TEST(Algorithms, remove_copy_if) {
	auto is_even = [](int x){ return x % 2 == 0; };

	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	int removed[10] = {};

	auto end = remove_copy_if(array, array + 10, removed, is_even);

	EXPECT_EQ(5, end - removed);
	EXPECT_EQ(1, removed[0]);
	EXPECT_EQ(9, removed[4]);
}

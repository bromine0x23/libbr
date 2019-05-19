#include "test.hpp"

#include <libbr/algorithms/all_of.hpp>

using namespace BR;

TEST(Algorithms, all_of) {
	auto is_even = [](int x){ return x % 2 == 0; };
	auto is_less_then_ten = [](int x){ return x < 10; };

	{
		int array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		EXPECT_FALSE(all_of(array, array + 10, is_even));

		EXPECT_TRUE(all_of(array, array + 10, is_less_then_ten));
	}
}

#include "test.hpp"

#include <libbr/algorithms/none_of.hpp>

using namespace BR;

TEST(Algorithms, none_of) {
	auto is_even = [](int x){ return x % 2 == 0; };
	auto is_greater_then_ten = [](int x){ return x > 10; };

	{
		int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

		EXPECT_FALSE(none_of(array, array + 10, is_even));

		EXPECT_TRUE(none_of(array, array + 10, is_greater_then_ten));
	}
}

#include "test.hpp"

#include <libbr/algorithms/any_of.hpp>

using namespace BR;

TEST(Algorithms, any_of) {
	auto is_even = [](int x){ return x % 2 == 0; };
	auto is_congruence_to_eleven = [](int x){ return x % 11 == 0; };

	{
		int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

		EXPECT_TRUE(any_of(array, array + 10, is_even));

		EXPECT_FALSE(any_of(array, array + 10, is_congruence_to_eleven));
	}
}

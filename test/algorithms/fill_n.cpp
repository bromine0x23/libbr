#include "test.hpp"

#include <libbr/algorithms/fill_n.hpp>

#include <libbr/algorithms/all_of.hpp>

using namespace BR;

TEST(Algorithms, fill_n) {
	{
		char array[10] = {};

		fill_n(array, 10, 'c');

		EXPECT_TRUE(all_of(array, array + 10, [](char x){ return x == 'c'; }));
	} {
		int array[10] = {};

		fill_n(array, 10, 0x23);

		EXPECT_TRUE(all_of(array, array + 10, [](int x){ return x == 0x23; }));
	}
}

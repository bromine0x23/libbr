#include "../test.hpp"
#include <libbr/algorithm/all_of.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>

using namespace BR;

TEST(Algorithm, all_of) {
	{
		DynamicArray<int> array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		EXPECT_FALSE(all_of(array.begin(), array.end(), [](auto x){ return x % 2 == 0; }));

		EXPECT_TRUE(all_of(array.begin(), array.end(), [](auto x){ return x < 10; }));
	} {
		DList<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		EXPECT_FALSE(all_of(list.begin(), list.end(), [](auto x){ return x % 2 == 0; }));

		EXPECT_TRUE(all_of(list.begin(), list.end(), [](auto x){ return x < 10; }));
	}
}

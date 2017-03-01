#include "../test.hpp"
#include <libbr/algorithm/any_of.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>

using namespace BR;

TEST(Algorithm, any_of) {
	{
		DynamicArray<int> array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		EXPECT_TRUE(any_of(array.begin(), array.end(), [](auto x){ return x % 2 == 0; }));

		EXPECT_FALSE(any_of(array.begin(), array.end(), [](auto x){ return x % 11 == 0; }));
	} {
		DList<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		EXPECT_TRUE(any_of(list.begin(), list.end(), [](auto x){ return x % 2 == 0; }));

		EXPECT_FALSE(any_of(list.begin(), list.end(), [](auto x){ return x % 11 == 0; }));
	}
}

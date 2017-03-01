#include "../test.hpp"
#include <libbr/algorithm/binary_search.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>

using namespace BR;

TEST(Algorithm, binary_search) {
	{
		DynamicArray<int> array{1, 3, 4, 5, 9};

		EXPECT_FALSE(binary_search(array.begin(), array.end(), 2));

		EXPECT_TRUE(binary_search(array.begin(), array.end(), 3));
	} {
		DList<int> list{1, 3, 4, 5, 9};

		EXPECT_FALSE(binary_search(list.begin(), list.end(), 2));

		EXPECT_TRUE(binary_search(list.begin(), list.end(), 3));
	}
}

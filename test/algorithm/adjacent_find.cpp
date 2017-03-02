#include "../test.hpp"
#include <libbr/algorithm/adjacent_find.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/functional/greater.hpp>
#include <libbr/iterator/distance.hpp>

using namespace BR;

TEST(Algorithm, adjacent_find) {
	{
		DynamicArray<int> array{ 0, 1, 2, 3, 40, 40, 41, 41, 5 };

		EXPECT_EQ(4, distance(array.cbegin(), adjacent_find(array.cbegin(), array.cend())));

		EXPECT_EQ(7, distance(array.cbegin(), adjacent_find(array.cbegin(), array.cend(), Greater<int, int>())));
	} {
		DList<int> list{ 0, 1, 2, 3, 40, 40, 41, 41, 5 };

		EXPECT_EQ(4, distance(list.cbegin(), adjacent_find(list.cbegin(), list.cend())));

		EXPECT_EQ(7, distance(list.cbegin(), adjacent_find(list.cbegin(), list.cend(), Greater<int, int>())));
	}
}

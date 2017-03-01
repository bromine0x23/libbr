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

		EXPECT_EQ(4, distance(array.begin(), adjacent_find(array.begin(), array.end())));

		EXPECT_EQ(7, distance(array.begin(), adjacent_find(array.begin(), array.end(), Greater<int, int>())));
	} {
		DList<int> list{ 0, 1, 2, 3, 40, 40, 41, 41, 5 };

		EXPECT_EQ(4, distance(list.begin(), adjacent_find(list.begin(), list.end())));

		EXPECT_EQ(7, distance(list.begin(), adjacent_find(list.begin(), list.end(), Greater<int, int>())));
	}
}

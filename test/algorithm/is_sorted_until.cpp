#include "../test.hpp"
#include <libbr/algorithm/is_sorted_until.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>
#include <libbr/iterator/distance.hpp>

using namespace BR;

TEST(Algorithm, is_sorted_until) {
	{
		DynamicArray<int> array{ 4, 5, 9, 3, 1, 1 };

		EXPECT_EQ(3, distance(array.cbegin(), is_sorted_until(array.cbegin(), array.cend())));
	} {
		DList<int> list{ 4, 5, 9, 3, 1, 1 };

		EXPECT_EQ(3, distance(list.cbegin(), is_sorted_until(list.cbegin(), list.cend())));
	} {
		SList<int> list{ 4, 5, 9, 3, 1, 1 };

		EXPECT_EQ(3, distance(list.cbegin(), is_sorted_until(list.cbegin(), list.cend())));
	}
}

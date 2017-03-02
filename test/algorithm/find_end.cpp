#include "../test.hpp"
#include <libbr/algorithm/find_end.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>
#include <libbr/iterator/distance.hpp>

using namespace BR;

TEST(Algorithm, find_end) {
	{
		DynamicArray<int> array{ 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4 };
		DynamicArray<int> sequence{ 1, 2, 3 };

		EXPECT_EQ(8, distance(array.cbegin(), find_end(array.cbegin(), array.cend(), sequence.cbegin(), sequence.cend())));
	} {
		DList<int> list{ 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4 };
		DList<int> sequence{ 1, 2, 3 };

		EXPECT_EQ(8, distance(list.cbegin(), find_end(list.cbegin(), list.cend(), sequence.cbegin(), sequence.cend())));
	} {
		SList<int> list{ 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4 };
		SList<int> sequence{ 1, 2, 3 };

		EXPECT_EQ(8, distance(list.cbegin(), find_end(list.cbegin(), list.cend(), sequence.cbegin(), sequence.cend())));
	}
}

#include "../test.hpp"
#include <libbr/algorithm/find_first_of.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>
#include <libbr/iterator/distance.hpp>

using namespace BR;

TEST(Algorithm, find_first_of) {
	{
		DynamicArray<int> array{0, 2, 3, 25, 5};
		DynamicArray<int> values{3, 19, 10, 2};

		EXPECT_EQ(1, distance(array.cbegin(), find_first_of(array.cbegin(), array.cend(), values.cbegin(), values.cend())));
	} {
		DList<int> list{0, 2, 3, 25, 5};
		DList<int> values{3, 19, 10, 2};

		EXPECT_EQ(1, distance(list.cbegin(), find_first_of(list.cbegin(), list.cend(), values.cbegin(), values.cend())));
	} {
		SList<int> list{0, 2, 3, 25, 5};
		SList<int> values{3, 19, 10, 2};

		EXPECT_EQ(1, distance(list.cbegin(), find_first_of(list.cbegin(), list.cend(), values.cbegin(), values.cend())));
	}
}

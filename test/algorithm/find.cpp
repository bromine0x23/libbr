#include "../test.hpp"
#include <libbr/algorithm/find.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>

using namespace BR;

TEST(Algorithm, find) {
	{
		DynamicArray<int> array{0, 1, 2, 3, 4};

		EXPECT_EQ(3, *find(array.cbegin(), array.cend(), 3));

		EXPECT_EQ(array.cend(), find(array.cbegin(), array.cend(), 5));
	} {
		DList<int> list{0, 1, 2, 3, 4};

		EXPECT_EQ(3, *find(list.cbegin(), list.cend(), 3));

		EXPECT_EQ(list.cend(), find(list.cbegin(), list.cend(), 5));
	} {
		SList<int> list{0, 1, 2, 3, 4};

		EXPECT_EQ(3, *find(list.cbegin(), list.cend(), 3));

		EXPECT_EQ(list.cend(), find(list.cbegin(), list.cend(), 5));
	}
}

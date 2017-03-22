#include "../test.hpp"
#include <libbr/algorithm/find_if_not.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>

using namespace BR;

TEST(Algorithm, find_if_not) {
	{
		DynamicArray<int> array{0, 1, 2, 3, 4};

		EXPECT_EQ(3, *find_if_not(array.cbegin(), array.cend(), [](int x){ return x < 3; }));

		EXPECT_EQ(array.cend(), find_if_not(array.cbegin(), array.cend(), [](int x){ return x <  5; }));
	} {
		DList<int> list{0, 1, 2, 3, 4};

		EXPECT_EQ(3, *find_if_not(list.cbegin(), list.cend(), [](int x){ return x < 3; }));

		EXPECT_EQ(list.cend(), find_if_not(list.cbegin(), list.cend(), [](int x){ return x < 5; }));
	} {
		SList<int> list{0, 1, 2, 3, 4};

		EXPECT_EQ(3, *find_if_not(list.cbegin(), list.cend(), [](int x){ return x < 3; }));

		EXPECT_EQ(list.cend(), find_if_not(list.cbegin(), list.cend(), [](int x){ return x < 5; }));
	}
}

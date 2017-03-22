#include "../test.hpp"
#include <libbr/algorithm/find_if.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>

using namespace BR;

TEST(Algorithm, find_if) {
	{
		DynamicArray<int> array{0, 1, 2, 3, 4};

		EXPECT_EQ(3, *find_if(array.cbegin(), array.cend(), [](int x){ return x > 2; }));

		EXPECT_EQ(array.cend(), find_if(array.cbegin(), array.cend(), [](int x){ return x > 4; }));
	} {
		DList<int> list{0, 1, 2, 3, 4};

		EXPECT_EQ(3, *find_if(list.cbegin(), list.cend(), [](int x){ return x > 2; }));

		EXPECT_EQ(list.cend(), find_if(list.cbegin(), list.cend(), [](int x){ return x > 4; }));
	} {
		SList<int> list{0, 1, 2, 3, 4};

		EXPECT_EQ(3, *find_if(list.cbegin(), list.cend(), [](int x){ return x > 2; }));

		EXPECT_EQ(list.cend(), find_if(list.cbegin(), list.cend(), [](int x){ return x > 4; }));
	}
}

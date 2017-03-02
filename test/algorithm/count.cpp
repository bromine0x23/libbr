#include "../test.hpp"
#include <libbr/algorithm/count.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>

using namespace BR;

TEST(Algorithm, count) {
	{
		DynamicArray<int> array{ 1, 2, 3, 4, 4, 3, 7, 8, 9, 10 };

		EXPECT_EQ(2, count(array.cbegin(), array.cend(), 3));

		EXPECT_EQ(0, count(array.cbegin(), array.cend(), 5));
	} {
		DList<int> list{ 1, 2, 3, 4, 4, 3, 7, 8, 9, 10 };

		EXPECT_EQ(2, count(list.cbegin(), list.cend(), 3));

		EXPECT_EQ(0, count(list.cbegin(), list.cend(), 5));
	} {
		SList<int> list{ 1, 2, 3, 4, 4, 3, 7, 8, 9, 10 };

		EXPECT_EQ(2, count(list.cbegin(), list.cend(), 3));

		EXPECT_EQ(0, count(list.cbegin(), list.cend(), 5));
	}
}

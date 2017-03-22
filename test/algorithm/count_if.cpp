#include "../test.hpp"
#include <libbr/algorithm/count_if.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>

using namespace BR;

TEST(Algorithm, count_if) {
	{
		DynamicArray<int> array{ 1, 2, 3, 4, 4, 3, 7, 8, 9, 10 };

		EXPECT_EQ(3, count_if(array.cbegin(), array.cend(), [](int x){ return x % 3 == 0; }));
	} {
		DList<int> list{ 1, 2, 3, 4, 4, 3, 7, 8, 9, 10 };

		EXPECT_EQ(3, count_if(list.cbegin(), list.cend(), [](int x){ return x % 3 == 0; }));
	} {
		SList<int> list{ 1, 2, 3, 4, 4, 3, 7, 8, 9, 10 };

		EXPECT_EQ(3, count_if(list.cbegin(), list.cend(), [](int x){ return x % 3 == 0; }));
	}
}

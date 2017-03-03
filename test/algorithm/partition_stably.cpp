#include "../test.hpp"
#include <libbr/algorithm/partition_stably.hpp>

#include <libbr/algorithm/partition.hpp>
#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>

using namespace BR;

TEST(Algorithm, partition_stably) {
	{
		DynamicArray<int> array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		auto is_even = [](int x){ return x % 2 == 0; };

		partition_stably(array.begin(), array.end(), is_even);

		EXPECT_EQ((DynamicArray<int>{ 2, 4, 6, 8, 1, 3, 5, 7, 9 }), array);
	} {
		DList<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		auto is_even = [](int x){ return x % 2 == 0; };

		partition_stably(list.begin(), list.end(), is_even);

		EXPECT_EQ((DList<int>{ 2, 4, 6, 8, 1, 3, 5, 7, 9 }), list);
	} {
		SList<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		auto is_even = [](int x){ return x % 2 == 0; };

		partition_stably(list.begin(), list.end(), is_even);

		EXPECT_EQ((SList<int>{ 2, 4, 6, 8, 1, 3, 5, 7, 9 }), list);
	}
}

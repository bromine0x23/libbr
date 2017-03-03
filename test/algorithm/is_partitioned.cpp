#include "../test.hpp"
#include <libbr/algorithm/is_partitioned.hpp>

#include <libbr/algorithm/partition.hpp>
#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>

using namespace BR;

TEST(Algorithm, is_partitioned) {
	{
		DynamicArray<int> array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		auto is_even = [](int x){ return x % 2 == 0; };

		EXPECT_FALSE(is_partitioned(array.cbegin(), array.cend(), is_even));

		partition(array.begin(), array.end(), is_even);

		EXPECT_TRUE(is_partitioned(array.cbegin(), array.cend(), is_even));
	} {
		DList<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		auto is_even = [](int x){ return x % 2 == 0; };

		EXPECT_FALSE(is_partitioned(list.cbegin(), list.cend(), is_even));

		partition(list.begin(), list.end(), is_even);

		EXPECT_TRUE(is_partitioned(list.cbegin(), list.cend(), is_even));
	} {
		SList<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		auto is_even = [](int x){ return x % 2 == 0; };

		EXPECT_FALSE(is_partitioned(list.cbegin(), list.cend(), is_even));

		partition(list.begin(), list.end(), is_even);

		EXPECT_TRUE(is_partitioned(list.cbegin(), list.cend(), is_even));
	}
}

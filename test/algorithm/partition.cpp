#include "../test.hpp"
#include <libbr/algorithm/partition.hpp>

#include <libbr/algorithm/all_of.hpp>
#include <libbr/algorithm/any_of.hpp>
#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>

using namespace BR;

TEST(Algorithm, partition) {
	{
		DynamicArray<int> array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		auto is_even = [](int x){ return x % 2 == 0; };

		auto pivot = partition(array.begin(), array.end(), is_even);

		EXPECT_TRUE(all_of(array.begin(), pivot, is_even));

		EXPECT_FALSE(any_of(pivot, array.end(), is_even));
	} {
		DList<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		auto is_even = [](int x){ return x % 2 == 0; };

		auto pivot = partition(list.begin(), list.end(), is_even);

		EXPECT_TRUE(all_of(list.begin(), pivot, is_even));

		EXPECT_FALSE(any_of(pivot, list.end(), is_even));
	}  {
		SList<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		auto is_even = [](int x){ return x % 2 == 0; };

		auto pivot = partition(list.begin(), list.end(), is_even);

		EXPECT_TRUE(all_of(list.begin(), pivot, is_even));

		EXPECT_FALSE(any_of(pivot, list.end(), is_even));
	}
}

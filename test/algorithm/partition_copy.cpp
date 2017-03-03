#include "../test.hpp"
#include <libbr/algorithm/partition_copy.hpp>

#include <libbr/algorithm/all_of.hpp>
#include <libbr/algorithm/any_of.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/iterator/insert_back_iterator.hpp>

using namespace BR;

TEST(Algorithm, partition_copy) {
	DynamicArray<int> array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	DynamicArray<int> group_true, group_false;

	auto is_even = [](int x){ return x % 2 == 0; };

	auto pivot = partition_copy(array.begin(), array.end(), make_insert_back_iterator(group_true), make_insert_back_iterator(group_false), is_even);

	EXPECT_TRUE(all_of(group_true.cbegin(), group_true.cend(), is_even));

	EXPECT_FALSE(any_of(group_false.cbegin(), group_false.cend(), is_even));
}

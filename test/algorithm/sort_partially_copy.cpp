#include "../test.hpp"
#include <libbr/algorithm/sort_partially_copy.hpp>

#include <libbr/algorithm/is_sorted.hpp>
#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>
#include <libbr/iterator/distance.hpp>

using namespace BR;

TEST(Algorithm, sort_partially_copy) {
	{
		DynamicArray<int> array{ 0, 2, 4, 1, 3 };

		DynamicArray<int> output0(3);

		auto end0 = sort_partially_copy(array.cbegin(), array.cend(), output0.begin(), output0.end());

		EXPECT_TRUE(is_sorted(output0.cbegin(), output0.cend()));

		EXPECT_EQ(output0.end(), end0);

		DynamicArray<int> output1(10);

		auto end1 = sort_partially_copy(array.cbegin(), array.cend(), output1.begin(), output1.end());

		EXPECT_TRUE(is_sorted(output1.cbegin(), output1.cbegin() + array.size()));

		EXPECT_NE(output1.end(), end1);
	} {
		DList<int> list{ 0, 2, 4, 1, 3 };

		DynamicArray<int> output0(3);

		auto end0 = sort_partially_copy(list.cbegin(), list.cend(), output0.begin(), output0.end());

		EXPECT_TRUE(is_sorted(output0.cbegin(), output0.cend()));

		EXPECT_EQ(output0.end(), end0);

		DynamicArray<int> output1(10);

		auto end1 = sort_partially_copy(list.cbegin(), list.cend(), output1.begin(), output1.end());

		EXPECT_TRUE(is_sorted(output1.cbegin(), output1.cbegin() + list.size()));

		EXPECT_NE(output1.end(), end1);
	} {
		SList<int> list{ 0, 2, 4, 1, 3 };

		DynamicArray<int> output0(3);

		auto end0 = sort_partially_copy(list.cbegin(), list.cend(), output0.begin(), output0.end());

		EXPECT_TRUE(is_sorted(output0.cbegin(), output0.cend()));

		EXPECT_EQ(output0.end(), end0);

		DynamicArray<int> output1(10);

		auto end1 = sort_partially_copy(list.cbegin(), list.cend(), output1.begin(), output1.end());

		EXPECT_TRUE(is_sorted(output1.cbegin(), output1.cbegin() + distance(list.cbegin(), list.cend())));

		EXPECT_NE(output1.end(), end1);
	}
}

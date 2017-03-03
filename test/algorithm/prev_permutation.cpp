#include "../test.hpp"
#include <libbr/algorithm/prev_permutation.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>

using namespace BR;

TEST(Algorithm, prev_permutation) {
	{
		DynamicArray<int> array{ 2, 1, 1 };

		EXPECT_TRUE(prev_permutation(array.begin(), array.end()));

		EXPECT_EQ((DynamicArray<int>{ 1, 2, 1 }), array);

		EXPECT_TRUE(prev_permutation(array.begin(), array.end()));

		EXPECT_EQ((DynamicArray<int>{ 1, 1, 2 }), array);

		EXPECT_FALSE(prev_permutation(array.begin(), array.end()));
	} {
		DList<int> list{ 2, 1, 1 };

		EXPECT_TRUE(prev_permutation(list.begin(), list.end()));

		EXPECT_EQ((DList<int>{ 1, 2, 1 }), list);

		EXPECT_TRUE(prev_permutation(list.begin(), list.end()));

		EXPECT_EQ((DList<int>{ 1, 1, 2 }), list);

		EXPECT_FALSE(prev_permutation(list.begin(), list.end()));
	}
}

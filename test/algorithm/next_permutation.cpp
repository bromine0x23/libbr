#include "../test.hpp"
#include <libbr/algorithm/next_permutation.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>

using namespace BR;

TEST(Algorithm, next_permutation) {
	{
		DynamicArray<int> array{ 1, 1, 2 };

		EXPECT_TRUE(next_permutation(array.begin(), array.end()));

		EXPECT_EQ((DynamicArray<int>{ 1, 2, 1 }), array);

		EXPECT_TRUE(next_permutation(array.begin(), array.end()));

		EXPECT_EQ((DynamicArray<int>{ 2, 1, 1 }), array);

		EXPECT_FALSE(next_permutation(array.begin(), array.end()));
	} {
		DList<int> list{ 1, 1, 2 };

		EXPECT_TRUE(next_permutation(list.begin(), list.end()));

		EXPECT_EQ((DList<int>{ 1, 2, 1 }), list);

		EXPECT_TRUE(next_permutation(list.begin(), list.end()));

		EXPECT_EQ((DList<int>{ 2, 1, 1 }), list);

		EXPECT_FALSE(next_permutation(list.begin(), list.end()));
	}
}

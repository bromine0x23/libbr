#include "../test.hpp"
#include <libbr/algorithm/remove.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>

using namespace BR;

TEST(Algorithm, remove) {
	{
		DynamicArray<int> array{ 1, 2, 3, 4, 2, 2, 3, 4 };

		array.erase(remove(array.begin(), array.end(), 2), array.end());

		EXPECT_EQ((DynamicArray<int>{ 1, 3, 4, 3, 4 }), array);
	} {
		DList<int> list{ 1, 2, 3, 4, 2, 2, 3, 4 };

		list.erase(remove(list.begin(), list.end(), 2), list.end());

		EXPECT_EQ((DList<int>{ 1, 3, 4, 3, 4 }), list);
	}
}

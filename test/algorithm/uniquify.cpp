#include "../test.hpp"
#include <libbr/algorithm/uniquify.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>

using namespace BR;

TEST(Algorithm, uniquify) {
	{
		DynamicArray<int> array{ 1, 1, 2, 2, 3, 1, 1, 2, 3 };

		array.erase(uniquify(array.begin(), array.end()), array.end());

		EXPECT_EQ((DynamicArray<int>{ 1, 2, 3, 1, 2, 3 }), array);
	} {
		DList<int> list{ 1, 1, 2, 2, 3, 1, 1, 2, 3 };

		list.erase(uniquify(list.begin(), list.end()), list.end());

		EXPECT_EQ((DList<int>{ 1, 2, 3, 1, 2, 3 }), list);
	}
}
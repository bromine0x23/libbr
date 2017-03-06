#include "../test.hpp"
#include <libbr/algorithm/replace.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>

using namespace BR;

TEST(Algorithm, replace) {
	{
		DynamicArray<int> array{ 1, 2, 3, 4, 2, 2, 3, 4 };

		replace(array.begin(), array.end(), 2, 22);

		EXPECT_EQ((DynamicArray<int>{ 1, 22, 3, 4, 22, 22, 3, 4 }), array);
	} {
		DList<int> list{ 1, 2, 3, 4, 2, 2, 3, 4 };

		replace(list.begin(), list.end(), 2, 22);

		EXPECT_EQ((DList<int>{ 1, 22, 3, 4, 22, 22, 3, 4 }), list);
	} {
		SList<int> list{ 1, 2, 3, 4, 2, 2, 3, 4 };

		replace(list.begin(), list.end(), 2, 22);

		EXPECT_EQ((SList<int>{ 1, 22, 3, 4, 22, 22, 3, 4 }), list);
	}
}

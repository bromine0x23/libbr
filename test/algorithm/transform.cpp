#include "../test.hpp"
#include <libbr/algorithm/transform.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>

using namespace BR;

TEST(Algorithm, transform) {
	{
		DynamicArray<int> array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		transform(array.cbegin(), array.cend(), array.begin(), [](int x){ return x + x; });

		EXPECT_EQ((DynamicArray<int>{ 2, 4, 6, 8, 10, 12, 14, 16, 18 }), array);
	} {
		DynamicArray<int> array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		DList<int> dlist{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		SList<int> slist{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		transform(array.cbegin(), array.cend(), array.begin(), [](int x, int y, int z){ return x * y + z; }, dlist.cbegin(), slist.cbegin());

		EXPECT_EQ((DynamicArray<int>{ 2, 6, 12, 20, 30, 42, 56, 72, 90 }), array);
	}
}
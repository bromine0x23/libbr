#include "../test.hpp"
#include <libbr/algorithm/accumulate.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>
#include <libbr/functional/multiply.hpp>

using namespace BR;

TEST(Algorithm, accumulate) {
	{
		DynamicArray<int> array{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

		EXPECT_EQ(55, accumulate(array.cbegin(), array.cend(), 0));

		EXPECT_EQ(3628800, accumulate(array.cbegin(), array.cend(), 1, Multiply<int, int>()));
	} {
		DList<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

		EXPECT_EQ(55, accumulate(list.cbegin(), list.cend(), 0));

		EXPECT_EQ(3628800, accumulate(list.cbegin(), list.cend(), 1, Multiply<int, int>()));
	} {
		SList<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

		EXPECT_EQ(55, accumulate(list.cbegin(), list.cend(), 0));

		EXPECT_EQ(3628800, accumulate(list.cbegin(), list.cend(), 1, Multiply<int, int>()));
	}
}

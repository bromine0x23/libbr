#include "../test.hpp"
#include <libbr/algorithm/accumulate.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/functional/multiply.hpp>

using namespace BR;

TEST(Algorithm, accumulate) {
	{
		DynamicArray<int> array{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

		EXPECT_EQ(55, accumulate(array.begin(), array.end(), 0));

		EXPECT_EQ(3628800, accumulate(array.begin(), array.end(), 1, Multiply<int, int>()));
	} {
		DList<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

		EXPECT_EQ(55, accumulate(list.begin(), list.end(), 0));

		EXPECT_EQ(3628800, accumulate(list.begin(), list.end(), 1, Multiply<int, int>()));
	}
}

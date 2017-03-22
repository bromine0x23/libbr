#include "../test.hpp"
#include <libbr/algorithm/min_element.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>
#include <libbr/iterator/distance.hpp>
#include <libbr/math/function/abs.hpp>

using namespace BR;

TEST(Algorithm, min_element) {
	auto absolute = [](int x, int y){ return abs(x) < abs(y); };
	{
		DynamicArray<int> array{ 3, 1, -14, 1, 5, -14, 9 };

		EXPECT_EQ(2, distance(array.cbegin(), min_element(array.cbegin(), array.cend())));

		EXPECT_EQ(1, distance(array.cbegin(), min_element(array.cbegin(), array.cend(), absolute)));
	} {
		DList<int> list{ 3, 1, -14, 1, 5, -14, 9 };

		EXPECT_EQ(2, distance(list.cbegin(), min_element(list.cbegin(), list.cend())));

		EXPECT_EQ(1, distance(list.cbegin(), min_element(list.cbegin(), list.cend(), absolute)));
	} {
		SList<int> list{ 3, 1, -14, 1, 5, -14, 9 };

		EXPECT_EQ(2, distance(list.cbegin(), min_element(list.cbegin(), list.cend())));

		EXPECT_EQ(1, distance(list.cbegin(), min_element(list.cbegin(), list.cend(), absolute)));
	}
}
#include "../test.hpp"
#include <libbr/algorithm/max_min_element.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>
#include <libbr/iterator/distance.hpp>
#include <libbr/math/function/abs.hpp>

using namespace BR;

TEST(Algorithm, max_min_element) {
	auto absolute = [](int x, int y){ return abs(x) < abs(y); };
	{
		DynamicArray<int> array{ 3, 1, -14, 1, 5, -14, 9 };
		{
			auto pair = max_min_element(array.cbegin(), array.cend());

			EXPECT_EQ(6, distance(array.cbegin(), pair.first));

			EXPECT_EQ(5, distance(array.cbegin(), pair.second));
		} {
			auto pair = max_min_element(array.cbegin(), array.cend(), absolute);

			EXPECT_EQ(2, distance(array.cbegin(), pair.first));

			EXPECT_EQ(3, distance(array.cbegin(), pair.second));
		}
	} {
		DList<int> list{ 3, 1, -14, 1, 5, -14, 9 };
		{
			auto pair = max_min_element(list.cbegin(), list.cend());

			EXPECT_EQ(6, distance(list.cbegin(), pair.first));

			EXPECT_EQ(5, distance(list.cbegin(), pair.second));
		} {
			auto pair = max_min_element(list.cbegin(), list.cend(), absolute);

			EXPECT_EQ(2, distance(list.cbegin(), pair.first));

			EXPECT_EQ(3, distance(list.cbegin(), pair.second));
		}
	} {
		SList<int> list{ 3, 1, -14, 1, 5, -14, 9 };
		{
			auto pair = max_min_element(list.cbegin(), list.cend());

			EXPECT_EQ(6, distance(list.cbegin(), pair.first));

			EXPECT_EQ(5, distance(list.cbegin(), pair.second));
		} {
			auto pair = max_min_element(list.cbegin(), list.cend(), absolute);

			EXPECT_EQ(2, distance(list.cbegin(), pair.first));

			EXPECT_EQ(3, distance(list.cbegin(), pair.second));
		}
	}
}
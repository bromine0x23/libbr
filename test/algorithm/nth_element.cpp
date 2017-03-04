#include "../test.hpp"
#include <libbr/algorithm/nth_element.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>
#include <libbr/functional/greater.hpp>

using namespace BR;

TEST(Algorithm, nth_element) {
	DynamicArray<int> array{ 5, 6, 4, 3, 2, 6, 7, 9, 3 };

	nth_element(array.begin(), array.begin() + array.size() / 2, array.end());

	EXPECT_EQ(5, array.at(array.size() / 2));

	nth_element(array.begin(), array.begin() + 1, array.end(), Greater<>());

	EXPECT_EQ(7, array.at(1));
}

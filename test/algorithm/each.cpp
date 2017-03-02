#include "../test.hpp"
#include <libbr/algorithm/each.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>

using namespace BR;

struct Sum {
	void operator()(int n) { sum += n; }
	int sum = 0;
};

TEST(Algorithm, each) {
	{
		DynamicArray<int> array{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		auto sum = each(array.cbegin(), array.cend(), Sum());

		EXPECT_EQ(45, sum.sum);

		sum.sum = 0;
		each(array.begin(), array.end(), [](auto & x){ ++x; });
		each(array.cbegin(), array.cend(), sum);

		EXPECT_EQ(55, sum.sum);
	} {
		DList<int> list{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		auto sum = each(list.cbegin(), list.cend(), Sum());

		EXPECT_EQ(45, sum.sum);

		sum.sum = 0;
		each(list.begin(), list.end(), [](auto & x){ ++x; });
		each(list.cbegin(), list.cend(), sum);

		EXPECT_EQ(55, sum.sum);
	}
}

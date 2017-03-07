#include "../test.hpp"
#include <libbr/algorithm/each_n.hpp>

#include <libbr/algorithm/each.hpp>
#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>

using namespace BR;

namespace {

struct Sum {
	void operator()(int n) { sum += n; }
	int sum = 0;
};

}

TEST(Algorithm, each_n) {
	{
		DynamicArray<int> array{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		auto sum = each(array.cbegin(), array.cend(), Sum());

		EXPECT_EQ(45, sum.sum);

		sum.sum = 0;
		each_n(array.begin(), array.size(), [](auto & x){ ++x; });
		each_n(array.cbegin(), array.size(), sum);

		EXPECT_EQ(55, sum.sum);
	} {
		DList<int> list{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		auto sum = each(list.cbegin(), list.cend(), Sum());

		EXPECT_EQ(45, sum.sum);

		sum.sum = 0;
		each_n(list.begin(), list.size(), [](auto & x){ ++x; });
		each_n(list.cbegin(), list.size(), sum);

		EXPECT_EQ(55, sum.sum);
	}
}

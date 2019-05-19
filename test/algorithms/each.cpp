#include "test.hpp"

#include <libbr/algorithms/each.hpp>

using namespace BR;

namespace {

struct Sum {
	void operator()(int n) { sum += n; }

	int sum = 0;
};

}

TEST(Algorithms, each) {


	int array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	auto sum = each(array, array + 10, Sum());

	EXPECT_EQ(45, sum.sum);

	sum.sum = 0;
	each(array, array + 10, [](int & x){ ++x; });
	each(array, array + 10, sum);

	EXPECT_EQ(55, sum.sum);
}

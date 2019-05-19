#include "test.hpp"

#include <libbr/algorithms/each_n.hpp>

using namespace BR;

namespace {

struct Sum {
	void operator()(int n) { sum += n; }

	int sum = 0;
};

}

TEST(Algorithms, each_n) {


	int array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	auto sum = Sum();
	EXPECT_EQ(array + 10, each_n(array, 10, sum));
	EXPECT_EQ(45, sum.sum);

	sum.sum = 0;
	each_n(array, 10, [](int & x){ ++x; });
	each_n(array, 10, sum);

	EXPECT_EQ(55, sum.sum);
}

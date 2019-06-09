#include "test.hpp"

#include <libbr/operators/partially_ordered.hpp>

using namespace BR;

namespace {

struct Integer : public PartiallyOrdered<Integer> {

	int i;

	Integer(int i) : i(i) {}

	auto operator<(Integer const & y) const -> Boolean {
		return i < y.i;
	}
};

struct Floating : public PartiallyOrdered<Floating>, public PartiallyOrdered<Floating, Integer> {

	double d;

	Floating(double d) : d(d) {}

	auto operator<(Floating const & y) const -> Boolean {
		return d < y.d;
	}

	auto operator<(Integer const & y) const -> Boolean {
		return d < y.i;
	}

	auto operator>(Integer const & y) const -> Boolean {
		return d > y.i;
	}
};

}

TEST(Operators, PartiallyOrdered) {
	Integer ix{1};
	Integer iy{2};
	Floating fx{1.0};
	Floating fy{2.0};

	EXPECT_TRUE(ix < iy);
	EXPECT_TRUE(ix <= iy);
	EXPECT_FALSE(ix > iy);
	EXPECT_FALSE(ix >= iy);

	EXPECT_TRUE(fx < fy);
	EXPECT_TRUE(fx <= fy);
	EXPECT_FALSE(fx > fy);
	EXPECT_FALSE(fx >= fy);

	EXPECT_FALSE(ix < fx);
	EXPECT_TRUE(ix <= fx);
	EXPECT_FALSE(ix > fx);
	EXPECT_TRUE(ix >= fx);
}

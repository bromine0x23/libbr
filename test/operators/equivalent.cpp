#include "test.hpp"

#include <libbr/operators/equivalent.hpp>

using namespace BR;

namespace {

struct Integer : public Equivalent<Integer> {

	int i;

	Integer(int i) : i(i) {}

	auto operator==(Integer const & y) const -> Boolean {
		return i == y.i;
	}
};

struct Floating : public Equivalent<Floating>, public Equivalent<Floating, Integer> {

	double d;

	Floating(double d) : d(d) {}

	auto operator==(Floating const & y) const -> Boolean {
		return d == y.d;
	}

	auto operator==(Integer const & y) const -> Boolean {
		return d == y.i;
	}
};

}

TEST(Operators, Equivalent) {
	Integer ix{1};
	Integer iy{2};
	Floating fx{1.0};
	Floating fy{2.0};

	EXPECT_FALSE(ix == iy);
	EXPECT_TRUE(ix != iy);

	EXPECT_FALSE(fx == fy);
	EXPECT_TRUE(fx != fy);

	EXPECT_TRUE(ix == fx);
	EXPECT_FALSE(ix != fx);
	EXPECT_FALSE(iy == fx);
	EXPECT_TRUE(iy != fx);
}

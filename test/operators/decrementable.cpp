#include "test.hpp"

#include <libbr/operators/decrementable.hpp>

using namespace BR;

namespace {

struct Integer : public Decrementable<Integer> {

	int v;

	Integer(int v) : v(v) {}

	auto operator--() -> Integer & {
		--v;
		return *this;
	}
};

}

TEST(Operators, Decrementable) {
	Integer i{5};

	--i;
	EXPECT_EQ(4, i.v);

	EXPECT_EQ(4, (i--).v);
	EXPECT_EQ(3, i.v);
}

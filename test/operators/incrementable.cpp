#include "test.hpp"

#include <libbr/operators/incrementable.hpp>

using namespace BR;

namespace {

struct Integer : public Incrementable<Integer> {

	int v;

	Integer(int v) : v(v) {}

	auto operator++() -> Integer & {
		++v;
		return *this;
	}
};

}

TEST(Operators, Incrementable) {
	Integer i{1};

	++i;
	EXPECT_EQ(2, i.v);

	EXPECT_EQ(2, (i++).v);
	EXPECT_EQ(3, i.v);
}

#include "test.hpp"

#include <libbr/operators/generically_totally_ordered.hpp>

using namespace BR;

namespace {

template< typename TValue >
struct Value : public GenericallyTotallyOrdered< Value<TValue>, Value > {

	TValue value;

	Value(TValue value) : value(value) {}

	template< typename TOtherValue >
	auto operator==(Value<TOtherValue> const & y) const -> Boolean {
		return value == y.value;
	}

	template< typename TOtherValue >
	auto operator<(Value<TOtherValue> const & y) const -> Boolean {
		return value < y.value;
	}

	template< typename TOtherValue >
	auto operator>(Value<TOtherValue> const & y) const -> Boolean {
		return value > y.value;
	}
};

}

TEST(Operators, GenericallyTotallyOrdered) {
	Value<int> vi{1};
	Value<long> vl{1L};
	Value<double> vd{2.0};

	EXPECT_TRUE(vi == vl);
	EXPECT_FALSE(vi != vl);
	EXPECT_FALSE(vi < vl);
	EXPECT_TRUE(vi <= vl);
	EXPECT_FALSE(vi > vl);
	EXPECT_TRUE(vi >= vl);

	EXPECT_FALSE(vi == vd);
	EXPECT_TRUE(vi != vd);
	EXPECT_TRUE(vi < vd);
	EXPECT_TRUE(vi <= vd);
	EXPECT_FALSE(vi > vd);
	EXPECT_FALSE(vi >= vd);
}

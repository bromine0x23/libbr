#include "test.hpp"

#include <libbr/operators/generically_equivalent.hpp>

using namespace BR;

namespace {

template< typename TValue >
struct Value : public GenericallyEquivalent< Value<TValue>, Value > {

	TValue value;

	Value(TValue value) : value(value) {}

	template< typename TOtherValue >
	auto operator==(Value<TOtherValue> const & y) const -> Boolean {
		return value == y.value;
	}
};

}

TEST(Operators, GenericallyEquivalent) {
	Value<int> vi{1};
	Value<double> vd{1.0};

	EXPECT_TRUE(vi == vd);
	EXPECT_FALSE(vi != vd);
}

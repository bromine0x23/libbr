#include "../test.hpp"
#include <libbr/container/array.hpp>
#include <libbr/container/tuple.hpp>
#include <libbr/utility/optional.hpp>

using namespace BR;

TEST(Utility, Optional) {
	{
		Optional<int> optional;

		EXPECT_TRUE(!optional);
		EXPECT_THROW(optional.value(), OptionalAccessException);

		optional = 0;

		EXPECT_EQ(0, optional);

		optional.emplace(1);

		EXPECT_EQ(1, optional);
	} {
		Optional< Tuple<int, double> > optional;

		EXPECT_TRUE(!optional);
		EXPECT_THROW(optional.value(), OptionalAccessException);

		auto tuple = make_tuple(1, 1.0);

		optional.emplace(1, 1.0);

		EXPECT_EQ(tuple, optional);

	} {
		Optional< Array< SInt, 5 > > optional;

		EXPECT_TRUE(!optional);
		EXPECT_THROW(optional.value(), OptionalAccessException);
	}
}

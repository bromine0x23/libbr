#include "test.hpp"

#include <libbr/functional/greater_equal.hpp>

using namespace BR;

TEST(Functional, GreaterEqual) {
	{
		auto greater_equal = GreaterEqual<>();

		EXPECT_TRUE(greater_equal(1, 1));
		EXPECT_TRUE(greater_equal(2, 1));
		EXPECT_TRUE(greater_equal(1, 1.0));
		EXPECT_TRUE(greater_equal(2, 1.0));
	} {
		auto greater_equal = GreaterEqual<UInt>();

		EXPECT_TRUE(greater_equal(1, 1));
		EXPECT_TRUE(greater_equal(2, 1));
		EXPECT_TRUE(greater_equal(-1, -1));
		EXPECT_TRUE(greater_equal(-1, 2));
		EXPECT_FALSE(greater_equal(-2, -1));
	}
}

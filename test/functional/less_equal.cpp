#include "test.hpp"

#include <libbr/functional/less_equal.hpp>

using namespace BR;

TEST(Functional, LessEqual) {
	{
		auto less_equal = LessEqual<>();

		EXPECT_TRUE(less_equal(1, 1));
		EXPECT_TRUE(less_equal(1, 2));
		EXPECT_TRUE(less_equal(1, 1.0));
		EXPECT_TRUE(less_equal(1, 2.0));
	} {
		auto less_equal = LessEqual<UInt>();

		EXPECT_TRUE(less_equal(1, 1));
		EXPECT_TRUE(less_equal(1, 2));
		EXPECT_TRUE(less_equal(-1, -1));
		EXPECT_FALSE(less_equal(-1, 2));
	}
}

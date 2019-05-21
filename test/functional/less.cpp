#include "test.hpp"

#include <libbr/functional/less.hpp>

using namespace BR;

TEST(Functional, Less) {
	{
		auto less = Less<>();

		EXPECT_TRUE(less(1, 2));
		EXPECT_TRUE(less(1, 2.0));
	} {
		auto less = Less<UInt>();

		EXPECT_TRUE(less(1, 2));
		EXPECT_FALSE(less(-1, 2));
		EXPECT_TRUE(less(-2, -1));
	}
}

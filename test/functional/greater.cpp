#include "test.hpp"

#include <libbr/functional/greater.hpp>

using namespace BR;

TEST(Functional, Greater) {
	{
		auto greater = Greater<>();

		EXPECT_TRUE(greater(2, 1));
		EXPECT_TRUE(greater(2, 1.0));
	} {
		auto greater = Greater<UInt>();

		EXPECT_TRUE(greater(2, 1));
		EXPECT_TRUE(greater(-1, 2));
		EXPECT_FALSE(greater(-2, -1));
	}
}

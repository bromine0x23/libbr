#include "test.hpp"

#include <libbr/functional/equal.hpp>

using namespace BR;

TEST(Functional, Equal) {
	{
		auto equal = Equal<>();

		EXPECT_TRUE(equal(1, 1));
		EXPECT_FALSE(equal(1, 2));
		EXPECT_TRUE(equal(1, 1.0));
		EXPECT_FALSE(equal(1, 2.0));
	}
}

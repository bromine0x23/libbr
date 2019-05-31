#include "test.hpp"

#include <libbr/math/gcd.hpp>

using namespace BR;

TEST(Math, gcd) {
	EXPECT_EQ(1, gcd(1, 1));
	EXPECT_EQ(3, gcd(12, 21));
	EXPECT_EQ(3, gcd(21, 12));
}

#include "../test.hpp"
#include <libbr/algorithm/clamp.hpp>

using namespace BR;

TEST(Algorithm, clamp) {
	EXPECT_EQ(128, clamp(167, 0, 128));
	EXPECT_EQ(  0, clamp(-69, 0, 128));
	EXPECT_EQ(111, clamp(111, 0, 128));
}

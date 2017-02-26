#include "../test.hpp"
#include <libbr/random/ranlux48_base.hpp>

using namespace BR;

TEST(Random, Ranlux48Base) {
	Ranlux48Base engine(233);
	EXPECT_EQ(0xFFFFFFFFFFFFULL, engine.max());
	EXPECT_EQ(0x000000000000ULL, engine.min());
	EXPECT_EQ(0x4C243F3597D6ULL, engine());
	EXPECT_EQ(0x074D74CC9A34ULL, engine());
	engine.discard(2);
	EXPECT_EQ(0x3F8AF3ADB0BFULL, engine());
	EXPECT_EQ(0x46FFE8DE77BDULL, engine());
}
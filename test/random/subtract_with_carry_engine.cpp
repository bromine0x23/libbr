#include "../test.hpp"
#include <libbr/random/subtract_with_carry_engine.hpp>

using namespace BR;

TEST(SubtractWithCarryEngine, Ranlux24Base) {
	Ranlux24Base engine(233);
	EXPECT_EQ(0x3597D6U, engine());
	EXPECT_EQ(0xF44C24U, engine());
	engine.discard(2);
	EXPECT_EQ(0xC104AFU, engine());
	EXPECT_EQ(0xBB673FU, engine());
}

TEST(SubtractWithCarryEngine, Ranlux48Base) {
	Ranlux48Base engine(233);
	EXPECT_EQ(0x4C243F3597D6ULL, engine());
	EXPECT_EQ(0x074D74CC9A34ULL, engine());
	engine.discard(2);
	EXPECT_EQ(0x3F8AF3ADB0BFULL, engine());
	EXPECT_EQ(0x46FFE8DE77BDULL, engine());
}
#include "../test.hpp"
#include <libbr/random/ranlux24_base.hpp>

using namespace BR;

TEST(Random, Ranlux24Base) {
	{
		Ranlux24Base engine;
		engine.discard(9999);
		EXPECT_EQ(0x791FA0U, engine());
	} {
		Ranlux24Base engine(233);
		EXPECT_EQ(0xFFFFFFU, engine.max());
		EXPECT_EQ(0x000000U, engine.min());
		EXPECT_EQ(0x3597D6U, engine());
		EXPECT_EQ(0xF44C24U, engine());
		engine.discard(2);
		EXPECT_EQ(0xC104AFU, engine());
		EXPECT_EQ(0xBB673FU, engine());
	}
}
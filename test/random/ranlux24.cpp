#include "../test.hpp"
#include <libbr/random/ranlux24.hpp>

using namespace BR;

TEST(Random, Ranlux24) {
	{
		Ranlux24 engine;
		engine.discard(9999);
		EXPECT_EQ(0x97160AU, engine());
	} {
		Ranlux24 engine(233);
		EXPECT_EQ(0xFFFFFFU, engine.max());
		EXPECT_EQ(0x000000U, engine.min());
		EXPECT_EQ(0x3597D6U, engine());
		EXPECT_EQ(0xF44C24U, engine());
		engine.discard(2);
		EXPECT_EQ(0xC104AFU, engine());
		EXPECT_EQ(0xBB673FU, engine());
	}
}
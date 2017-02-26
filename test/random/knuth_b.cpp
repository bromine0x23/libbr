#include "../test.hpp"
#include <libbr/random/knuth_b.hpp>

using namespace BR;

TEST(Random, KnuthB) {
	{
		KnuthB engine;
		engine.discard(9999);
		EXPECT_EQ(0x424CF248U, engine());
	} {
		KnuthB engine(233);
		EXPECT_EQ(0x7FFFFFFEU, engine.max());
		EXPECT_EQ(0x00000001U, engine.min());
		EXPECT_EQ(0x023D203BU, engine());
		EXPECT_EQ(0x114005CEU, engine());
		engine.discard(2);
		EXPECT_EQ(0x187355DCU, engine());
		EXPECT_EQ(0x454D5311U, engine());
	}
}
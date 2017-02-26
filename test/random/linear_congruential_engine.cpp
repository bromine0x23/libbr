#include "../test.hpp"
#include <libbr/random/linear_congruential_engine.hpp>

using namespace BR;

TEST(Random, LinearCongruentialEngine) {
	LinearCongruentialEngine<UInt16, 16807, 0, 0x7FFFU> engine(233);
	EXPECT_EQ(0x4176U, engine());
	EXPECT_EQ(0x4B8DU, engine());
	engine.discard(2);
	EXPECT_EQ(0x1EA0U, engine());
	EXPECT_EQ(0x2A15U, engine());
}
#include "../test.hpp"
#include <libbr/random/mersenne_twister_engine.hpp>

using namespace BR;

TEST(MersenneTwisterEngine, MT19937) {
	MT19937 engine(233);
	EXPECT_EQ(0x26439BE7, engine());
	EXPECT_EQ(0x7D120F27, engine());
	engine.discard(2);
	EXPECT_EQ(0x954A57FC, engine());
	EXPECT_EQ(0x8FEA4483, engine());
}

TEST(MersenneTwisterEngine, MT19937_64) {
	MT19937_64 engine(233);
	EXPECT_EQ(0xE1A9DB5D833E02F9ULL, engine());
	EXPECT_EQ(0xCE66D897E298C671ULL, engine());
	engine.discard(2);
	EXPECT_EQ(0xE64EFB1F851F1817ULL, engine());
	EXPECT_EQ(0x9BDB9C55AD7A7F70ULL, engine());
}
#include "../test.hpp"
#include <libbr/random/mt19937.hpp>

using namespace BR;

TEST(Random, MT19937) {
	MT19937 engine(233);
	EXPECT_EQ(0xFFFFFFFFU, engine.max());
	EXPECT_EQ(0x00000000U, engine.min());
	EXPECT_EQ(0x26439BE7U, engine());
	EXPECT_EQ(0x7D120F27U, engine());
	engine.discard(2);
	EXPECT_EQ(0x954A57FCU, engine());
	EXPECT_EQ(0x8FEA4483U, engine());
}
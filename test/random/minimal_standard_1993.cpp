#include "../test.hpp"
#include <libbr/random/minimal_standard_1993.hpp>

using namespace BR;

TEST(Random, MinimalStandard1993) {
	MinimalStandard1993 engine(233);
	EXPECT_EQ(0x7FFFFFFEU, engine.max());
	EXPECT_EQ(0x00000001U, engine.min());
	EXPECT_EQ(0x00AB9E27U, engine());
	EXPECT_EQ(0x6801FCC5U, engine());
	engine.discard(2);
	EXPECT_EQ(0x444F943AU, engine());
	EXPECT_EQ(0x194EC907U, engine());
}
#include "../test.hpp"
#include <libbr/random/minimal_standard_1988.hpp>

using namespace BR;

TEST(Random, MinimalStandard1988) {
	{
		MinimalStandard1988 engine;
		engine.discard(9999);
		EXPECT_EQ(0x3E345911U, engine());
	} {
		MinimalStandard1988 engine(233);
		EXPECT_EQ(0x7FFFFFFEU, engine.max());
		EXPECT_EQ(0x00000001U, engine.min());
		EXPECT_EQ(0x003BC0FFU, engine());
		EXPECT_EQ(0x52FBA577U, engine());
		engine.discard(2);
		EXPECT_EQ(0x114005CEU, engine());
		EXPECT_EQ(0x023D203BU, engine());
	}
}
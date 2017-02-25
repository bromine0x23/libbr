#include "../test.hpp"
#include <libbr/random/linear_congruential_engine.hpp>

using namespace BR;

TEST(LinearCongruentialEngine, MinimalStandard1988) {
	MinimalStandard1988 engine(233);
	EXPECT_EQ(0x003BC0FFU, engine());
	EXPECT_EQ(0x52FBA577U, engine());
	engine.discard(2);
	EXPECT_EQ(0x114005CEU, engine());
	EXPECT_EQ(0x023D203BU, engine());
}

TEST(LinearCongruentialEngine, MinimalStandard1993) {
	MinimalStandard1993 engine(233);
	EXPECT_EQ(0x00AB9E27U, engine());
	EXPECT_EQ(0x6801FCC5U, engine());
	engine.discard(2);
	EXPECT_EQ(0x444F943AU, engine());
	EXPECT_EQ(0x194EC907U, engine());
}

TEST(LinearCongruentialEngine, UInt16) {
	LinearCongruentialEngine<UInt16, 16807, 0, 0x7FFFU> engine(233);
	EXPECT_EQ(0x4176U, engine());
	EXPECT_EQ(0x4B8DU, engine());
	engine.discard(2);
	EXPECT_EQ(0x1EA0U, engine());
	EXPECT_EQ(0x2A15U, engine());
}
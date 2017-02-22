#include "../test.hpp"
#include <libbr/random/linear_congruential_engine.hpp>

using namespace BR;

TEST(LinearCongruentialEngine, MinimalStandard1988) {

	MinimalStandard1988 engine(233);

	EXPECT_EQ(3916031, engine());
	EXPECT_EQ(1392223607, engine());
	engine.discard(2);
	EXPECT_EQ(289408462, engine());
	EXPECT_EQ(37560379, engine());
}

TEST(LinearCongruentialEngine, MinimalStandard1993) {
	MinimalStandard1993 engine(233);

	EXPECT_EQ(11247143, engine());
	EXPECT_EQ(1744960709, engine());
	engine.discard(2);
	EXPECT_EQ(1146065978, engine());
	EXPECT_EQ(424593671, engine());
}

TEST(LinearCongruentialEngine, UInt16) {
	LinearCongruentialEngine<UInt16, 16807, 0, 0x7FFFU> engine(233);
	EXPECT_EQ(16758, engine());
	EXPECT_EQ(19341, engine());
	engine.discard(2);
	EXPECT_EQ(7840, engine());
	EXPECT_EQ(10773, engine());
}
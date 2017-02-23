#include "../test.hpp"
#include <libbr/random/mersenne_twister_engine.hpp>

using namespace BR;

TEST(MersenneTwisterEngine, MT19937) {
	{
		MT19937 engine(233);

		EXPECT_EQ(641965031, engine());
		EXPECT_EQ(2098335527, engine());
		engine.discard(2);
		EXPECT_EQ(2504677372, engine());
		EXPECT_EQ(2414494851, engine());
	}
}
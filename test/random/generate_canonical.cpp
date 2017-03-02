#include "../test.hpp"
#include <libbr/random/generate_canonical.hpp>
#include <libbr/random/ranlux24.hpp>
#include <libbr/random/mt19937.hpp>

using namespace BR;

TEST(Random, generate_canonical) {
	{
		Ranlux24 engine;
		engine.seed(); EXPECT_EQ(0.89641070365905761719, (generate_canonical<double, 24>(engine)));
		engine.seed(); EXPECT_EQ(0.97298180439535997266, (generate_canonical<double, 48>(engine)));
		engine.seed(); EXPECT_EQ(0.85136216717849999558, (generate_canonical<double, 64>(engine)));
	} {
		MT19937 engine;
		engine.seed(); EXPECT_EQ(0.81472367048263549805, (generate_canonical<float,  24>(engine)));
		engine.seed(); EXPECT_EQ(0.13547700429678050105, (generate_canonical<double, 53>(engine)));
	}
}
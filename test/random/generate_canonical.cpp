#include "../test.hpp"
#include <libbr/random/generate_canonical.hpp>
#include <libbr/random/ranlux24.hpp>

using namespace BR;

TEST(Random, generate_canonical) {
	Ranlux24 engine;
	engine.seed(); EXPECT_EQ(0.8964107036590576, (generate_canonical<double, 24>(engine)));
	engine.seed(); EXPECT_EQ(0.97298180439536,   (generate_canonical<double, 48>(engine)));
	engine.seed(); EXPECT_EQ(0.8513621671785,    (generate_canonical<double, 72>(engine)));
}
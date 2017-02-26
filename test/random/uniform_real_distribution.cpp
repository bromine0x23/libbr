#include "../test.hpp"
#include <libbr/random/uniform_real_distribution.hpp>
#include <libbr/random/minimal_standard_1993.hpp>

using namespace BR;

TEST(Random, UniformRealDistribution) {
	MinimalStandard1993 engine;
	UniformRealDistribution<> distribution(1, 2);
	EXPECT_EQ(1.0850324487174336507, distribution(engine));
}
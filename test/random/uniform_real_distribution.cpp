#include "../test.hpp"
#include <libbr/random/uniform_real_distribution.hpp>
#include <libbr/random/mt19937.hpp>

using namespace BR;

TEST(Random, UniformRealDistribution) {
	MT19937 engine;
	UniformRealDistribution<> distribution(1, 2);
	EXPECT_EQ(1.1354770042967805566, distribution(engine));
}
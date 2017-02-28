#include "../test.hpp"
#include <libbr/random/exponential_distribution.hpp>
#include <libbr/random/mt19937.hpp>

using namespace BR;

TEST(Random, ExponentialDistribution) {
	MT19937 engine;
	ExponentialDistribution<> distribution(1);
	EXPECT_EQ(0.14557737420884162005, distribution(engine));
}
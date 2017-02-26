#include "../test.hpp"
#include <libbr/random/bernoulli_distribution.hpp>
#include <libbr/random/minimal_standard_1993.hpp>

using namespace BR;

TEST(Random, BernoulliDistribution) {
	MinimalStandard1993 engine;
	BernoulliDistribution distribution(0.25);
	EXPECT_TRUE(distribution(engine));
	EXPECT_FALSE(distribution(engine));
	engine.discard(2);
	EXPECT_FALSE(distribution(engine));
	EXPECT_FALSE(distribution(engine));
}
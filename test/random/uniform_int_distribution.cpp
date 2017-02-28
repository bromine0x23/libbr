#include "../test.hpp"
#include <libbr/random/uniform_int_distribution.hpp>
#include <libbr/random/mt19937.hpp>
#include <libbr/random/mt19937_64.hpp>

using namespace BR;

TEST(Random, UniformIntDistribution) {
	UniformIntDistribution<> distribution(-1123, 5127);
	{
		MT19937 engine;
		EXPECT_EQ(3969, distribution(engine));
	} {
		MT19937_64 engine;
		EXPECT_EQ(3795, distribution(engine));
	}
}
#include "../test.hpp"
#include <libbr/algorithm/shuffle.hpp>

#include <libbr/container/dynamic_array.hpp>
#include <libbr/random/mt19937.hpp>

using namespace BR;

TEST(Algorithm, shuffle) {
	DynamicArray<int> array{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	MT19937 engine;

	shuffle(array.begin(), array.end(), engine);

	// 5, 8, 0, 3, 4, 2, 9, 7, 1, 6
}
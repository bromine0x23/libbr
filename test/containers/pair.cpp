#include "test.hpp"

#include <libbr/containers/pair.hpp>

using namespace BR;

#if defined(BR_DEBUG)
template class BR::Pair<int, float>;
#endif

TEST(Containers, Pair) {
	Pair< int, float > pair0;
	pair0 = { 1, 2.0 };

	auto pair1 = Pair< int, float >{ 2, 0.2 };

	EXPECT_TRUE(pair0 < pair1);

	swap(pair0, pair1);
}
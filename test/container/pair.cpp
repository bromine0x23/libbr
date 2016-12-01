#include "../test.hpp"
#include <libbr/container/pair.hpp>
using namespace BR;

#if defined(BR_DEBUG)
template class BR::Pair<int, float>;
#endif

TEST(Pair, DefaultConstruct) {
	Pair< int, float > pair;
}
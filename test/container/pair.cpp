#include "../test.hpp"
#include <libbr/container/pair.hpp>
using namespace BR;

template class BR::Pair<int, float>;

TEST(Pair, DefaultConstruct) {
	Pair< int, float > pair;
}
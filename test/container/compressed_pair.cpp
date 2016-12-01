#include "../test.hpp"
#include <libbr/container/compressed_pair.hpp>
#include <libbr/memory/allocator.hpp>

using namespace BR;

#if defined(BR_DEBUG)
template class BR::CompressedPair< int, Allocator<int> >;
#endif

TEST(CompressedPair, DefaultConstruct) {
	CompressedPair< int, Allocator<int> > pair;
}

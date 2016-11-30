#include "../test.hpp"
#include <libbr/container/compressed_pair.hpp>
#include <libbr/memory/allocator.hpp>

using namespace BR;

template class BR::CompressedPair< int, Allocator<int> >;


TEST(CompressedPair, DefaultConstruct) {
	CompressedPair< int, Allocator<int> > pair;
}

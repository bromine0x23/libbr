#include "test.hpp"

#include <libbr/memory/address_of.hpp>

using namespace BR;

TEST(Memory, address_of) {
#if defined(BR_SINCE_CXX17)
	constexpr int x = 43;
	constexpr const int y = *address_of(x);
#endif
}
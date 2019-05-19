#include "test.hpp"

#include <libbr/iterators/reverse_iterator.hpp>

using namespace BR;

TEST(Iterators, ReverseIterator) {
	char string[] = "0123456789";

	auto reversed = make_reverse_iterator(string + 5);

	EXPECT_EQ('4', *reversed);
}

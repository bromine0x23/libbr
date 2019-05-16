#include "test.hpp"

#include <libbr/iterators/iterator_traits.hpp>

#include <libbr/type_traits/is_same.hpp>

using namespace BR;

TEST(Iterators, IteratorTraits) {

	using Traits = IteratorTraits<int *>;

	EXPECT_TRUE((is_same< Traits::Iterator, int * >));
	EXPECT_TRUE((is_same< Traits::Element, int>));
	EXPECT_TRUE((is_same< Traits::Pointer, int *>));
	EXPECT_TRUE((is_same< Traits::Reference, int & >));
	EXPECT_TRUE((is_same< Traits::Difference, PointerDifference >));
}

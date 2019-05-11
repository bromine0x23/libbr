#include "test.hpp"

#include <libbr/memory/pointer_traits.hpp>
#include <libbr/type_traits/is_same.hpp>

using namespace BR;

TEST(Memory, PointerTraits) {

	EXPECT_TRUE((is_same<PointerTraits<int *>::Element, int>));
	EXPECT_TRUE((is_same<PointerTraits<int *>::Pointer, int *>));
	EXPECT_TRUE((is_same<PointerTraits<int *>::Difference , PointerDifference>));
	EXPECT_TRUE((is_same<PointerTraits<int *>::Rebind<double>, double *>));

	int t = 0;
	auto p = PointerTraits<decltype(t) *>::make_pointer(t);
	EXPECT_EQ(p, PointerTraits<decltype(t) *>::to_raw(p));
}
#include "../test.hpp"
#include <libbr/container/list.hpp>

using namespace BR;

static bool is_even(int v) {
	return v % 2 == 0;
}

#if defined(BR_DEBUG)
template class BR::List<int>;
#endif

TEST(List, Each) {

	List<int> list{ 0, 1, 2, 3, 4 };

	list.each();
	list.reverse_each();

	EXPECT_TRUE(list.any(is_even));
	EXPECT_FALSE(list.all(is_even));
	EXPECT_FALSE(list.none(is_even));
	EXPECT_TRUE(list.include(2));
	EXPECT_FALSE(list.include(8));
}
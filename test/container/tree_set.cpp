#include "../test.hpp"
#include <libbr/container/tree_set.hpp>
#include <libbr/algorithm/all_of.hpp>

using namespace BR;

#if defined(BR_DEBUG)
template class BR::TreeSet<int>;
#endif

TEST(TreeSet, DefaultConstruct) {
	TreeSet<int> set;
	EXPECT_EQ(0, set.size());
}

TEST(TreeSet, InitializerListConstruct) {
	TreeSet<int> set{ 1, 3, 5, 7, 9 };
	EXPECT_EQ(5, set.size());
	EXPECT_TRUE(all_of(set.begin(), set.end(), [](int const & element){ return element & 1; }));
}

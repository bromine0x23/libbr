#include "../test.hpp"
#include <libbr/container/tree_multi_set.hpp>
#include <libbr/algorithm/all_of.hpp>

using namespace BR;

#if defined(BR_DEBUG)
template class BR::TreeMultiSet<int>;
#endif

TEST(TreeMultiSet, DefaultConstruct) {
	TreeMultiSet<int> set;
	EXPECT_EQ(0, set.size());
}

TEST(TreeMultiSet, InitializerListConstruct) {
	TreeMultiSet<int> set{ 1, 3, 5, 7, 9, 7, 5, 3, 1 };
	EXPECT_EQ(9, set.size());
	EXPECT_TRUE(all_of(set.begin(), set.end(), [](int const & element){ return element & 1; }));
}

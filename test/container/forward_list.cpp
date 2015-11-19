#include <libbr/container/forward_list.hpp>
#include <gtest/gtest.h>

using namespace BR;

template class ForwardList<int>;

template class ForwardList< ForwardList<int> >;

TEST(TestForwardList, Constructor) {
}
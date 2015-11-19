#include <libbr/container/list.hpp>
#include <gtest/gtest.h>

using namespace BR;

template class List<int>;

template class List< List<int> >;

TEST(TestList, Constructor) {
}
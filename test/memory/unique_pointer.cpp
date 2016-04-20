#include <libbr/memory/unique_pointer.hpp>
#include <gtest/gtest.h>

using namespace BR;

template class UniquePointer<int>;

template class UniquePointer<int[]>;

TEST(TestUniquePointer, Constructor) {
}
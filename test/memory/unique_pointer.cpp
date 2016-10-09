#include "../test.hpp"
#include <libbr/memory/unique_pointer.hpp>

namespace BR {

template class UniquePointer<int>;

template class UniquePointer<int[]>;

}

using namespace BR;

TEST(TestUniquePointer, Constructor) {
}
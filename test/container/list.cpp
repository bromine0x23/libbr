#include "../test.hpp"
#include <libbr/container/list.hpp>

namespace BR {

template class List<int>;

template class List< List<int> >;

}

using namespace BR;

struct S {};

TEST(List, Size) {
}
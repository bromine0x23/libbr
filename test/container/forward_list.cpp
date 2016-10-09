#include "../test.hpp"
#include <libbr/container/forward_list.hpp>

using namespace BR;

namespace BR {

template class ForwardList<int>;

template class ForwardList< ForwardList<int> >;

}

TEST(ForwardList, Size) {
}
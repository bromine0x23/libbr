#include "../test.hpp"
#include <libbr/container/rb_tree.hpp>

namespace BR {
}

using namespace BR;

TEST(RBTree, Size) {
	std::cout << "sizeof(Tree<int>): " << sizeof(Detail::Container::RBTree::Base< int, Less<int>, Allocator<int> >) << std::endl ;
	std::cout << "sizeof(Tree<int>): " << sizeof(Detail::Container::RBTree::HeadNode< void * >) << std::endl ;
}
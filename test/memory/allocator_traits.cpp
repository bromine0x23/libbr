#include "test.hpp"

#include <libbr/memory/allocator_traits.hpp>

#include <libbr/memory/allocator.hpp>
#include <libbr/type_traits/is_same.hpp>

using namespace BR;

namespace {

template<typename TElement, Size size>
struct CustomAllocator {

	using Element = TElement;

	template<typename TOtherElement>
	using Rebind = CustomAllocator<TOtherElement, size>;

	static auto max_size() noexcept -> Size {
		return size;
	}
};

}


TEST(Memory, AllocatorTraits) {
	{
		using Traits = AllocatorTraits< Allocator<int> >;

		EXPECT_TRUE((is_same< Traits::Allocator, Allocator<int> >));
		EXPECT_TRUE((is_same< Traits::Element, int >));
		EXPECT_TRUE((is_same< Traits::Pointer, int * >));
		EXPECT_TRUE((is_same< Traits::ConstPointer, int const * >));
		EXPECT_TRUE((is_same< Traits::VoidPointer , void * >));
		EXPECT_TRUE((is_same< Traits::ConstVoidPointer , void const * >));
		EXPECT_TRUE((is_same< Traits::Rebind<double>, Allocator<double> >));
		EXPECT_FALSE(Traits::IS_PROPAGATE_ON_CONTAINER_COPY_ASSIGNMENT);
		EXPECT_TRUE(Traits::IS_PROPAGATE_ON_CONTAINER_MOVE_ASSIGNMENT);
		EXPECT_FALSE(Traits::IS_PROPAGATE_ON_CONTAINER_SWAP);
		EXPECT_TRUE(Traits::IS_ALWAYS_EQUAL);
	} {
		using Traits = AllocatorTraits< CustomAllocator<int, 10> >;

		EXPECT_TRUE((is_same< Traits::Allocator, CustomAllocator<int, 10> >));
		EXPECT_TRUE((is_same< Traits::Element, int >));
		EXPECT_TRUE((is_same< Traits::Pointer, int * >));
		EXPECT_TRUE((is_same< Traits::ConstPointer, int const * >));
		EXPECT_TRUE((is_same< Traits::VoidPointer , void * >));
		EXPECT_TRUE((is_same< Traits::ConstVoidPointer , void const * >));
		EXPECT_TRUE((is_same< Traits::Rebind<double>, CustomAllocator<double, 10> >));
		EXPECT_EQ(Traits::max_size(Traits::Allocator{}), 10);
	}
}
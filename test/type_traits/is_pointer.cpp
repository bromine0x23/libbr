#include "test.hpp"

#include <libbr/type_traits/is_pointer.hpp>

using namespace BR;

TEST(TypeTraits, IsPointer) {
	IS_TRAITS_CHECK_CV(false, Pointer, pointer, void);
}
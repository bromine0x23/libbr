#include "test.hpp"

#include <libbr/type_traits/is_null_pointer.hpp>

using namespace BR;

TEST(TypeTraits, IsNullPointer) {
	IS_TRAITS_CHECK_CV(false, NullPointer, null_pointer, void);
}
#include "test.hpp"

#include <libbr/type_traits/has_copy_constructor.hpp>

using namespace BR;

TEST(TypeTraits, HasCopyConstructor) {
	HAS_TRAITS_CHECK(false, CopyConstructor, copy_constructor, void);
}
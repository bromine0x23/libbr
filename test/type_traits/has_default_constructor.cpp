#include "test.hpp"

#include <libbr/type_traits/has_default_constructor.hpp>

using namespace BR;

TEST(TypeTraits, HasDefaultConstructor) {
	HAS_TRAITS_CHECK(false, DefaultConstructor, default_constructor, void);
}
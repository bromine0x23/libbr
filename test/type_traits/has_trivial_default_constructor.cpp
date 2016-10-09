#include "test.hpp"

#include <libbr/type_traits/has_trivial_default_constructor.hpp>

using namespace BR;

TEST(TypeTraits, HasTrivialDefaultConstructor) {
	HAS_TRAITS_CHECK(false, TrivialDefaultConstructor, trivial_default_constructor, void);
}
#include "test.hpp"

#include <libbr/type_traits/has_trivial_default_constructor.hpp>

using namespace BR;

TEST(TypeTraits, HasTrivialDefaultConstructor) {
	HAS_TRAITS_CHECK(false, TrivialDefaultConstructor, trivial_default_constructor, void);

	HAS_TRAITS_CHECK(true, TrivialDefaultConstructor, trivial_default_constructor, int);
	HAS_TRAITS_CHECK(true, TrivialDefaultConstructor, trivial_default_constructor, int *);
	HAS_TRAITS_CHECK(true, TrivialDefaultConstructor, trivial_default_constructor, int[2]);
	HAS_TRAITS_CHECK(true, TrivialDefaultConstructor, trivial_default_constructor, Class);
}